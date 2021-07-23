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

void AFuntion::PostInitProperties() //프로퍼티가 초기화 되면 실행되는 함수 Actor안에 있어서 상속받아 virtual과 override를 씀.
{
	Super::PostInitProperties(); // 상속받은 부모 클래스에있는 함수를 가져오는데 쓰는 키워드 Super 부모 클래스에있던걸 한번 호출해주는게 좋음.
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
