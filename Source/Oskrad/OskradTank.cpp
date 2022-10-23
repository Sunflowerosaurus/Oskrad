// Fill out your copyright notice in the Description page of Project Settings.



#include "OskradTank.h"
#include "OskradUnit.h"

// Sets default values
AOskradTank::AOskradTank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

void AOskradTank::BasicAttack(IOskradUnitInterface* InTarget)
{
	InTarget->ReceiveDamage(BaseDamage);
}

float AOskradTank::GetHealth()
{
	float HP = HealthPoints;
	return HP;
}



// Called when the game starts or when spawned
void AOskradTank::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AOskradTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AOskradTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

