// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputAction(const FGameplayTag& TargetTag, bool bLogNotFound) const
{
	for(FAuraInputAction AuraInputAction : AuraInputActions)
	{
		if(AuraInputAction.InputAction && AuraInputAction.InputTag.MatchesTagExact(TargetTag))
			return AuraInputAction.InputAction;
	}
	if(bLogNotFound)
		UE_LOG(LogTemp, Warning, TEXT("Tag not found"));
	return nullptr;
}
