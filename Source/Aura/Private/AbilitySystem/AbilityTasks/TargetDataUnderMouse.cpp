// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	FHitResult HitResult;
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	MouseTargetDataDelegate.Broadcast(HitResult.Location);
}
