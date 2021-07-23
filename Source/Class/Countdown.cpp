// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Countdown Text"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);//������ �ؽ�Ʈ ��ġ
	CountdownText->SetWorldSize(150.0f); //������ �ؽ�Ʈ ũ�� ����
	RootComponent = CountdownText;

	
	CountdownTime = 3;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateTimerDisplay(); // Ÿ�̸� ���÷��� �����ֱ� ����
	GetWorldTimerManager().SetTimer(CountdownTimerhandle, this, &ACountdown::AdvanceTimer, 1.0f, true); // Ÿ�̸� ����.
}

void ACountdown::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0))); // CountdownTime ������ ����� Ÿ�̸Ӱ� ���
}

void ACountdown::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay(); //Ÿ�̸� 1�����̰� �����ֱ�

	if (CountdownTime < 1)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerhandle); //0�ʵǸ� Ÿ�̸� clear
		CountdownHasFinished(); //Ÿ�̸� �������� �����ϴ� �Լ�
	}
}

void ACountdown::CountdownHasFinished_Implementation()
{
	CountdownText->SetText(TEXT("Go !")); //Ÿ�̸� �ð� ������ Go! ���
}

