// Fill out your copyright notice in the Description page of Project Settings.


#include "Funtion.h"

// Sets default values
AFuntion::AFuntion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TotalDamage = 200;
	DamageTimeInSeconds = 1.0f;
	str = TEXT("Test");
}

// Called when the game starts or when spawned
void AFuntion::BeginPlay()
{
	Super::BeginPlay();
	CallFromCpp();
	
}

// Called every frame
void AFuntion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AFuntion::CalculateDPS()
{
	DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

void AFuntion::PostInitProperties() //������Ƽ�� �ʱ�ȭ �Ǹ� ����Ǵ� �Լ� Actor�ȿ� �־ ��ӹ޾� virtual�� override�� ��.
{
	Super::PostInitProperties(); // ��ӹ��� �θ� Ŭ�������ִ� �Լ��� �������µ� ���� Ű���� Super �θ� Ŭ�������ִ��� �ѹ� ȣ�����ִ°� ����.
	CalculateDPS();
}

void AFuntion::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateDPS();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AFuntion::CallFromCpp_Implementation()
{
	str.Append(TEXT("_Implementation"));
}
