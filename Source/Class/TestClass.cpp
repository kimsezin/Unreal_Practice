// Fill out your copyright notice in the Description page of Project Settings.


#include "TestClass.h"

// Sets default values
ATestClass::ATestClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<APawn> BpClass(TEXT("/Game/StarterContent/Bp_TestClass")); // �������Ʈ Ŭ���� �ҷ����� �����ȿ� �������Ʈ Ŭ������ ��ӹ޴� C++Ŭ���� Ÿ�� , �������Ʈ Ŭ���� ���
	if (BpClass.Succeeded() && BpClass.Class != NULL) // ���������� �ҷ���������.
	{
		BpClass.Class->//����ȿ�����
	}

	UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); // StaticMeshasset�� ���� StaticmeshComponent�ҷ�����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone")); //���ҽ� ��������
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

