#pragma once

#include "CoreMinimal.h"
#include "OskradUnit.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UOskradUnitInterface : public UInterface
{
	GENERATED_BODY()
};



class IOskradUnitInterface
{
	GENERATED_BODY()
public:
	virtual void ReceiveDamage(float InDamage) = 0;
		
	virtual void BasicAttack(IOskradUnitInterface* InTarget) = 0;
	virtual void SpecialAttack1(IOskradUnitInterface* InTarget) = 0;
	virtual void SpecialAttack2(IOskradUnitInterface* InTarget) = 0;
	virtual void SpecialAttack3(IOskradUnitInterface* InTarget) = 0;

	virtual void MoveAction(IOskradUnitInterface* InTarget) = 0;

	virtual float GetHealth() = 0;

};

