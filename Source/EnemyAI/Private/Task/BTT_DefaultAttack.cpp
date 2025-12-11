// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTT_DefaultAttack.h"
#include "AIController.h"
#include "Enemy/EnemyCharacter.h"

UBTT_DefaultAttack::UBTT_DefaultAttack()
{
    //노드에 표시할 이름 (다른 태스크도 같음 이름만 다름)
    NodeName = "DefaultAttack"; 
}

EBTNodeResult::Type UBTT_DefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //컨트롤러와 에너미 캐릭터 받아와서 에너미 캐릭터에 있는 함수 호출, 다른 태스크도 동일 
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC) return EBTNodeResult::Failed;

    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIC->GetPawn());
    if (!Enemy) return EBTNodeResult::Failed;

    // 캐릭터의 WieldSword 함수 호출
    Enemy->DefaultAttack();

    return EBTNodeResult::Succeeded;
}
