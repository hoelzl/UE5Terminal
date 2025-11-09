// Copyright (c) 2025 Matthias Hölzl. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonTerminalWidget.generated.h"

class STerminalWidget;

/**
 * CommonUI wrapper for the Slate terminal widget
 */
UCLASS()
class TERMINAL_API UCommonTerminalWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UCommonTerminalWidget(const FObjectInitializer& ObjectInitializer);

	/** Maximum number of lines to keep in history */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal")
	int32 MaxHistoryLines;

	/** Font size for the terminal text */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Terminal")
	int32 FontSize;

	/** Add a line of text to the terminal output */
	UFUNCTION(BlueprintCallable, Category = "Terminal")
	void AddOutputLine(const FString& Line);

	/** Clear all terminal output */
	UFUNCTION(BlueprintCallable, Category = "Terminal")
	void ClearOutput();

	/** Execute a command programmatically */
	UFUNCTION(BlueprintCallable, Category = "Terminal")
	void ExecuteCommand(const FString& Command);

	/** Get the command history */
	UFUNCTION(BlueprintCallable, Category = "Terminal")
	TArray<FString> GetCommandHistory() const;

	/** Get the output history */
	UFUNCTION(BlueprintCallable, Category = "Terminal")
	TArray<FString> GetOutputHistory() const;

	/** Event called when a command is executed */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCommandExecutedEvent, const FString&, Command);

	UPROPERTY(BlueprintAssignable, Category = "Terminal|Events")
	FOnCommandExecutedEvent OnCommandExecuted;

	/** Event called when terminal is cleared */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTerminalClearedEvent);

	UPROPERTY(BlueprintAssignable, Category = "Terminal|Events")
	FOnTerminalClearedEvent OnTerminalCleared;

protected:
	// UUserWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UUserWidget interface

private:
	/** Handle command execution from the Slate widget */
	void HandleCommandExecuted(const FString& Command);

	/** Handle terminal cleared event */
	void HandleTerminalCleared();

	/** Pointer to the underlying Slate widget */
	TSharedPtr<STerminalWidget> TerminalWidget;
};
