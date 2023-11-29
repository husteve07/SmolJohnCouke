

#include "Character/AuraCharacterBase.h"

#include "ShaderPrintParameters.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Widgets/Text/ISlateEditableTextWidget.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponSkeletalMesh");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AAuraCharacterBase::GetCombatSocket()
{
	return WeaponMesh->GetSocketLocation(CombatSocketName);
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GamePlayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GamePlayEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GamePlayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);	
}



void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::InitializeVitalAttributes() const
{

}

void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
	if(!HasAuthority()) return;
	ASC->AddCharacterAbilities(CharacterAbilities);
	
}



