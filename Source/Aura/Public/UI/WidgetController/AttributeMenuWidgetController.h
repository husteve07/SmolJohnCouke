// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo, Info);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;

	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attribute")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditAnywhere, Category="GAS|Attribute")
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadCastAttributeInfo(const FGameplayTag AttributeTag, const FGameplayAttribute GameplayAttribute) const;
};
