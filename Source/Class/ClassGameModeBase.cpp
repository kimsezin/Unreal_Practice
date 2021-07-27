// Copyright Epic Games, Inc. All Rights Reserved.


#include "ClassGameModeBase.h"
#include <Blueprint/UserWidget.h>

void AClassGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);

}

void AClassGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr) //위젯이 비어있지않으면
	{
		CurrentWidget->RemoveFromViewport(); //화면에서 UI 지우고 위젯비우기
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass); //새 위겟 만들어 저장 후
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport(); //뷰포트에 보이게하기
		}
	}
}