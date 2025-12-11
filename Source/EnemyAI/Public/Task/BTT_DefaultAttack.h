// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_DefaultAttack.generated.h"
//태스크는 전부 플레이어 안에 있는 함수 호출하는 방식, 거의 같음, 그래서 다른 태스크는 주석 없음
/**
 * 
 */
UCLASS()
class ENEMYAI_API UBTT_DefaultAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_DefaultAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
