// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0; // ���� ���� �� �ڵ����� �÷��̾� �Է� ����

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")); //RootComponent�� ����

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera!!!")); //UCamera ����
	OurCamera->SetupAttachment(RootComponent); //Root Component�� ����
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f)); //��ġ
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); //ȸ��

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent")); //ī�޶� ���̰� �ϱ�����
	OurVisibleComponent->SetupAttachment(RootComponent); //Root Component�� ����
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X; //������Ʈ ũ�� ��������
		if (bGrowing)
		{
			if (InputTime > 0.0f && InputTime <= 0.5f)
			{
				CurrentScale = 2.0f;
			}
			else
			CurrentScale += DeltaTime;
		}
		else
		{
			CurrentScale -= DeltaTime * 0.5f;
		}
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f); // Clamp�Լ��� 1.0f ~ 2.0f�� ����
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale)); // ������Ʈ ũ������
	}

	{
		if (!CurrentVelocity.IsZero()) // �Է��� ������ ����
		{
			InputTime += DeltaTime;
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime * (InputTime <= 1.0f ? 1.0f : 3.0f)); //�̵�
			SetActorLocation(NewLocation);
		}
		else
		{
			InputTime = 0.0f;
		}
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing); // �Լ��� �Է��� �����ϴ°��� ���ε��Ѵٰ���.
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);

}

void AMyPawn::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f; // -1 ~ 1 �� ���� �� 100�� ����. wŰ�� ���� ȭ��ǥ ��Ű�� ���ÿ������� �� ���� ���ÿ� �ջ�Ǳ� ������ Clamp�� ���� ���� �߻� ����
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f; // -1 ~ 1 �� ���� �� 100�� ����. wŰ�� ���� ȭ��ǥ ��Ű�� ���ÿ������� �� ���� ���ÿ� �ջ�Ǳ� ������ Clamp�� ���� ���� �߻� ����
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}
void AMyPawn::StopGrowing()
{
	bGrowing = false;
}