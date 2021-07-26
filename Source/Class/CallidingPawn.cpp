// Fill out your copyright notice in the Description page of Project Settings.


#include "CallidingPawn.h"
#include "CollidingPawnMovementComponent.h"
#include <Engine/Classes/Components/SphereComponent.h>
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include <Engine/Classes/Particles/ParticleSystemComponent.h>
#include <Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
ACallidingPawn::ACallidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); //Sphere 컴포넌트 생성
	RootComponent = SphereComponent; //생성한 스피어 컴포넌트를 루트 컴포넌트로 지정
	SphereComponent->InitSphereRadius(40.0f); // 처음 크기
	SphereComponent->SetCollisionProfileName(TEXT("Pawn")); //콜리전프로파일 이름 충돌감지용
	

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation")); //형태씌워주기 위함
	SphereVisual->SetupAttachment(RootComponent); //루트컴포넌트에 부착
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StaterContents/Shapes/Shape_Sphere.Shape_Sphere")); //구체 찾아와 만들어주기
	if (SphereVisualAsset.Succeeded()) //load 성공 시
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);//비주얼을 가져온 sphereVisualasset으로 설정
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f)); //위치설정
		SphereVisual->SetWorldScale3D(FVector(0.8f)); //크기설정
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OurParticleSystem"));
	OurParticleSystem->SetupAttachment(RootComponent);
	OurParticleSystem->bAutoActivate = false; //시작될때 자동으로 켜지는거 방지
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f)); // 위치조절
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire")); //파티클에셋 찾아와 불러주기
	if (ParticleAsset.Succeeded()) //성공하면
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object); //System에 넣어줌
	}

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm")); //카메라가 캐릭터보다 약간 늦게 따라가게, 벽뚫기 예방
	SpringArm->SetupAttachment(RootComponent); 
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); //각도조절
	SpringArm->TargetArmLength = 400.0f; //타겟과의거리
	SpringArm->bEnableCameraLag = true; //천천히 따라가기
	SpringArm->CameraLagSpeed = 3.0f; // 따라가는 속도

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera")); //스프링암에 부착할 카메라
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); //두번쨰매개변수는 카메라를 스프링암에 내장된 소켓에 붙일 수 있음

	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("OurMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

	AutoPossessPlayer = EAutoReceiveInput::Player0; // 기본플레이어가 조종하도록 설정

}

// Called when the game starts or when spawned
void ACallidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACallidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACallidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACallidingPawn::ParticleToggle);

	InputComponent->BindAxis("MoveForward", this, &ACallidingPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACallidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACallidingPawn::Turn);
}

UPawnMovementComponent* ACallidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACallidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACallidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACallidingPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

void ACallidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}