// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "IntetFace/EnemyInterface.h"
#include "BTT_SetMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class ENEMYAI_API UBTT_SetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_SetMovementSpeed();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	// 에디터에서 설정할 이동 상태 (예: Idle, Walking, Sprint)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EEnemySpeed MovementState;
};
