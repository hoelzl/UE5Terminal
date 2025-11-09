// Copyright (c) 2025 Matthias Hölzl. Licensed under the MIT License.

#include "CommonTerminalWidget.h"
#include "STerminalWidget.h"

UCommonTerminalWidget::UCommonTerminalWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MaxHistoryLines = 100;
	FontSize = 10;
}

void UCommonTerminalWidget::AddOutputLine(const FString& Line)
{
	if (TerminalWidget.IsValid())
	{
		TerminalWidget->AddOutputLine(Line);
	}
}

void UCommonTerminalWidget::ClearOutput()
{
	if (TerminalWidget.IsValid())
	{
		TerminalWidget->ClearOutput();
	}
}

void UCommonTerminalWidget::ExecuteCommand(const FString& Command)
{
	if (TerminalWidget.IsValid())
	{
		TerminalWidget->ExecuteCommand(Command);
	}
}

TArray<FString> UCommonTerminalWidget::GetCommandHistory() const
{
	if (TerminalWidget.IsValid())
	{
		return TerminalWidget->GetCommandHistory();
	}
	return TArray<FString>();
}

TArray<FString> UCommonTerminalWidget::GetOutputHistory() const
{
	if (TerminalWidget.IsValid())
	{
		return TerminalWidget->GetOutputHistory();
	}
	return TArray<FString>();
}

TSharedRef<SWidget> UCommonTerminalWidget::RebuildWidget()
{
	TerminalWidget = SNew(STerminalWidget)
		.MaxHistoryLines(MaxHistoryLines)
		.FontSize(FontSize)
		.OnTerminalCleared(this, &UCommonTerminalWidget::HandleTerminalCleared);

	TerminalWidget->OnCommandExecuted.BindUObject(this, &UCommonTerminalWidget::HandleCommandExecuted);

	return TerminalWidget.ToSharedRef();
}

void UCommonTerminalWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	TerminalWidget.Reset();
}

void UCommonTerminalWidget::HandleCommandExecuted(const FString& Command)
{
	OnCommandExecuted.Broadcast(Command);
}

void UCommonTerminalWidget::HandleTerminalCleared()
{
	OnTerminalCleared.Broadcast();
}
