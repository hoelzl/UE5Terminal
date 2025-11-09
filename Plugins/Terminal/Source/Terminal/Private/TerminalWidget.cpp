// Copyright (c) 2025 Matthias Hölzl. Licensed under the MIT License.

#include "TerminalWidget.h"
#include "STerminalWidget.h"

UTerminalWidget::UTerminalWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxHistoryLines = 100;
	FontSize = 10;
}

void UTerminalWidget::AddOutputLine(const FString& Line)
{
	if (TerminalWidget.IsValid())
	{
		TerminalWidget->AddOutputLine(Line);
	}
}

void UTerminalWidget::ClearOutput()
{
	if (TerminalWidget.IsValid())
	{
		TerminalWidget->ClearOutput();
	}
}

void UTerminalWidget::ExecuteCommand(const FString& Command)
{
	if (TerminalWidget.IsValid())
	{
		TerminalWidget->ExecuteCommand(Command);
	}
}

TArray<FString> UTerminalWidget::GetCommandHistory() const
{
	if (TerminalWidget.IsValid())
	{
		return TerminalWidget->GetCommandHistory();
	}
	return TArray<FString>();
}

TArray<FString> UTerminalWidget::GetOutputHistory() const
{
	if (TerminalWidget.IsValid())
	{
		return TerminalWidget->GetOutputHistory();
	}
	return TArray<FString>();
}

TSharedRef<SWidget> UTerminalWidget::RebuildWidget()
{
	TerminalWidget = SNew(STerminalWidget)
		.MaxHistoryLines(MaxHistoryLines)
		.FontSize(FontSize)
		.OnTerminalCleared(this, &UTerminalWidget::HandleTerminalCleared);

	TerminalWidget->OnCommandExecuted.BindUObject(this, &UTerminalWidget::HandleCommandExecuted);

	return TerminalWidget.ToSharedRef();
}

void UTerminalWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	TerminalWidget.Reset();
}

void UTerminalWidget::HandleCommandExecuted(const FString& Command)
{
	OnCommandExecuted.Broadcast(Command);
}

void UTerminalWidget::HandleTerminalCleared()
{
	OnTerminalCleared.Broadcast();
}
