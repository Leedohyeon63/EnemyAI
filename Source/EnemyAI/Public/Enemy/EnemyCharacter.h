// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/EnumBase.h"
#include "Intetface/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ENEMYAI_API AEnemyCharacter : public ACharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
    // 무기 클래스 (블루프린트에서 할당)
    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<AActor> WeaponClass;

    // 현재 무기 인스턴스
    UPROPERTY(VisibleAnywhere, Category = "Combat")
    AActor* CurrentWeapon;

    // 공격 애니메이션
    UPROPERTY(EditAnywhere, Category = "Combat")
    UAnimMontage* AttackMontage;

    // 소켓 이름
    UPROPERTY(EditAnywhere, Category = "Combat")
    FName WeaponSocketName = TEXT("RHandSoket");

    // 상태 확인용 변수 (BT 데코레이터용)
    UPROPERTY(BlueprintReadWrite, Category = "Combat")
    bool bIsWieldingWeapon;

    // -- 함수들 --
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void WieldSword();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void DefaultAttack();



    UFUNCTION(BlueprintCallable, Category = "Movement")
    void UpdateMovementSpeed(float NewSpeed);

    virtual float SetMovementSpeed_Implementation(EEnemySpeed State) override;
};
