// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyCharacter.h"

AMyAIController::AMyAIController()
{
    // 1. Perception 컴포넌트 생성
    AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
    SetPerceptionComponent(*AIPerceptionComp);

    // 2. 시각(Sight) 설정
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 1000.0f;
    SightConfig->LoseSightRadius = 1200.0f;
    SightConfig->PeripheralVisionAngleDegrees = 60.0f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    AIPerceptionComp->ConfigureSense(*SightConfig);

    // 3. 피격(Damage) 설정 (스크린샷의 SenseHit 대응)
    DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
    AIPerceptionComp->ConfigureSense(*DamageConfig);

    // 지배적 감각 설정
    AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();
    // 델리게이트 바인딩 (블루프린트의 OnTargetPerceptionUpdated 이벤트와 동일)
    if (AIPerceptionComp)
    {
        AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetPerceptionUpdated);
    }
}

void AMyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // BT 실행 (캐릭터나 컨트롤러에 BT가 할당되어 있다고 가정)
    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn);
    // 참고: 실제로는 Enemy->BehaviorTreeAsset 등을 가져와서 RunBehaviorTree 해야 함.
}

EEnemyState AMyAIController::GetCurrentState() const
{
    if (Blackboard)
    {
        return (EEnemyState)Blackboard->GetValueAsEnum(Key_State);
    }
    return EEnemyState::Patrol;
}

void AMyAIController::SetStateAsAttack(AActor* TargetActor)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsObject(Key_Target, TargetActor);
        Blackboard->SetValueAsEnum(Key_State, (uint8)EEnemyState::Attack);
    }
}

void AMyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    // 1. 플레이어인지 확인
    ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (Actor != PlayerChar) return;

    // 2. 감각이 성공적으로 감지되었는지 확인 (Sensed)
    if (!Stimulus.WasSuccessfullySensed()) return;

    // 3. 현재 상태 확인
    EEnemyState CurrentState = GetCurrentState();

    // 4. 로직 분기 (Switch on E_State)
    // Idle이나 Patrol 상태일 때만 Attack으로 전환
    if (CurrentState == EEnemyState::Idle || CurrentState == EEnemyState::Patrol)
    {
        // 시각(Sight) 혹은 데미지(Damage) 인지 확인
        // (스크린샷에서는 둘 다 비슷하게 처리하므로 통합했습니다)
        SetStateAsAttack(Actor);
    }
    // 이미 Attack, Die, Hit 상태라면 무시
}
