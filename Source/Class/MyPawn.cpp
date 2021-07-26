// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0; // 게임 시작 후 자동으로 플레이어 입력 연결

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")); //RootComponent에 저장

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera!!!")); //UCamera 생성
	OurCamera->SetupAttachment(RootComponent); //Root Component에 부착
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f)); //위치
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); //회전

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent")); //카메라가 보이게 하기위함
	OurVisibleComponent->SetupAttachment(RootComponent); //Root Component에 부착
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
		float CurrentScale = OurVisibleComponent->GetComponentScale().X; //컴포넌트 크기 가져오기
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
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f); // Clamp함수로 1.0f ~ 2.0f로 제한
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale)); // 컴포넌트 크기지정
	}

	{
		if (!CurrentVelocity.IsZero()) // 입력이 들어오는 동안
		{
			InputTime += DeltaTime;
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime * (InputTime <= 1.0f ? 1.0f : 3.0f)); //이동
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

	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing); // 함수와 입력을 연결하는것을 바인딩한다고함.
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);

}

void AMyPawn::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f; // -1 ~ 1 로 제한 후 100을 곱함. w키와 위쪽 화살표 두키를 동시에누르면 두 값이 동시에 합산되기 때문에 Clamp를 쓰면 버그 발생 제한
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f; // -1 ~ 1 로 제한 후 100을 곱함. w키와 위쪽 화살표 두키를 동시에누르면 두 값이 동시에 합산되기 때문에 Clamp를 쓰면 버그 발생 제한
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}
void AMyPawn::StopGrowing()
{
	bGrowing = false;
}