// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Korean.generated.h"

UCLASS()
class CLASS_API AKorean : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKorean();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//한글 쓰는법
	UPROPERTY(EditAnywhere)
		FString korean;
};
