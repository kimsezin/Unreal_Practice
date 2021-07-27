// Fill out your copyright notice in the Description page of Project Settings.


#include "Korean.h"

// Sets default values
AKorean::AKorean()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	korean = TEXT("한글이 깨짐");
}

// Called when the game starts or when spawned
void AKorean::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKorean::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

