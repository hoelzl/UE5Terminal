// Copyright (c) 2025 Matthias Hölzl. Licensed under the MIT License.

#include "STerminalWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SBox.h"
#include "Framework/Application/SlateApplication.h"

void STerminalWidget::Construct(const FArguments& InArgs)
{
	MaxHistoryLines = InArgs._MaxHistoryLines;
	FontSize = InArgs._FontSize;
	OnTerminalCleared = InArgs._OnTerminalCleared;
	HistoryNavigationIndex = -1;
	CurrentInputText = TEXT("");

	ChildSlot
	[
		SNew(SVerticalBox)

		// Output area
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor(0.02f, 0.02f, 0.02f, 1.0f))
			.Padding(FMargin(5.0f))
			[
				SNew(SScrollBox)
				.Orientation(Orient_Vertical)
				.ScrollBarAlwaysVisible(false)

				+ SScrollBox::Slot()
				[
					SNew(STextBlock)
					.Text(this, &STerminalWidget::GetOutputText)
					.Font(FCoreStyle::GetDefaultFontStyle("Mono", FontSize))
					.ColorAndOpacity(FLinearColor(0.8f, 0.8f, 0.8f, 1.0f))
				]
			]
		]

		// Input area
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FMargin(0.0f, 2.0f, 0.0f, 0.0f))
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(FMargin(5.0f, 0.0f))
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT(">")))
				.Font(FCoreStyle::GetDefaultFontStyle("Mono", FontSize))
				.ColorAndOpacity(FLinearColor(0.0f, 1.0f, 0.0f, 1.0f))
			]

			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SAssignNew(InputTextBox, SEditableTextBox)
				.Font(FCoreStyle::GetDefaultFontStyle("Mono", FontSize))
				.OnTextCommitted(this, &STerminalWidget::OnInputTextCommitted)
				.OnKeyDownHandler(this, &STerminalWidget::OnInputKeyDown)
			]
		]
	];
}

void STerminalWidget::AddOutputLine(const FString& Line)
{
	OutputHistory.Add(Line);

	// Trim history if needed
	while (OutputHistory.Num() > MaxHistoryLines)
	{
		OutputHistory.RemoveAt(0);
	}
}

void STerminalWidget::ClearOutput()
{
	OutputHistory.Empty();
	CommandHistory.Empty();
	HistoryNavigationIndex = -1;
	CurrentInputText = TEXT("");

	if (OnTerminalCleared.IsBound())
	{
		OnTerminalCleared.Execute();
	}
}

void STerminalWidget::ExecuteCommand(const FString& Command)
{
	if (Command.IsEmpty())
	{
		return;
	}

	// Add command to output
	AddOutputLine(FString::Printf(TEXT("> %s"), *Command));

	// Add to command history
	CommandHistory.Add(Command);
	HistoryNavigationIndex = -1;

	// Trim command history if needed
	while (CommandHistory.Num() > MaxHistoryLines)
	{
		CommandHistory.RemoveAt(0);
	}

	// Execute the command
	if (OnCommandExecuted.IsBound())
	{
		OnCommandExecuted.Execute(Command);
	}
}

void STerminalWidget::OnInputTextCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	if (CommitType == ETextCommit::OnEnter)
	{
		FString Command = Text.ToString();
		ExecuteCommand(Command);

		// Clear the input
		if (InputTextBox.IsValid())
		{
			InputTextBox->SetText(FText::GetEmpty());
		}

		// Reset history navigation
		HistoryNavigationIndex = -1;
		CurrentInputText = TEXT("");
	}
}

FReply STerminalWidget::OnInputKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (CommandHistory.Num() == 0)
	{
		return FReply::Unhandled();
	}

	if (InKeyEvent.GetKey() == EKeys::Up)
	{
		// Navigate to previous command
		if (HistoryNavigationIndex == -1)
		{
			// Store current input
			if (InputTextBox.IsValid())
			{
				CurrentInputText = InputTextBox->GetText().ToString();
			}
			HistoryNavigationIndex = CommandHistory.Num() - 1;
		}
		else if (HistoryNavigationIndex > 0)
		{
			HistoryNavigationIndex--;
		}

		if (InputTextBox.IsValid() && HistoryNavigationIndex >= 0 && HistoryNavigationIndex < CommandHistory.Num())
		{
			InputTextBox->SetText(FText::FromString(CommandHistory[HistoryNavigationIndex]));
		}

		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == EKeys::Down)
	{
		// Navigate to next command
		if (HistoryNavigationIndex != -1)
		{
			HistoryNavigationIndex++;

			if (InputTextBox.IsValid())
			{
				if (HistoryNavigationIndex >= CommandHistory.Num())
				{
					// Restore original input
					InputTextBox->SetText(FText::FromString(CurrentInputText));
					HistoryNavigationIndex = -1;
				}
				else
				{
					InputTextBox->SetText(FText::FromString(CommandHistory[HistoryNavigationIndex]));
				}
			}
		}

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FText STerminalWidget::GetOutputText() const
{
	FString OutputText;
	for (const FString& Line : OutputHistory)
	{
		OutputText += Line + TEXT("\n");
	}
	return FText::FromString(OutputText);
}
