// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"

#include "AssetTypeCategories.h"
#include "GameplayTagsManager.h"
#include "NativeGameplayTags.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{

	//primary attribute
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Primary.Strength", Attributes_Primary_Strength, "Character Strength Attribute, Increases physical Dmg")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Primary.Intelligence", Attributes_Primary_Intelligence, "Character Intelligence Attriut, Increase Magic Dmg and Mana")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Primary.Resilience", Attributes_Primary_Resilience, "Character Resilience Attribute, Increase Armour and Crit")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Primary.Vigor", Attributes_Primary_Vigor, "Character Vigor Attribute, Increases Health ")

	//secondary attribute
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.Armor", Attributes_Secondary_Armor, "Reduces Dmg Taken, Improves Block Chances")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.ArmorPenetration", Attributes_Secondary_ArmorPenetration, "Increase Dmg Against armord enemies")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.BlockChance", Attributes_Secondary_BlockChance, "Improves Block Chances")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.CriticalHitChance", Attributes_Secondary_CriticalHitChance, "Increases crit rate")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.CriticalHitDamage", Attributes_Secondary_CriticalHitDamage, "Increases Crit Damage")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.CriticalHitResistance", Attributes_Secondary_CriticalHitResistance, "Decreases enemy crit dmg")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.HealthRegeneration", Attributes_Secondary_HealthRegeneration, "increase health regen")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.ManaRegeneration", Attributes_Secondary_ManaRegeneration, "increase mana regen")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.MaxHealth", Attributes_Secondary_MaxHealth, "increases max health")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Secondary.MaxMana", Attributes_Secondary_MaxMana, "increases max mana")

	//Input Action abilities
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("InputTag.LMB", InputTag_LMB, "Input Tag for left mouse button")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("InputTag.RMB", InputTag_RMB, "Input Tag for Right mouse button")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("InputTag.1", InputTag_1, "Input Tag for button 1")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("InputTag.2", InputTag_2, "Input Tag for button 2")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("InputTag.3", InputTag_3, "Input Tag for button 3")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("InputTag.4", InputTag_4, "Input Tag for button 4")

	
	//GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces Dmg Taken, improves block Chances"));

	/*
	 *Damage Types
	 */
	
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Damage", Damage, "Damage For Meta Attribute")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Damage.Fire", Damage_Fire, "Fire Damage Type")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Damage.Lightning", Damage_Lightning, "Lightning Damage Type")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Damage.Arcane", Damage_Arcane, "Arcane Damage Type")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Damage.Physical", Damage_Physical, "Physical Damage Type")

/*
 *Damage type resistances
 */
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Resistance.Fire", Attributes_Resistance_Fire, "Fire Damage Type Resistance")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Resistance.Lightning", Attributes_Resistance_Lightning, "Lightning Damage Type Resistance")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Resistance.Arcane", Attributes_Resistance_Arcane, "Arcane Damage Type Resistance")
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Attributes.Resistance.Physical", Attributes_Resistance_Physical, "Physical Damage Type Resistance")

	/*
	 *Map of Damge Types to Resistance
	 */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	/*
	 *effects
	 */
	DEFINE_NATIVE_GAMEPLAY_TAGS_WITH_COMMENT("Effects.HitReact", Effects_HitReact, "Hit reaction")
	
}
