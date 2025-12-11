// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTT_DefaultAttack.h"
#include "AIController.h"
#include "Enemy/EnemyCharacter.h"

UBTT_DefaultAttack::UBTT_DefaultAttack()
{
    NodeName = "DefaultAttack";
}

EBTNodeResult::Type UBTT_DefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC) return EBTNodeResult::Failed;

    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIC->GetPawn());
    if (!Enemy) return EBTNodeResult::Failed;

    // 캐릭터의 WieldSword 함수 호출
    Enemy->DefaultAttack();

    return EBTNodeResult::Succeeded;
}
