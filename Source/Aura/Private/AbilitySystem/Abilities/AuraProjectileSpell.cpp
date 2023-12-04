// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	

}

void UAuraProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	const bool isServer = 	GetOwningActorFromActorInfo()->HasAuthority();

	if(!isServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if(CombatInterface)
	{
		FTransform SpawnTransform;
		FRotator SpawnRotation = (TargetLocation - CombatInterface->GetCombatSocket()).Rotation();
		
		SpawnTransform.SetLocation(CombatInterface->GetCombatSocket());

		//TODO:Set projectile Rotation
		SpawnTransform.SetRotation(SpawnRotation.Quaternion());
		
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			AuraProjectile,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
		//TODO: give the projectile a gameplay effect spec for causing damage

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(ProjectileGameplayEffects, GetAbilityLevel(), SourceASC->MakeEffectContext());
		Projectile->GameplayEffectSpec = SpecHandle;
		
		FAuraGameplayTags AuraGameplayTags = FAuraGameplayTags::Get();

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AuraGameplayTags.Damage, 50.f);

		Projectile->FinishSpawning(SpawnTransform);
	}
}
