// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TSubclassOf<UGameplayEffect> ProjectileGameplayEffects;
	

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
