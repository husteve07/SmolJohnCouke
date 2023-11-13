// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	Intelligence.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	Intelligence.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	Intelligence.bSnapshot = false;

	RelevantAttributesToCapture.Add(Intelligence);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float IntelligenceValue = 0.f;
	GetCapturedAttributeMagnitude(Intelligence, Spec, EvaluateParameters, IntelligenceValue);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f+2.5f*IntelligenceValue + 15.f * PlayerLevel;
	
}
