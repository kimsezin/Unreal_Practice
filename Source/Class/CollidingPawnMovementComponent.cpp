// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) //PawnOwner:������Ʈ�� �����ϰ��ִ� Pawn / UpdateComponent:�� �����Ʈ ������Ʈ�� �̵���Ű�� ������Ʈ�ؾ��� ������Ʈ
																		//ShouldSkipUpdate:������ ������Ʈ�� �̵��� �� ���ų� ������ �� �� �ִ��� �˷��ִ� �Լ�(�̵������� ��������)
	{
		return;
	}

	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f; //�Էµ� �̵����� ������
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(),true,Hit); // �𸮾����� �̿��� ��ֹ��� ���� pawnmovement ������Ʈ�� �̵�������

		if (Hit.IsValidBlockingHit()) // ������Ʈ�� �̵��ϴ� �浹 �߻� ��
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.0 - Hit.Time, Hit.Normal, Hit); //���ڸ��� ���ߴ� ��� ǥ�� Ÿ�� �̲���������..
		}
	}
}