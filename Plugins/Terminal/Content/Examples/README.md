# Terminal Plugin Examples

This directory contains example implementations and use cases for the Terminal plugin.

## C++ Example: Custom Command Handler

```cpp
// TerminalCommandHandler.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STerminalWidget.h"
#include "TerminalCommandHandler.generated.h"

UCLASS()
class ATerminalCommandHandler : public AActor
{
    GENERATED_BODY()

public:
    ATerminalCommandHandler();

    UPROPERTY()
    TSharedPtr<STerminalWidget> Terminal;

protected:
    virtual void BeginPlay() override;

private:
    void HandleCommand(const FString& Command);
    void ExecuteHelpCommand();
    void ExecuteClearCommand();
    void ExecuteEchoCommand(const FString& Args);
};

// TerminalCommandHandler.cpp
#include "TerminalCommandHandler.h"

ATerminalCommandHandler::ATerminalCommandHandler()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATerminalCommandHandler::BeginPlay()
{
    Super::BeginPlay();

    // Create and initialize terminal
    Terminal = SNew(STerminalWidget)
        .MaxHistoryLines(200)
        .FontSize(12);

    // Bind command handler
    Terminal->OnCommandExecuted.BindUObject(this, &ATerminalCommandHandler::HandleCommand);

    // Show welcome message
    Terminal->AddOutputLine(TEXT("Terminal initialized. Type 'help' for available commands."));
}

void ATerminalCommandHandler::HandleCommand(const FString& Command)
{
    FString TrimmedCommand = Command.TrimStartAndEnd();

    if (TrimmedCommand.IsEmpty())
    {
        return;
    }

    // Parse command and arguments
    FString Cmd, Args;
    if (!TrimmedCommand.Split(TEXT(" "), &Cmd, &Args))
    {
        Cmd = TrimmedCommand;
    }

    Cmd = Cmd.ToLower();

    // Execute commands
    if (Cmd == TEXT("help"))
    {
        ExecuteHelpCommand();
    }
    else if (Cmd == TEXT("clear"))
    {
        ExecuteClearCommand();
    }
    else if (Cmd == TEXT("echo"))
    {
        ExecuteEchoCommand(Args);
    }
    else
    {
        Terminal->AddOutputLine(FString::Printf(TEXT("Unknown command: %s"), *Cmd));
        Terminal->AddOutputLine(TEXT("Type 'help' for available commands."));
    }
}

void ATerminalCommandHandler::ExecuteHelpCommand()
{
    Terminal->AddOutputLine(TEXT("Available commands:"));
    Terminal->AddOutputLine(TEXT("  help  - Show this help message"));
    Terminal->AddOutputLine(TEXT("  clear - Clear the terminal"));
    Terminal->AddOutputLine(TEXT("  echo  - Echo the provided text"));
}

void ATerminalCommandHandler::ExecuteClearCommand()
{
    Terminal->ClearOutput();
}

void ATerminalCommandHandler::ExecuteEchoCommand(const FString& Args)
{
    Terminal->AddOutputLine(Args);
}
```

## Blueprint Example: Simple Terminal Widget

1. **Create a Widget Blueprint:**
   - Create a new Widget Blueprint (name it `WBP_Terminal`)
   - Add a `Terminal Widget` to the canvas
   - Set it to fill the entire canvas
   - Configure properties:
     - Max History Lines: 100
     - Font Size: 10

2. **Handle Command Execution:**
   - In the Event Graph, add an event for `OnCommandExecuted`
   - Use a `Switch on String` node to handle different commands:
     - "help": Call `AddOutputLine` with help text
     - "clear": Call `ClearOutput`
     - "time": Call `AddOutputLine` with current time
     - Default: Call `AddOutputLine` with "Unknown command"

3. **Example Blueprint Event Graph:**
   ```
   Event OnCommandExecuted
       |
       v
   Switch on String (Command)
       |
       +-- "help" --> AddOutputLine ("Available commands: help, clear, time")
       |
       +-- "clear" --> ClearOutput
       |
       +-- "time" --> Get Current Time --> AddOutputLine (Formatted Time)
       |
       +-- Default --> AddOutputLine ("Unknown command: " + Command)
   ```

## CommonUI Example: Game Console

```cpp
// GameConsoleWidget.h
#pragma once

#include "CoreMinimal.h"
#include "CommonTerminalWidget.h"
#include "GameConsoleWidget.generated.h"

UCLASS()
class UGameConsoleWidget : public UCommonTerminalWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnCommandReceived(const FString& Command);

    void RegisterConsoleCommands();
    void ExecuteConsoleCommand(const FString& CommandName, const FString& Args);
};

// GameConsoleWidget.cpp
#include "GameConsoleWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void UGameConsoleWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind to command event
    OnCommandExecuted.AddDynamic(this, &UGameConsoleWidget::OnCommandReceived);

    // Show welcome message
    AddOutputLine(TEXT("Game Console v1.0"));
    AddOutputLine(TEXT("Type 'help' for available commands"));

    RegisterConsoleCommands();
}

void UGameConsoleWidget::OnCommandReceived(const FString& Command)
{
    FString Cmd, Args;
    if (!Command.Split(TEXT(" "), &Cmd, &Args))
    {
        Cmd = Command;
    }

    ExecuteConsoleCommand(Cmd.ToLower(), Args);
}

void UGameConsoleWidget::RegisterConsoleCommands()
{
    // Commands are registered and handled in ExecuteConsoleCommand
}

void UGameConsoleWidget::ExecuteConsoleCommand(const FString& CommandName, const FString& Args)
{
    if (CommandName == TEXT("help"))
    {
        AddOutputLine(TEXT("Available commands:"));
        AddOutputLine(TEXT("  help - Show this message"));
        AddOutputLine(TEXT("  quit - Exit the game"));
        AddOutputLine(TEXT("  fps - Toggle FPS display"));
    }
    else if (CommandName == TEXT("quit"))
    {
        AddOutputLine(TEXT("Quitting game..."));
        UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
    }
    else if (CommandName == TEXT("fps"))
    {
        // Toggle FPS display
        GEngine->Exec(GetWorld(), TEXT("stat fps"));
        AddOutputLine(TEXT("Toggled FPS display"));
    }
    else
    {
        AddOutputLine(FString::Printf(TEXT("Unknown command: %s"), *CommandName));
    }
}
```

## Key Features Demonstrated

1. **Command Parsing**: Splitting commands and arguments
2. **Command History**: Automatic history navigation with arrow keys
3. **Event Handling**: Using delegates and events for command execution
4. **Output Management**: Adding lines and clearing output
5. **Integration**: Both C++ and Blueprint usage patterns
6. **CommonUI**: Game console implementation using CommonUI

## Tips

- Use `MaxHistoryLines` to control memory usage in long-running sessions
- Bind `OnTerminalCleared` to reset any related state
- Consider implementing command auto-completion for better UX
- Use different font sizes for different contexts (in-game console vs debug terminal)
