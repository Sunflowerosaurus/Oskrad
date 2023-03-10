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
	if (HealthPoints <= 0)
	{
		this->Destroy();
	}
	UE_LOG(LogTemp, Error, TEXT("---HP: %f ---"), HealthPoints);
}

void AOskradTank::BasicAttack(AOskradUnitBase* InTarget)
{
		InTarget->ReceiveDamage(BaseDamage);
}

void AOskradTank::SpecialAttack2(AOskradUnitBase* InTarget) 
{
	InTarget = this;
	this->ArmorPoints += 20; // Implement turns it should last 2-3 turns
	UE_LOG(LogTemp, Error, TEXT("----ARMOR POINTS: %f----"), ArmorPoints);
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

