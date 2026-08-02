#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BeltScrollDamageable.generated.h"

class AActor;

UINTERFACE(MinimalAPI, Blueprintable)
class UBeltScrollDamageable : public UInterface
{
    GENERATED_BODY()
};

/**
 * Implement this interface on actors that can receive a player attack
 */
class BELTSCROLLACTION_API IBeltScrollDamageable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    void ReceiveAttack(float Damage, AActor* DamageCauser, const FVector& impactPoint);
};