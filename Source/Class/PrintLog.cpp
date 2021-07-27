// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintLog.h"
#include <Kismet/KismetSystemLibrary.h> //로그창에 나오게하기위함

// Sets default values
APrintLog::APrintLog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APrintLog::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrintLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Hello 2")); //레벨에 보이는 프린트로그
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Hello 3"), true, true, FLinearColor::Green, 2.0f);
}

