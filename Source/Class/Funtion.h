// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Funtion.generated.h"

UCLASS()
class CLASS_API AFuntion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuntion();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Damage")
	float DamagePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	FString str;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void CalculateDPS();

	virtual void PostInitProperties() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	//UFUNCTION(BlueprintImplementableEvent, Category = "Damage") //BlueprintImplementableEvent면 블루프린트에서 내용 써야함.
	UFUNCTION(BlueprintNativeEvent, Category = "Damage")//블루프린트에서 만들지 않으면 cpp내에서 만들 수 있음
	void CallFromCpp();
	virtual void CallFromCpp_Implementation();
	
};
