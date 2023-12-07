// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Exec_CalcDamage.generated.h"

/**
 * 
 */



UCLASS()
class AURA_API UExec_CalcDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExec_CalcDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
