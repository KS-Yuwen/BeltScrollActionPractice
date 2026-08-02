#include "AnimNotify_AttackTrace.h"
#include "BeltScrollActionCharacter.h"
#include "Components/SkeletalMeshComponent.h"

void UAnimNotify_AttackTrace::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (!MeshComp)
    {
        return;
    }

    if (ABeltScrollActionCharacter *Character = Cast<ABeltScrollActionCharacter>(MeshComp->GetOwner()))
    {
        Character->DoAttackTrace();
    }
}