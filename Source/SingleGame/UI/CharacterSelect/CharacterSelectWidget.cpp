// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"

void UCharacterSelectWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UCharacterSelectWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("GameStart")));

}

void UCharacterSelectWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCharacterSelectWidget::NativeTick(
	const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UCharacterSelectWidget::OnClickStartButton()
{
}

void UCharacterSelectWidget::EnableStartButton(bool Enable)
{
	mStartButton->SetIsEnabled(Enable);
}
