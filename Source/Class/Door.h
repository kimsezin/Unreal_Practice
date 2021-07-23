// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/StaticMeshComponent.h>
#include "Door.generated.h"

UCLASS()
class CLASS_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh; //  문 모델링 변수

	UPROPERTY(EditAnywhere)
	float CloseTime; //  열렸다 닫히는 시간

	float DoorDeltaTime; // 열리고 닫히는 과정 표현

	bool bOpen; // 열린 상태 표현

	FTimerHandle DoorTimerHandle; // 타이머 관리 핸들
	
	FRotator OriginRotation; // 문의 원래상태 저장

	void Open();

	void Close();
};
