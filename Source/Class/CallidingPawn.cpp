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

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); //Sphere ������Ʈ ����
	RootComponent = SphereComponent; //������ ���Ǿ� ������Ʈ�� ��Ʈ ������Ʈ�� ����
	SphereComponent->InitSphereRadius(40.0f); // ó�� ũ��
	SphereComponent->SetCollisionProfileName(TEXT("Pawn")); //�ݸ����������� �̸� �浹������
	

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation")); //���¾����ֱ� ����
	SphereVisual->SetupAttachment(RootComponent); //��Ʈ������Ʈ�� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StaterContents/Shapes/Shape_Sphere.Shape_Sphere")); //��ü ã�ƿ� ������ֱ�
	if (SphereVisualAsset.Succeeded()) //load ���� ��
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);//���־��� ������ sphereVisualasset���� ����
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f)); //��ġ����
		SphereVisual->SetWorldScale3D(FVector(0.8f)); //ũ�⼳��
	}

	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("OurParticleSystem"));
	OurParticleSystem->SetupAttachment(RootComponent);
	OurParticleSystem->bAutoActivate = false; //���۵ɶ� �ڵ����� �����°� ����
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f)); // ��ġ����
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire")); //��ƼŬ���� ã�ƿ� �ҷ��ֱ�
	if (ParticleAsset.Succeeded()) //�����ϸ�
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object); //System�� �־���
	}

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm")); //ī�޶� ĳ���ͺ��� �ణ �ʰ� ���󰡰�, ���ձ� ����
	SpringArm->SetupAttachment(RootComponent); 
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); //��������
	SpringArm->TargetArmLength = 400.0f; //Ÿ�ٰ��ǰŸ�
	SpringArm->bEnableCameraLag = true; //õõ�� ���󰡱�
	SpringArm->CameraLagSpeed = 3.0f; // ���󰡴� �ӵ�

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera")); //�������Ͽ� ������ ī�޶�
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); //�ι����Ű������� ī�޶� �������Ͽ� ����� ���Ͽ� ���� �� ����

	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("OurMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

	AutoPossessPlayer = EAutoReceiveInput::Player0; // �⺻�÷��̾ �����ϵ��� ����

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