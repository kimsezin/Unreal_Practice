// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/Classes/Components/TextRenderComponent.h>
#include "Countdown.generated.h"

UCLASS()
class CLASS_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	//How long, in seconds, the countdown will run
	UPROPERTY(EditAnywhere)
	int32 CountdownTime;

	UTextRenderComponent* CountdownText;

	void UpdateTimerDisplay();

	void AdvanceTimer(); //타이머가 돌아가면서 호출될 함수

	UFUNCTION(BlueprintNativeEvent) // 블루프린터에서도 수정 가능
	void CountdownHasFinished(); // 타이머가 정한만큼 동작하고 마무리처리
	virtual void CountdownHasFinished_Implementation(); //블루프린트 처리

	FTimerHandle CountdownTimerhandle; // 타이머를 컨트롤하기위한 구조체
};
