#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OskradUnit.h"
#include "OskradCharacter.h"
#include "OskradTank.generated.h"

UCLASS()
class OSKRAD_API AOskradTank : public AOskradUnitBase
{
	GENERATED_BODY()

public:
	void ReceiveDamage(float InDamage) override;

	void BasicAttack(AOskradUnitBase* InTarget) override;

	void SpecialAttack1(AOskradUnitBase* InTarget) override
	{
		checkf(false, TEXT("TODO: NOT IMPLEMENTED YET."));
	}

	void SpecialAttack2(AOskradUnitBase* InTarget) override;

	void SpecialAttack3(AOskradUnitBase* InTarget) override
	{
		checkf(false, TEXT("TODO: NOT IMPLEMENTED YET."));
	}

	void MoveAction(AOskradUnitBase* InTarget) override
	{
		checkf(false, TEXT("TODO: NOT IMPLEMENTED YET."));
	}

	virtual float GetHealth() override;

	AOskradTank();

private:
	float HealthPoints;
	int ActionPoints;
	float ArmorPoints;
	float BaseDamage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

