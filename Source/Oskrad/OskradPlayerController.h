// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// UE
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"

// Oskrad
#include "OskradUnit.h"

// Gen
#include "OskradPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class AOskradPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AOskradPlayerController();
	
	void OnBasicAttack();


	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UNiagaraSystem* FXCursor;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	/*
	* Actor interface
	*/

	virtual void BeginPlay() override;

	/*
	* PlayerController interface
	*/

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	/*
	 * OskradPlayerController functionality
	 */

	void SelectUnit(AOskradUnitBase* const ToSelect);

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void MovePawnCameraUp();



	void OnInteractMainPressed();

protected:
	UPROPERTY(EditDefaultsOnly)
	AOskradUnitBase* SelectedUnit = nullptr;
	
	bool bTargetingMode = false; // false = select mode; true = targetMode


private:
	bool bMoveDestinationInputPressed; 

	// For how long it "move to destination" input has been pressed
	float MoveDestinationFollowTime; 
};


