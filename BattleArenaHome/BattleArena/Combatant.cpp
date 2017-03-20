#include "Combatant.h"
#include <ctime>
#include <iostream>
#include <random>


Combatant::Combatant()
{

}

Combatant::Combatant(int a_iHealth, int a_iDamage, Weapon* weapon, int iPosition, Type a_class)
{
	m_iHealth = a_iHealth;
	m_iDamage = a_iDamage;
	m_pWeapon = weapon;
	m_iPosition = iPosition;
	m_class = a_class;
}

int Combatant::GetPosition()
{
	return m_iPosition;
}

void Combatant::TakeDamage(int a_iDamage)
{
	m_iHealth -= a_iDamage;
}

std::string Combatant::getClass(Type a_class) 
{
	switch (a_class)
	{
	case Type::Knight:
	{
		return "Knight";
		break;
	}
	case Type::Samurai:
	{
		return "Samurai";
		break;
	}
	case Type::Viking:
	{
		return "Viking";
		break;
	}
	}
}

Combatant::Type Combatant::getType()
{
	return m_class;
}

void Combatant::DealDamage(int a_iDamage, Combatant* a_kEnemy)
{
	int hitSuccess = randRange(1, 100);
	int actualDamage = 0;

	switch (hitSuccess / 20)
	{
	case 0: // Less than 20 hp
		actualDamage = a_iDamage * 0;
		break;
	case 1: // less than 40 hp
		actualDamage = a_iDamage;
		break;
	default: // anything else
		actualDamage = a_iDamage * 2;
		break;
	}

	a_kEnemy->TakeDamage(actualDamage);
}

int Combatant::GetDamage(Weapon* weapon) 
{
	return weapon->GetDamage();
}

Weapon* Combatant::GetWeapon()
{
	return m_pWeapon;
}

int Combatant::GetHealth() 
{
	return m_iHealth;
}

int Combatant::randRange(unsigned int min, unsigned int max) {
	std::random_device rand;
	std::mt19937 eng(rand());
	std::uniform_int_distribution<> range(min, max);
	return(range(eng));
}

Combatant::~Combatant()
{
	
}

