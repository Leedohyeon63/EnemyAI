 // Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTT_SetMovementSpeed.h"
#include "AIController.h"
#include "Enemy/EnemyCharacter.h"

UBTT_SetMovementSpeed::UBTT_SetMovementSpeed()
{
    // 에디터 노드에 표시될 이름
    NodeName = "Set Movement Speed";

    // 기본값 설정 (선택 사항)
    MovementState = EEnemySpeed::Walking;

}

EBTNodeResult::Type UBTT_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // 1. AI 컨트롤러 가져오기
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!AIC)
    {
        return EBTNodeResult::Failed;
    }

    // 2. 조종 중인 폰(캐릭터) 가져오기
    APawn* ControlledPawn = AIC->GetPawn();
    if (!ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }

    // 3. 인터페이스 구현 여부 확인 및 실행
    // 주의: 인터페이스를 Cast 할 때는 UEnemyInterface를 사용하고, 함수 호출은 IEnemyInterface를 사용합니다.
    if (ControlledPawn->Implements<UEnemyInterface>())
    {
        // BlueprintNativeEvent로 선언된 인터페이스 함수는 'Execute_' 접두사가 붙은 정적 함수로 호출해야 합니다.
        // 첫 번째 인자로 대상 객체(ControlledPawn)를 넘겨줍니다.
        IEnemyInterface::Execute_SetMovementSpeed(ControlledPawn, MovementState);

        return EBTNodeResult::Succeeded;
    }

    // 인터페이스가 없는 캐릭터라면 실패 처리
    return EBTNodeResult::Failed;
}
