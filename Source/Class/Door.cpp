// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh")); //UStaticMeshComponent
	RootComponent = DoorMesh; //Root Component로 지정

	CloseTime = 3.0f; // 문 닫히는 시간
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	OriginRotation = GetActorRotation();
	GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::Open, 0.03f, true); //Door클래스의 Open함수를 0.03초 간격으로 반복해서 호출
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorDeltaTime += DeltaTime;

}

void ADoor::Open()
{
	if (!bOpen)// 문이 열리지 않은 상태
	{
		bOpen = true;
		DoorDeltaTime = 0.0f;
	}

	FRotator rotation = GetActorRotation(); //Actor의 회전상태 가져옴
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(0.0f, 90.0f, DoorDeltaTime), 0.0f); //DoorDeltaTime의 값에 따라 열린 상태로 문을 회전시키고
	SetActorRotation(rotation);
	if (DoorDeltaTime > 1.0f) // DoorDeltaTime의 값이 1보다 커지면
	{
		GetWorldTimerManager().ClearTimer(DoorTimerHandle); // 현재 작동중인 타이머 멈추기
		GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::Close, 0.03f, true, CloseTime); // 문닫기
	}

}

void ADoor::Close()
{
	if (bOpen)
	{
		bOpen = false;
		DoorDeltaTime = 0.0f;
	}
	FRotator rotation = GetActorRotation(); //Actor의 회전상태 가져옴
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(90.0f, 0.0f, DoorDeltaTime), 0.0f); //DoorDeltaTime의 값에 따라 닫힌 상태로 문을 회전시키고
	SetActorRotation(rotation);
	if (DoorDeltaTime > 1.0f) // DoorDeltaTime의 값이 1보다 커지면
	{
		GetWorldTimerManager().ClearTimer(DoorTimerHandle); // 현재 작동중인 타이머 멈추기
	}
}
