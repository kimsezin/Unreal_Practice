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
	
		//카메라 전환 코드
		APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);//로컬플레이어의 컨트롤을 처리하는 액터 찾기
																					   //controller변수에 플레이어 컨트롤러 저장
		if (controller)
		{
			if ((controller->GetViewTarget() != NowCamera.Camera) && (NowCamera.Camera != nullptr)) // 현재바라보는 타겟이 CameraOne이 아닐 시
			{
				if (NowCamera.SmoothBlendTime <= 0)
				{
					controller->SetViewTarget(NowCamera.Camera); //타겟을 CameraOne으로 변경
				}
				else
				{
					controller->SetViewTargetWithBlend(NowCamera.Camera, NowCamera.SmoothBlendTime);
				}
			}

			//if ((controller->GetViewTarget() != CameraOne) && (CameraOne != nullptr)) // 현재바라보는 타겟이 CameraOne이 아닐 시
			//{
			//	controller->SetViewTarget(CameraOne); //타겟을 CameraOne으로 변경
			//}
			
			//else if ((controller->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
			//{
			//	controller->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime); //카메라 2를 카메라로 변경													
			//																	//SetViewTargetWithBlend함수는 카메라 전환 시 바로 컷 할지, 이동시키면서 들어갈지에 대한 선택
			//}
		}
		NowCameraIndex++;
		if (NowCameraIndex >= Cameras.Num())
		{
			NowCameraIndex = 0;
		}
	}

}

