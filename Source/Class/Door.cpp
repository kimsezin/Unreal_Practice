// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh")); //UStaticMeshComponent
	RootComponent = DoorMesh; //Root Component�� ����

	CloseTime = 3.0f; // �� ������ �ð�
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	OriginRotation = GetActorRotation();
	GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::Open, 0.03f, true); //DoorŬ������ Open�Լ��� 0.03�� �������� �ݺ��ؼ� ȣ��
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorDeltaTime += DeltaTime;

}

void ADoor::Open()
{
	if (!bOpen)// ���� ������ ���� ����
	{
		bOpen = true;
		DoorDeltaTime = 0.0f;
	}

	FRotator rotation = GetActorRotation(); //Actor�� ȸ������ ������
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(0.0f, 90.0f, DoorDeltaTime), 0.0f); //DoorDeltaTime�� ���� ���� ���� ���·� ���� ȸ����Ű��
	SetActorRotation(rotation);
	if (DoorDeltaTime > 1.0f) // DoorDeltaTime�� ���� 1���� Ŀ����
	{
		GetWorldTimerManager().ClearTimer(DoorTimerHandle); // ���� �۵����� Ÿ�̸� ���߱�
		GetWorldTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::Close, 0.03f, true, CloseTime); // ���ݱ�
	}

}

void ADoor::Close()
{
	if (bOpen)
	{
		bOpen = false;
		DoorDeltaTime = 0.0f;
	}
	FRotator rotation = GetActorRotation(); //Actor�� ȸ������ ������
	rotation = OriginRotation + FRotator(0.0f, FMath::Lerp(90.0f, 0.0f, DoorDeltaTime), 0.0f); //DoorDeltaTime�� ���� ���� ���� ���·� ���� ȸ����Ű��
	SetActorRotation(rotation);
	if (DoorDeltaTime > 1.0f) // DoorDeltaTime�� ���� 1���� Ŀ����
	{
		GetWorldTimerManager().ClearTimer(DoorTimerHandle); // ���� �۵����� Ÿ�̸� ���߱�
	}
}
