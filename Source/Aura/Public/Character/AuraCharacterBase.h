// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual FVector GetCombatSocket() override;

protected:

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;
	
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Combat")
	FName CombatSocketName;
	
	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level) const;

	void InitializeDefaultAttributes() const;

	virtual void InitAbilityActorInfo();

	void InitializeVitalAttributes() const;

	virtual void AddCharacterAbilities();
	
private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CharacterAbilities;
	
};
