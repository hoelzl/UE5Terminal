# UE5Terminal

A terminal window plugin for Unreal Engine 5 that provides a fully-featured terminal widget with Slate, UMG, and CommonUI support.

## Features

- **Slate Terminal Widget (STerminalWidget)**: Core terminal implementation using Slate
- **UMG Wrapper (UTerminalWidget)**: Blueprint-accessible terminal widget for UMG
- **CommonUI Wrapper (UCommonTerminalWidget)**: CommonUI-compatible terminal widget
- Command history navigation with up/down arrow keys
- Customizable font size and history buffer
- Event-driven command execution
- Terminal output display with scrolling

## Installation

1. Copy the `Plugins/Terminal` folder to your Unreal Engine 5 project's `Plugins` directory
2. Regenerate project files
3. Build your project
4. Enable the Terminal plugin in the Plugins menu

## Usage

### Using in C++ (Slate)

```cpp
#include "STerminalWidget.h"

TSharedRef<STerminalWidget> TerminalWidget = SNew(STerminalWidget)
    .MaxHistoryLines(200)
    .FontSize(12);

// Bind to command execution event
TerminalWidget->OnCommandExecuted.BindLambda([](const FString& Command)
{
    UE_LOG(LogTemp, Log, TEXT("Command executed: %s"), *Command);
});

// Add output programmatically
TerminalWidget->AddOutputLine(TEXT("Welcome to the terminal!"));
```

### Using in Blueprints (UMG)

1. Create a UMG Widget Blueprint
2. Add a `Terminal Widget` from the palette
3. Configure `MaxHistoryLines` and `FontSize` in the Details panel
4. Bind to the `OnCommandExecuted` event to handle commands
5. Use `AddOutputLine` to display responses

### Using with CommonUI

1. Create a CommonUI Widget Blueprint
2. Add a `Common Terminal Widget` from the palette
3. Configure properties and bind events as needed

## API Reference

### STerminalWidget (Slate)

- `void AddOutputLine(const FString& Line)` - Add a line to terminal output
- `void ClearOutput()` - Clear all terminal output
- `void ExecuteCommand(const FString& Command)` - Execute a command programmatically
- `TArray<FString> GetCommandHistory()` - Get command history
- `TArray<FString> GetOutputHistory()` - Get output history
- `FOnCommandExecuted OnCommandExecuted` - Event fired when command is executed

### UTerminalWidget (UMG)

- `UFUNCTION AddOutputLine(const FString& Line)` - Add output line (Blueprint callable)
- `UFUNCTION ClearOutput()` - Clear terminal (Blueprint callable)
- `UFUNCTION ExecuteCommand(const FString& Command)` - Execute command (Blueprint callable)
- `UFUNCTION GetCommandHistory()` - Get command history (Blueprint callable)
- `UFUNCTION GetOutputHistory()` - Get output history (Blueprint callable)
- `OnCommandExecuted` - Blueprint event for command execution
- `OnTerminalCleared` - Blueprint event when terminal is cleared

### UCommonTerminalWidget (CommonUI)

Same API as UTerminalWidget, but inherits from `UCommonUserWidget` for CommonUI compatibility.

## Configuration

Both UMG and CommonUI widgets expose the following properties:

- `MaxHistoryLines` (int32, default: 100) - Maximum lines in history buffer
- `FontSize` (int32, default: 10) - Terminal font size

## License

MIT License - See LICENSE file for details

## Credits

Created by Matthias Hölzl
