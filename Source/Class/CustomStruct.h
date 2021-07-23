// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.generated.h" // 헤더파일 추가

/**
 * 
 */
class CLASS_API CustomStruct
{
public:
	CustomStruct();
	~CustomStruct();
};

USTRUCT(Atomic,BlueprintType)
struct FCustomStruct //구조체는 F로 시작해야함
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* actor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 i;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float f;
};