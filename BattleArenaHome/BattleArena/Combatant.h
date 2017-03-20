#pragma once
#include "Weapon.h"
#include <string>

class Combatant
{
public:
	Combatant();

	enum Type
	{
		Knight,
		Samurai, 
		Viking,
	};

	void TakeDamage(int a_iDamage);
	void DealDamage(int a_iDamage, Combatant* a_kEnemy);
	Combatant(int a_iHealth, int a_iDamage, Weapon* weapon, int iPosition, Type a_class);
	int GetHealth();
	int GetDamage(Weapon* weapon);
	Weapon* GetWeapon();
	int GetPosition();
	int randRange(unsigned int min, unsigned int max);
	std::string getClass(Type a_class);
	Type getType();

	~Combatant();

private: 
	int m_iHealth;
	int m_iDamage;
	Weapon* m_pWeapon;
	int m_iPosition;
	Type m_class;
};

