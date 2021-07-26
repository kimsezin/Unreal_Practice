// Fill out your copyright notice in the Description page of Project Settings.


#include "TestClass.h"

// Sets default values
ATestClass::ATestClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<APawn> BpClass(TEXT("/Game/StarterContent/Bp_TestClass")); // 블루프린트 클래스 불러오기 꺽새안에 블루프린트 클래스가 상속받는 C++클래스 타입 , 블루프린트 클래스 경로
	if (BpClass.Succeeded() && BpClass.Class != NULL) // 성공적으로 불러와졌는지.
	{
		BpClass.Class->//여기안에있음
	}

	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); // StaticMeshasset에 넣을 StaticmeshComponent불러오기
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone")); //리소스 가져오기
	if (MeshAsset.Succeeded() && MeshAsset.Object != NULL)
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void ATestClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

