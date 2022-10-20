#pragma once

#include "CoreMinimal.h"

class IOskradUnit
{
	public:
		
		virtual void ReceiveDamage(float Damage, float Health, float ArmorPoints) = 0;
		virtual void BasicAttack(float BaseDamage, int ActionPoints) = 0;
		virtual void SpecialAttack1(float BaseDamage, int ActionPoints) = 0;
		virtual void SpecialAttack2(float BaseDamage, int ActionPoints) = 0;
		virtual void SpecialAttack3(float BaseDamage, int ActionPoints) = 0;
		virtual void MoveAction(int ActionPoints) = 0;

};

