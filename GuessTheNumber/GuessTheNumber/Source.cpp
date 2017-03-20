#include <iostream>
#include <ctime> 
#include <string>
#include "SaveGame.h"
#include <random>

void Difficulty();
void CompGuess();
int randRange(unsigned int min, unsigned int max);

int iGuessMax = 0;
int iRandomNumberMax = 0;
int iModNumber = iRandomNumberMax;

int iCompMax = iRandomNumberMax;
int iCompMin = 0;

int iRandomNumber = 0;
bool bGuessing = true;
bool bGuessRunning = true;

int iCompGuess = 0;
bool running = true;
int iCompGuessCount = 0;

void main(float deltaTime)
{
	Difficulty();
	iRandomNumber = randRange(0, iRandomNumberMax);
	iCompMax = iRandomNumberMax;
	iCompMin = 0;

	int iGuess = 0;
	int iGuessCount = 0;
	const int cArrayLength = 64;
	char cInput[cArrayLength];
	bool vInput = false;
	float input;
	std::cout << "Guess the number from 1 to " << iRandomNumberMax << std::endl;
	std::cout << "--------------------------" << std::endl;

	while (running)
	{
		vInput = false;
		input = (float)INT_MAX;
		CompGuess();
		std::cout << "The computer has guessed " << iCompGuess << std::endl;
		std::cout << "--------------------------" << std::endl;

		while (!vInput)
		{
			std::cin >> input;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');

			if (input != (float)INT_MAX)
			{
				vInput = true;
				iGuess = input;
				iGuessCount += 1;
			}
			else
			{
				std::cout << "Invalid input" << std::endl;
			}
		}

		if (iGuessCount > iGuessMax)
		{
			iRandomNumber = randRange(0, iRandomNumberMax);
			iGuessCount = 0;
			std::cout << "The number has changed" << std::endl;
		}

		if (iGuess > iRandomNumber)
		{
			std::cout << "Lower" << std::endl;
		}
		else if (iGuess < iRandomNumber)
		{
			std::cout << "Higher" << std::endl;
		}
		else
		{
			std::cout << "--------------------------" << std::endl;
			std::cout << "Correct" << std::endl;
			std::cout << "--------------------------" << std::endl;
			std::cout << "Do you wish to play again?" << std::endl;
			std::cout << "--------------------------" << std::endl;
			std::cin >> cInput;
			std::cout << "--------------------------" << std::endl;
			if (strcmp(cInput, "Yes") == 0 || strcmp(cInput, "yes") == 0)
			{
				main(deltaTime);
			}
			else {
				running = false;
			}
		}
	}
}
void Difficulty()
{
	int iInput;
	bool validInput = false;
	std::cout << "Choose a difficulty level" << std::endl;

	while (!validInput)
	{
		std::cin >> iInput;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "--------------------------" << std::endl;

		if (iInput > 0 || iInput < 3)
		{
			validInput = true;
		}
		else
		{
			std::cout << "Invalid Input" << std::endl;
		}
	}

	switch (iInput) {
	case 1: {
		iGuessMax = 7;
		iRandomNumberMax = 100;
		break;
	}
	case 2: {
		iGuessMax = 10;
		iRandomNumberMax = 1000;
		break;
	}
	case 3: {
		iGuessMax = 15;
		iRandomNumberMax = 10000;
		break;
	}
	}

}

void CompGuess()
{
	while (bGuessRunning)
	{
		if (bGuessing)
		{
			iCompGuess = randRange(iCompMin, iCompMax);
			++iCompGuessCount;
			if (iCompGuess > iRandomNumber)
			{
				iCompMax = iCompGuess;
			}

			if (iCompGuess < iRandomNumber)
			{
				iCompMin = iCompGuess;
			}

			if (iCompGuess == iRandomNumber)
			{
				std::cout << "Game over, the computer won, you lose" << std::endl;
				std::cout << "--------------------------" << std::endl;
				bGuessing = false;
				running = false;
			}
		}
		break;
	}
}

// Returns a random unsigned integer in the specified range
int randRange(unsigned int min, unsigned int max) 
{
	std::random_device rand;
	std::mt19937 eng(rand());
	std::uniform_int_distribution<> range(min, max);
	return(range(eng));
}