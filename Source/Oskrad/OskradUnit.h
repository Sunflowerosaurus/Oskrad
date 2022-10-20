// nasze pole

#pragma once

#include "CoreMinimal.h"

class IOskradUnit
{
	public:
		
		virtual void ReceiveDamage(float Damage, float Health, float ArmorPoints) = 0;
		virtual void BasicAttack(float BaseDamage, int MovementPoints) = 0;
		virtual void SpecialAttack1(float BaseDamage, int MovementPoints) = 0;
		virtual void SpecialAttack2(float BaseDamage, int MovementPoints) = 0;
		virtual void SpecialAttack3(float BaseDamage, int MovementPoints) = 0;
		virtual void MoveAction(float MovementPoints) = 0; // Unit Move Action

};

class OskradTankHero : public IOskradUnit
{
	public:
		float Health = 300;
		int MovementPoints = 10;
		float ArmorPoints = 20;

		virtual void ReceiveDamage(float Damage, float Health, int ArmorPoints)
		{
			Health = Health - (Damage - ArmorPoints);
			if (Health <= 0) {
				//Unit is Dead
			}
		}

		virtual void BasicAttack(float BaseDamage, int MovementPoints)
		{
			if (MovementPoints >= 2) {
				

			} else {
				printf("NIE DA RADY SIR");
			}

		}

	private:
		float BaseDamage = 20;
};

class OskradDamageHero : public IOskradUnit
{
	public:
		float Health = 150;
		int MovementPoints = 15;
		float ArmorPoints = 15;

		virtual void ReceiveDamage(float Damage, float Health, int ArmorPoints)
		{
			Health = Health - (Damage - ArmorPoints);
			if (Health <= 0) {
				//Unit is Dead
			}
		}

	private:
		float BaseDamage = 35;
};

class OskradSupportDamage : public IOskradUnit
{
	public:
		float Health = 125;
		int MovementPoints = 20;
		float ArmorPoints = 10;

		virtual void ReceiveDamage(float Damage, float Health, int ArmorPoints)
		{
			Health = Health - (Damage - ArmorPoints);
			if (Health <= 0) {
				//Unit is Dead
			}
		}

	private:
		float BaseDamage = 15;


};