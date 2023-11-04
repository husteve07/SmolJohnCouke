// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/AuraEffectActor.h"
#include "Components/StaticMeshComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMesh);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(GetRootComponent());
}




void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GEngine)GEngine->AddOnScreenDebugMessage(0, 30.f, FColor::Red, FString("begin overlap"));
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		if(GEngine)GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, FString("Picked Up potion"));
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* MutableAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	if(GEngine)GEngine->AddOnScreenDebugMessage(2, 30.f, FColor::Red, FString("begin play"));

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}



