// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Data/EnumBase.h"
#include "MyAIController.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Damage;
/**
 * 
 */
UCLASS()
class ENEMYAI_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
    AMyAIController();
protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

public:
    // 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UAIPerceptionComponent* AIPerceptionComp;

    class UAISenseConfig_Sight* SightConfig;
    class UAISenseConfig_Damage* DamageConfig;

    // 블랙보드 키 이름 (오타 방지용)
    const FName Key_State = FName("State");
    const FName Key_Target = FName("AttackTarget"); // 스크린샷의 AttackTarget

    // -- 헬퍼 함수 --
    EEnemyState GetCurrentState() const;
    void SetStateAsAttack(AActor* TargetActor);

    // -- 이벤트 핸들러 --
    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
