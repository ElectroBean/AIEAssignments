#pragma once
#include <iostream>

class Weapon
{
public:
	Weapon();
	Weapon(int a_iDamage, std::string a_sName);

	int GetDamage();

	~Weapon();

private:
	int m_iDamage;
	std::string m_sName;
};

