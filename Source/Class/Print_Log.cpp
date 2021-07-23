// Fill out your copyright notice in the Description page of Project Settings.


#include "Print_Log.h"
#include "Class.h"
// Sets default values
APrint_Log::APrint_Log()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APrint_Log::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Error, TEXT("Error Message")); //�Ķ���� : �α�ī�װ�, �α� �� ����, ���� �޽���
	UE_LOG(LogTemp, Warning, TEXT("Warning Message"));
	UE_LOG(LogTemp, Display, TEXT("Display Message"));
	//�α�ī�װ� : ��µ� �αװ� ��� �ý��ۿ��� �߻��� ���� �˷��ִ� ����
	//LogTemp : �ӽ÷� ���� �α�
	//Log���� ���� Ctrl + Space ������ ����
	//�ڱⰡ ���� ���� ���� ���� �ش� ������Ʈ�� �������, cpp���Ͽ� �߰��ϴ°� (Class.h, Class.cpp ����)
	UE_LOG(MyLogCategory, Log, TEXT("My Category log"));


	//�α� �� ���� : �α��� �߿��� ���� �߿��Ѱ� ���ظ��� ���̰�, �Ⱥ��̰԰���
	//Fatal : �α׷� �׻� �ܼ� �� �α����Ͽ� ��µǸ� ��Ȱ��ȭ �� ���¿����� ��� �۵��� �ߴ�. (���� ġ���� ����)
	//Error : �ܼ� �� �α����Ͽ� ��µǸ� ����������ǥ��
	//Warning : �ܼ� �� �α����Ͽ� ��µǸ� �α״� ��������� ǥ��
	//Display : �ֹܼ� �α����Ͽ� ���
	//Log : �α����Ͽ� ��µ����� ���ӳ��� �ֿܼ����� ��� X
	//Verbose : �α����Ͽ� Ǯ��, ���� ���� �ܼ� X
	//VeryVerbose : ���Ͱ���. �뷮�α׿� ���

	FString CharacterName = TEXT("Hiwer");
	UE_LOG(LogTemp, Log, TEXT("My Character Name : %s"), *CharacterName);

	bool isAttackable = true;
	UE_LOG(LogTemp, Log, TEXT("Is Attackable ? = %s"), isAttackable ? TEXT("True") : TEXT("False"));

	FVector CharacterPosition = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Position = %s"), *CharacterPosition.ToString());
}

// Called every frame
void APrint_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

