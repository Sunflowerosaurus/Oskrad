// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OskradUnit.h"
#include "OskradCharacter.h"
#include "OskradTank.generated.h"

UCLASS()
class OSKRAD_API AOskradTank : public AOskradCharacter, public IOskradUnitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties

	void ReceiveDamage(float InDamage) override;

	
	void BasicAttack(IOskradUnitInterface* InTarget) override;
	void SpecialAttack1(IOskradUnitInterface* InTarget) override
	{
		checkf(false, TEXT("TODO: NOT IMPLEMENTED YET."));
	} 
	void SpecialAttack2(IOskradUnitInterface* InTarget) override
	{
		checkf(false, TEXT("TODO: NOT IMPLEMENTED YET."));
	}
	void SpecialAttack3(IOskradUnitInterface* InTarget) override 
	{
		checkf(false, TEXT("TODO: NOT IMPLEMENTED YET."));
	}

	void MoveAction(IOskradUnitInterface* InTarget) override 
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

