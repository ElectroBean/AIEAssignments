#include <iostream> 
#include "Combatant.h"
#include "Weapon.h"
#include <ctime>
#include <random>
#include <fstream>
#include <string>
#include "Storage.h"
int randRange(unsigned int min, unsigned int max);
void readHighScores();

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
	int totalCombatantCount = 0;

	while (gameOpen)
	{
		while (gamePlaying)
		{
			system("cls");
			std::cout << "How big shall the fight be?" << std::endl;

			int roundCount = 1;
			int index = 0;
			int attacker = 0;
			int attackee = 0;
			int aliveCount = 0;
			int aliveIndex = 0;
			int winnerCount = 0;

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
			totalCombatantCount = KnightCount + SamuraiCount + VikingCount;

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
						//2 random numbers to iterate places within the combatant array
						attacker = randRange(0, aliveCount);
						attackee = randRange(0, aliveCount);

						/*
						makes sure that the attacker and attackee are both alive
						and are on opposing teams
						and are not each other
						*/
						if (combatants[attacker]->GetHealth() > 0
							&& combatants[attackee]->GetHealth() > 0
							&& attacker != attackee
							&& combatants[attacker]->getClass(combatants[attacker]->getType()) != combatants[attackee]->getClass(combatants[attackee]->getType()))
						{
							//deals damage taking in the attackers damage from their weapon
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
						//sets the combatant health to 0 if they have < 0 health
						combatants[i]->TakeDamage(+(combatants[i]->GetHealth()));
					}
					if (combatants[i]->GetHealth() > 0)
					{
						//counts how many are currently alive
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
						//temp variable for sorting
						Combatant* temp;
						//sorts the combatants based on their health (descending)
						if (combatants[i]->GetHealth() < combatants[i + 1]->GetHealth())
						{
							//bubble sort
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
				//checks if all are dead, or there is only 1 person left
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
					//checks to see if there is only 1 type of combatant alive
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
				//if the amount of people on a team == amount of people alive, end the game
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

				bWinLog.open("bWinLog.dat", std::ios::app | std::ios::binary);
				if (bWinLog.good())
				{
					char* pWinnerType = new char[combatants[0]->getClass(combatants[0]->getType()).size() + 1];
					/*std::copy(*(combatants[0]->getClass(combatants[0]->getType()).begin()), *(combatants[0]->getClass(combatants[0]->getType()).end()), pWinnerType);*/
					strcpy(pWinnerType, combatants[0]->getClass(combatants[0]->getType()).data());
					//pWinnerType[combatants[0]->getClass(combatants[0]->getType()).size()] = '\0';
					bWinLog.write(pWinnerType, strlen(pWinnerType));
					bWinLog.write("\n", 1);
					delete[] pWinnerType;
				}
				bWinLog.close();
			}
			else
			{
				std::cout << "error" << std::endl;
			}


			//also deletes everything within arrays
			for (int i = 0; i < totalCombatantCount; i++)
			{
				delete weapons[i];
			}
			for (int i = 0; i < totalCombatantCount; i++)
			{
				delete combatants[i];
			}

			//deletes everything
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
			gameOpen = true;
			gamePlaying = true;
			isGameRunning = true;
		}
		else
		{
			std::cout << "would you like to see the win logs?";
			std::cin >> sInput;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');

			if (strcmp(sInput, "yes") == 0 || strcmp(sInput, "Yes") == 0 || strcmp(sInput, "y") == 0 || strcmp(sInput, "Y") == 0)
			{
				system("cls");
				readHighScores();
			}
			gameOpen = false;
		}
	}
	system("pause");
}

// Returns a random unsigned integer in the specified range
int randRange(unsigned int min, unsigned int max) {
	std::random_device rand;
	std::mt19937 eng(rand());
	std::uniform_int_distribution<> range(min, max);
	return(range(eng));
}

//reads highscores from a binary file
void readHighScores()
{
	std::ifstream bWinLog("bWinLog.dat", std::ios::in | std::ios::binary);
	if (bWinLog.good())
	{
		while (!bWinLog.eof() && bWinLog.peek() != EOF)
		{
			char winner[16]{0};
			//char c; bWinLog.get(c);
			bWinLog.getline(winner, 15);
			std::cout << winner << std::endl;
		}
		bWinLog.close();
	}
}