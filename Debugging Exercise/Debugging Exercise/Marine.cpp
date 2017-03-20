#include "Marine.h"



Marine::Marine()
{
	health = 1000;
}


Marine::~Marine()
{
}

int Marine::attack()
{
	return 10;
}

void Marine::takeDamage(int damage)
{
	health -= damage;
}
