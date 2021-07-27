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
	if (CurrentWidget != nullptr) //������ �������������
	{
		CurrentWidget->RemoveFromViewport(); //ȭ�鿡�� UI ����� ��������
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass); //�� ���� ����� ���� ��
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport(); //����Ʈ�� ���̰��ϱ�
		}
	}
}