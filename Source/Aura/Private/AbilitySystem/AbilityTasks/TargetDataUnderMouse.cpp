// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"
UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->IsLocallyControlled();
	if(bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		// we are on the server, listen for target data
	}
	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	//Set predicting scope to server
	FScopedPredictionWindow(AbilitySystemComponent.Get());
	
	FHitResult HitResult;
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	//set target data hit result
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = HitResult;

	//Send data to the server
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);
	AbilitySystemComponent->ServerSetReplicatedTargetData(
	GetAbilitySpecHandle(),
	GetActivationPredictionKey(),
	DataHandle,
	FGameplayTag(),
	AbilitySystemComponent->ScopedPredictionKey
	);
	//broadcast data
	if(ShouldBroadcastAbilityTaskDelegates())
		MouseTargetDataDelegate.Broadcast(DataHandle);
}
