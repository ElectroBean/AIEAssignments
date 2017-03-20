#include <iostream> 
#include "Combatant.h"
#include "Weapon.h"
#include <ctime>
#include <random>
#include <fstream>
#include <string>
#include "Storage.h"
int randRange(unsigned int min, unsigned int max);

void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::fstream tWinLog;
	std::ofstream bWinLog;

	bool gamePlaying = true;
	int m_Round = 0;
	bool bVInput = false;
	int iInput[3] = { INT_MAX };
	bool isGameRunning = true;
	bool roundGoing = false;
	bool gameOpen = true;

	while(gameOpen)
	{
	while (gamePlaying) 
	{
		system("cls");
		std::cout << "How big shall the fight be?" << std::endl;

		for (int i = 0; i < 3; i++)
		{
			bVInput = false;
			std::cout << "\n";
			if (i == 0)
			{
				std::cout << "How many Knights? ";
			}
			else if (i == 1)
			{
				std::cout << "How many Samurai? ";
			}
			else
			{
				std::cout << "How many Vikings? ";
			}
			while (!bVInput)
			{
				std::cin >> iInput[i];
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				if (iInput[i] != INT_MAX)
				{
					bVInput = true;
				}
				else
				{
					bVInput = false;
					std::cout << "Invalid Input" << std::endl;
				}
			}
		}


		int KnightCount = iInput[0];
		int SamuraiCount = iInput[1];
		int VikingCount = iInput[2];

		Combatant** combatants = new Combatant*[KnightCount + SamuraiCount + VikingCount];
		Weapon** weapons = new Weapon*[KnightCount + SamuraiCount + VikingCount];
		int roundCount = 1;
		int index = 0;
		int attacker = 0;
		int attackee = 0;
		int aliveCount = 0;
		int aliveIndex = 0;
		int winnerCount = 0;
		int totalCombatantCount = KnightCount + SamuraiCount + VikingCount;

		//weapon initialisation//////////////////////////////
		for (int i = 0; i < KnightCount; i++)
		{
			weapons[i] = new Weapon(5, "Sword and Shield");
		}
		for (int i = 0; i < SamuraiCount; i++)
		{
			weapons[KnightCount + i] = new Weapon(15, "Katana");
		}
		for (int i = 0; i < VikingCount; i++)
		{
			weapons[KnightCount + SamuraiCount + i] = new Weapon(10, "Short Sword");
		}
		//////////////////////////////////////////////////////

		//combatant initialisation//////////////////////////////
		for (int i = 0; i < KnightCount; i++)
		{
			combatants[i] = new Combatant(120, weapons[i]->GetDamage(), weapons[i], i + 1, Combatant::Type::Knight);
		}
		for (int i = 0; i < SamuraiCount; i++)
		{
			combatants[KnightCount + i] = new Combatant(70, weapons[KnightCount + i]->GetDamage(), weapons[KnightCount + i], KnightCount + i + 1, Combatant::Type::Samurai);
		}
		for (int i = 0; i < VikingCount; i++)
		{
			combatants[KnightCount + SamuraiCount + i] = new Combatant(90, weapons[KnightCount + SamuraiCount + i]->GetDamage(), weapons[KnightCount + SamuraiCount + i], KnightCount + SamuraiCount + i + 1, Combatant::Type::Viking);
		}
		////////////////////////////////////////////////////////


		while (isGameRunning)
		{
			index = 0;
			aliveIndex = 0;
			m_Round++;
			while (roundGoing)
			{
				for (int i = 0; i < totalCombatantCount / 2; i++)
				{
					attacker = randRange(0, aliveCount);
					attackee = randRange(0, aliveCount);
					if (combatants[attacker]->GetHealth() > 0
						&& combatants[attackee]->GetHealth() > 0
						&& attacker != attackee
						&& combatants[attacker]->getClass(combatants[attacker]->getType()) != combatants[attackee]->getClass(combatants[attackee]->getType()))
					{
						combatants[attacker]->DealDamage(combatants[attacker]->GetDamage(combatants[attacker]->GetWeapon()), combatants[attackee]);
					}
					else
					{

					}
				}
				roundGoing = false;
				system("Pause");
			}
			system("cls");
			for (int i = 0; i < totalCombatantCount; i++)
			{
				if (combatants[i]->GetHealth() < 0)
				{
					combatants[i]->TakeDamage(+(combatants[i]->GetHealth()));
				}
				if (combatants[i]->GetHealth() > 0)
				{
					++aliveIndex;
				}
			}

			aliveCount = aliveIndex - 1;

			bool sorting = true;
			while (sorting)
			{
				sorting = false;
				for (int i = 0; i < totalCombatantCount - 1; i++)
				{
					Combatant* temp;
					if (combatants[i]->GetHealth() < combatants[i + 1]->GetHealth())
					{
						temp = combatants[i + 1];
						combatants[i + 1] = combatants[i];
						combatants[i] = temp;
						sorting = true;

					}
				}
			}

			std::cout << "        Round " << m_Round << "        \n";

			//counting how many are dead and displaying current health
			for (int i = 0; i < totalCombatantCount; i++)
			{
				if (combatants[i]->GetHealth() == 0)
				{
					index++;
				}
				std::cout << combatants[i]->getClass(combatants[i]->getType()) << ": " << combatants[i]->GetPosition() << ", has " << combatants[i]->GetHealth() << " health" << std::endl;
			}
			if (index == totalCombatantCount || index == totalCombatantCount - 1)
			{
				roundGoing = false;
				isGameRunning = false;
			}
			else
			{
				Combatant::Type temp;
				temp = combatants[0]->getType();
				winnerCount = 0;
				// trying to make it check if there are only 1 Type of combatant alive
				for (int i = 0; i < totalCombatantCount; i++)
				{
					if (combatants[i]->GetHealth() > 0)
					{
						if (combatants[i]->getType() != temp)
						{
							isGameRunning = true;
							roundGoing = true;
						}
						else
						{
							winnerCount += 1;
						}
					}
				}
			}
			if (winnerCount == aliveCount + 1)
			{
				isGameRunning = false;
				roundGoing = false;
			}
		}
		if (index == totalCombatantCount)
		{
			std::cout << "No survivors" << std::endl;
		}
		else if (winnerCount == aliveCount + 1)
		{
			std::cout << "----------------------------------------" << std::endl;
			std::cout << std::endl << combatants[0]->getClass(combatants[0]->getType()) << "(s) " << " won, with: " << winnerCount << " alive." << std::endl;
			std::cout << std::endl << "----------------------------------------" << std::endl;
			tWinLog.open("winLog.txt", std::ios_base::app);
			tWinLog << combatants[0]->getClass(combatants[0]->getType()) << "(s) " << " won, " << " with " << aliveIndex << " alive" << std::endl;
			tWinLog.close();

			bWinLog.open("bWinLog.txt", std::ios::app | std::ios::binary);
			if (bWinLog.good())
			{
				char* pWinnerType = new char[combatants[0]->getClass(combatants[0]->getType()).size() + 1];
				/*std::copy(*(combatants[0]->getClass(combatants[0]->getType()).begin()), *(combatants[0]->getClass(combatants[0]->getType()).end()), pWinnerType);*/
				strcpy(pWinnerType, combatants[0]->getClass(combatants[0]->getType()).data());
				pWinnerType[combatants[0]->getClass(combatants[0]->getType()).size()] = '\0';
				bWinLog.write(pWinnerType, strlen(pWinnerType));
				bWinLog.write("\n", 2);
				delete[] pWinnerType;
			}
			bWinLog.close();
		}
		else
		{
			std::cout << "error" << std::endl;
		}


		for (int i = 0; i < totalCombatantCount; i++)
		{
			delete weapons[i];
		}
		for (int i = 0; i < totalCombatantCount; i++)
		{
			delete combatants[i];
		}

		delete[] combatants;
		combatants = nullptr;
		delete[] weapons;
		weapons = nullptr;
		system("pause");
		gamePlaying = false;
	}
	system("cls");
	char sInput[64];
	std::cout << "Would you like to 'play' again?";
	std::cin >> sInput;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	if (strcmp(sInput, "yes") == 0 || strcmp(sInput, "Yes") == 0 || strcmp(sInput, "y") == 0 || strcmp(sInput, "Y") == 0)
	{
		gamePlaying = true;
	}
	else
	{
		system("pause");
	}
}
}

// Returns a random unsigned integer in the specified range
int randRange(unsigned int min, unsigned int max) {
	std::random_device rand;
	std::mt19937 eng(rand());
	std::uniform_int_distribution<> range(min, max);
	return(range(eng));
}