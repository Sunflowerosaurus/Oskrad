#include "OskradTank.h"

AOskradTank::AOskradTank()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthPoints = 300.f;
	ActionPoints = 20;
	ArmorPoints = 10.f;
	BaseDamage = 40.f;
}

void AOskradTank::ReceiveDamage(float InDamage)
{
	HealthPoints = HealthPoints - (InDamage - ArmorPoints);
	UE_LOG(LogTemp, Error, TEXT("---HP: %f ---"), HealthPoints);
}

void AOskradTank::BasicAttack(AOskradUnitBase* InTarget)
{
	InTarget->ReceiveDamage(BaseDamage);
}

float AOskradTank::GetHealth()
{
	return HealthPoints;
}

void AOskradTank::BeginPlay()
{
	Super::BeginPlay();
}

void AOskradTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOskradTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

