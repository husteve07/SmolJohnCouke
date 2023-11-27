// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/AuraEffectActor.h"
#include "Components/StaticMeshComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "NavigationSystemTypes.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

FGameplayEffectSpecHandle AAuraEffectActor::CreateGameplayEffectSpecHandle(AActor* TargetActor, TSubclassOf<UGameplayEffect>& GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = GetAbilitySystemComponent(TargetActor);
	if(TargetASC == nullptr) return nullptr;
	check(GameplayEffectClass);
	
	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetASC->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);

	return TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, GameplayEffectContextHandle);
	
}
UAbilitySystemComponent* AAuraEffectActor::GetAbilitySystemComponent(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	return TargetASC;
}


void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = GetAbilitySystemComponent(TargetActor);
	if(TargetASC)
	{
		FGameplayEffectSpecHandle GameplayEffectSpecHandle = CreateGameplayEffectSpecHandle(TargetActor, GameplayEffectClass);

		FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

		const bool bIsInfinite = GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
		if(bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemovalOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
		}
		
	}
	
}

EGameplayEffectDurationType AAuraEffectActor::GetGamePlayEffectDurationType(AActor* TargetActor, TSubclassOf<UGameplayEffect>& GameplayEffectClass)
{
	return CreateGameplayEffectSpecHandle(TargetActor, GameplayEffectClass).Data.Get()->Def.Get()->DurationPolicy;
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	for(TSubclassOf<UGameplayEffect>& GamePlayEffectClass : MultipleDurationGameplayEffect)
	{
		if(GetGamePlayEffectDurationType(TargetActor, GamePlayEffectClass) == EGameplayEffectDurationType::Instant &&
			InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, GamePlayEffectClass);
		}

		if(GetGamePlayEffectDurationType(TargetActor, GamePlayEffectClass) == EGameplayEffectDurationType::HasDuration
			&&DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, GamePlayEffectClass);
		}
		if(GetGamePlayEffectDurationType(TargetActor, GamePlayEffectClass) == EGameplayEffectDurationType::Infinite
			&&InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, GamePlayEffectClass);
		}
		
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for(TSubclassOf<UGameplayEffect>& GamePlayEffectClass : MultipleDurationGameplayEffect)
	{
		if(GetGamePlayEffectDurationType(TargetActor, GamePlayEffectClass) == EGameplayEffectDurationType::Instant &&
			InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
		if(GetGamePlayEffectDurationType(TargetActor, GamePlayEffectClass) == EGameplayEffectDurationType::HasDuration &&
			DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
		if(GetGamePlayEffectDurationType(TargetActor, GamePlayEffectClass) == EGameplayEffectDurationType::Infinite)
		{
			if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::DoNotRemove)
			{
				ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
			}
			if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemovalOnEndOverlap)
			{
				UAbilitySystemComponent* TargetASC = GetAbilitySystemComponent(TargetActor);
				check(TargetASC);

				TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		
				for(TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePairs : ActiveEffectHandles)
				{
					if(TargetASC == HandlePairs.Value)
					{
						TargetASC->RemoveActiveGameplayEffect(HandlePairs.Key, 1);
						HandlesToRemove.Add(HandlePairs.Key);
					}
				}

				for(auto& Handle : HandlesToRemove)
				{
					ActiveEffectHandles.FindAndRemoveChecked(Handle);
				}
			}
		}
	}
}


