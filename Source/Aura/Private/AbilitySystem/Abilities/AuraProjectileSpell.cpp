// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	const bool isServer = HasAuthority(&ActivationInfo);
	if(!isServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(ActorInfo->AvatarActor);

	if(CombatInterface)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(CombatInterface->GetCombatSocket());
		//TODO:Set projectile Rotation
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			AuraProjectile,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
		//TODO: give the projectile a gameplay effect spec for causing damage

		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
