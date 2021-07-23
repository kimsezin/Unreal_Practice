// Fill out your copyright notice in the Description page of Project Settings.


#include "Countdown.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Countdown Text"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);//렌더링 텍스트 위치
	CountdownText->SetWorldSize(150.0f); //렌더링 텍스트 크기 조절
	RootComponent = CountdownText;

	
	CountdownTime = 3;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateTimerDisplay(); // 타이머 디스플레이 보여주기 실행
	GetWorldTimerManager().SetTimer(CountdownTimerhandle, this, &ACountdown::AdvanceTimer, 1.0f, true); // 타이머 설정.
}

void ACountdown::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0))); // CountdownTime 변수에 저장된 타이머값 출력
}

void ACountdown::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay(); //타이머 1초줄이고 보여주기

	if (CountdownTime < 1)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerhandle); //0초되면 타이머 clear
		CountdownHasFinished(); //타이머 끝났을떄 실행하는 함수
	}
}

void ACountdown::CountdownHasFinished_Implementation()
{
	CountdownText->SetText(TEXT("Go !")); //타이머 시간 끝나면 Go! 출력
}

