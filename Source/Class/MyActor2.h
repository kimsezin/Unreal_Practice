// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor2.generated.h"

UCLASS()
class CLASS_API AMyActor2 : public AActor
{
	GENERATED_BODY()
	
public:	//전체
	// Sets default values for this actor's properties
	AMyActor2();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient,Category="Damage")
	float DamagePerSecond;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAttackable;


protected: // 상속받은애들만
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
