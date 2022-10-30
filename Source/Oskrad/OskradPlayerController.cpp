#include "OskradPlayerController.h"

// UE
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"

// Oskrad
#include "OskradCharacter.h"
#include "Oskrad.h"

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

	InputComponent->BindAction("PickUnitSingle", IE_Pressed, this, &AOskradPlayerController::OnPickUnitSinglePressed);
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

		// TODO [RCH]: This would move our pawn instead of the selected unit. Move the selected unit instead.
		// We move there and spawn some particles
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
	}
}

void AOskradPlayerController::OnPickUnitSinglePressed()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, true, Hit);
	auto* TargetActor = Hit.GetActor();

	auto* TargetOskradUnit = Cast<AOskradUnitBase>(TargetActor);
	SelectUnit(TargetOskradUnit); // Takes care of nullptrs
}
