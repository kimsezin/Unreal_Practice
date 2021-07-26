// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) //PawnOwner:컴포넌트를 소유하고있는 Pawn / UpdateComponent:이 무브먼트 컴포넌트가 이동시키고 업데이트해야할 컴포넌트
																		//ShouldSkipUpdate:생성된 컴포넌트가 이동할 수 없거나 렌더링 할 수 있는지 알려주는 함수(이동가능한 상태인지)
	{
		return;
	}

	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f; //입력된 이동벡터 가져옴
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(),true,Hit); // 언리얼엔진을 이용해 장애물을 피해 pawnmovement 컴포넌트를 이동시켜줌

		if (Hit.IsValidBlockingHit()) // 컴포넌트가 이동하다 충돌 발생 시
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.0 - Hit.Time, Hit.Normal, Hit); //제자리에 멈추는 대신 표면 타고 미끄러지듯이..
		}
	}
}