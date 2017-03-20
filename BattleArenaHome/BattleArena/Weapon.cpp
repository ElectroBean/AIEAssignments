#include "Weapon.h"
#include <iostream>


Weapon::Weapon()
{

}

Weapon::Weapon(int a_iDamage, std::string a_sName) 
{
	m_sName = a_sName;
	m_iDamage = a_iDamage;
}

int Weapon::GetDamage() 
{
	return m_iDamage;
}

Weapon::~Weapon()
{

}
