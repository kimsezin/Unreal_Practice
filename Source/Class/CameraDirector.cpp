// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2;
	const float SmoothBlendTime = 0.75;

	TimeToNextCamerChange -= DeltaTime;
	if (TimeToNextCamerChange <= 0)
	{
		FChangeCameraData NowCamera = Cameras[NowCameraIndex];

		TimeToNextCamerChange += NowCamera.TimeBetweenCameraChanges;
	
		//ī�޶� ��ȯ �ڵ�
		APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);//�����÷��̾��� ��Ʈ���� ó���ϴ� ���� ã��
																					   //controller������ �÷��̾� ��Ʈ�ѷ� ����
		if (controller)
		{
			if ((controller->GetViewTarget() != NowCamera.Camera) && (NowCamera.Camera != nullptr)) // ����ٶ󺸴� Ÿ���� CameraOne�� �ƴ� ��
			{
				if (NowCamera.SmoothBlendTime <= 0)
				{
					controller->SetViewTarget(NowCamera.Camera); //Ÿ���� CameraOne���� ����
				}
				else
				{
					controller->SetViewTargetWithBlend(NowCamera.Camera, NowCamera.SmoothBlendTime);
				}
			}

			//if ((controller->GetViewTarget() != CameraOne) && (CameraOne != nullptr)) // ����ٶ󺸴� Ÿ���� CameraOne�� �ƴ� ��
			//{
			//	controller->SetViewTarget(CameraOne); //Ÿ���� CameraOne���� ����
			//}
			
			//else if ((controller->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			//{
			//	controller->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime); //ī�޶� 2�� ī�޶�� ����													
			//																	//SetViewTargetWithBlend�Լ��� ī�޶� ��ȯ �� �ٷ� �� ����, �̵���Ű�鼭 ������ ���� ����
			//}
		}
		NowCameraIndex++;
		if (NowCameraIndex >= Cameras.Num())
		{
			NowCameraIndex = 0;
		}
	}

}

