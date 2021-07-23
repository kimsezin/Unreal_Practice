// Fill out your copyright notice in the Description page of Project Settings.


#include "Print_Log.h"
#include "Class.h"
// Sets default values
APrint_Log::APrint_Log()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APrint_Log::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Error, TEXT("Error Message")); //파라미터 : 로그카테고리, 로그 상세 수준, 남길 메시지
	UE_LOG(LogTemp, Warning, TEXT("Warning Message"));
	UE_LOG(LogTemp, Display, TEXT("Display Message"));
	//로그카테고리 : 출력된 로그가 어느 시스템에서 발생한 건지 알려주는 역할
	//LogTemp : 임시로 띄우는 로그
	//Log까지 쓰고 Ctrl + Space 누르면 나옴
	//자기가 직접 만들 수도 있음 해당 프로젝트의 헤더파일, cpp파일에 추가하는것 (Class.h, Class.cpp 참조)
	UE_LOG(MyLogCategory, Log, TEXT("My Category log"));


	//로그 상세 수준 : 로그의 중요한 수준 중요한거 수준마다 보이게, 안보이게가능
	//Fatal : 로그로 항상 콘솔 및 로그파일에 출력되며 비활성화 된 상태에서도 모든 작동을 중단. (가장 치명적 수준)
	//Error : 콘솔 및 로그파일에 출력되며 빨간색으로표시
	//Warning : 콘솔 및 로그파일에 출력되며 로그는 노란색으로 표시
	//Display : 콘솔및 로그파일에 출력
	//Log : 로그파일엔 출력되지만 게임내의 콘솔에서는 출력 X
	//Verbose : 로그파일엔 풀력, 게임 내의 콘솔 X
	//VeryVerbose : 위와같음. 대량로그에 출력

	FString CharacterName = TEXT("Hiwer");
	UE_LOG(LogTemp, Log, TEXT("My Character Name : %s"), *CharacterName);

	bool isAttackable = true;
	UE_LOG(LogTemp, Log, TEXT("Is Attackable ? = %s"), isAttackable ? TEXT("True") : TEXT("False"));

	FVector CharacterPosition = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Position = %s"), *CharacterPosition.ToString());
}

// Called every frame
void APrint_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

