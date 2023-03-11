#include "OskradPlayerController.h"

// UE
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "AIController.h"


// Oskrad
#include "OskradCharacter.h"
#include "Oskrad.h"
#include "OskradUnit.h"

AOskradPlayerController::AOskradPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AOskradPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto InputMode = FInputModeGameAndUI{};
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AOskradPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveDestinationInputPressed)
	{
		MoveDestinationFollowTime += DeltaTime;

		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		const FVector HitLocation = Hit.Location;

		if (SelectedUnit != nullptr)
		{
			FVector WorldDirection = (HitLocation - SelectedUnit->GetActorLocation()).GetSafeNormal();
			SelectedUnit->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		MoveDestinationFollowTime = 0.f;
	}
}

void AOskradPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AOskradPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AOskradPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("InteractMain", IE_Pressed, this, &AOskradPlayerController::OnInteractMainPressed);

	InputComponent->BindAction("BasicAttack", IE_Pressed, this, &AOskradPlayerController::OnBasicAttack);
	InputComponent->BindAction("SpecialAttack2", IE_Pressed, this, &AOskradPlayerController::OnSpecialAttack2);
}


void AOskradPlayerController::SelectUnit(AOskradUnitBase* const InToSelect)
{
	if (InToSelect == nullptr)
	{
		UE_LOG(LogOskrad, Warning, TEXT("Trying to select a nullptr."));
		return;
	}

	SelectedUnit = InToSelect;
}

void AOskradPlayerController::OnSetDestinationPressed()
{
	bMoveDestinationInputPressed = true;

	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}


void AOskradPlayerController::OnBasicAttack()
{
	ActionNum = Basic;
}

void AOskradPlayerController::OnSpecialAttack2()
{
	ActionNum = Special2;
}

void AOskradPlayerController::OnSetDestinationReleased()
{
	bMoveDestinationInputPressed = false;

	// Handle short press
	if (MoveDestinationFollowTime <= ShortPressThreshold)
	{
		// We look for the location in the world where the player has pressed the input
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);

		if (SelectedUnit != nullptr)
		{
			auto* AiController = SelectedUnit->GetAiController();
			if (AiController != nullptr)
			{
				AiController->MoveToLocation(HitLocation);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("[AOskradPlayerController::OnSetDestinationReleased] SelectedUnit->GetAiController() returned a nullptr."));
			}
		}
	}
}

void AOskradPlayerController::OnInteractMainPressed()
{
	// TODO: Co teraz?
	if (ActionNum != Default)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Pawn, true, Hit);
		auto* TargetActor = Hit.GetActor();

		auto* TargetOskradUnit = Cast<AOskradUnitBase>(TargetActor);
		if (TargetOskradUnit != nullptr && SelectedUnit != nullptr)
		{
			if (ActionNum == Basic)
			{
				SelectedUnit->BasicAttack(TargetOskradUnit);
			}

			else if (ActionNum == Special2)
			{
				
			}
		}

		ActionNum = Default;
	}
	else
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Pawn, true, Hit);
		auto* TargetActor = Hit.GetActor();

		auto* TargetOskradUnit = Cast<AOskradUnitBase>(TargetActor);
		SelectUnit(TargetOskradUnit); // Takes care of nullptrs
	}
}
