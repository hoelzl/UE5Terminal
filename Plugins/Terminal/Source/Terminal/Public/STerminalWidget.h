// Copyright (c) 2025 Matthias Hölzl. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SEditableTextBox.h"

/**
 * Slate terminal widget that displays command history and provides an input field
 */
class TERMINAL_API STerminalWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STerminalWidget)
		: _MaxHistoryLines(100)
		, _FontSize(10)
	{}
		SLATE_ARGUMENT(int32, MaxHistoryLines)
		SLATE_ARGUMENT(int32, FontSize)
		SLATE_EVENT(FSimpleDelegate, OnTerminalCleared)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	/** Add a line of text to the terminal output */
	void AddOutputLine(const FString& Line);

	/** Clear all terminal output */
	void ClearOutput();

	/** Execute a command */
	void ExecuteCommand(const FString& Command);

	/** Get the command history */
	TArray<FString> GetCommandHistory() const { return CommandHistory; }

	/** Get the output history */
	TArray<FString> GetOutputHistory() const { return OutputHistory; }

	/** Delegate called when a command is executed */
	DECLARE_DELEGATE_OneParam(FOnCommandExecuted, const FString&);
	FOnCommandExecuted OnCommandExecuted;

private:
	/** Handle text committed in the input box */
	void OnInputTextCommitted(const FText& Text, ETextCommit::Type CommitType);

	/** Handle up/down arrow keys for command history navigation */
	FReply OnInputKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);

	/** Generate the output text */
	FText GetOutputText() const;

	/** Reference to the input text box */
	TSharedPtr<SEditableTextBox> InputTextBox;

	/** Command history */
	TArray<FString> CommandHistory;

	/** Output history */
	TArray<FString> OutputHistory;

	/** Maximum number of history lines to keep */
	int32 MaxHistoryLines;

	/** Current position in command history (-1 means not navigating) */
	int32 HistoryNavigationIndex;

	/** Temporary storage for current input while navigating history */
	FString CurrentInputText;

	/** Font size for the terminal */
	int32 FontSize;

	/** Callback when terminal is cleared */
	FSimpleDelegate OnTerminalCleared;
};
