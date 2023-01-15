#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"

// Oskrad
#include "OskradCharacter.h"

// Gen
#include "OskradUnit.generated.h"

// TODO [RCH]: This should probably just inherit from APawn, but ACharacters provides a lot of features for free, so we keep it this way for now
UCLASS()
class AOskradUnitBase : public AOskradCharacter
{
	GENERATED_BODY()
public:
	// ---------------------------------------------------------
	// Strictly Gameplay
	// ---------------------------------------------------------

	virtual void ReceiveDamage(float InDamage) {};

	virtual void BasicAttack(AOskradUnitBase* InTarget) {};
	virtual void SpecialAttack1(AOskradUnitBase* InTarget) {};
	virtual void SpecialAttack2(AOskradUnitBase* InTarget) {};
	virtual void SpecialAttack3(AOskradUnitBase* InTarget) {};

	virtual void MoveAction(AOskradUnitBase* InTarget) {};

	virtual float GetHealth() { return -1.f; };

	// ---------------------------------------------------------
	// Other
	// ---------------------------------------------------------

	virtual AAIController* GetAiController()
	{ 
		return Cast<AAIController>(GetController());
	}
};