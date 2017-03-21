#include <iostream>
#include <fstream>
#include <vector>
#include "GameInfo.h"

using std::cout;
using std::cin;
using std::endl;

GameInfo LoadGameFromTextFile(std::fstream& file);
std::vector<GameInfo> LoadAllGamesFromFile(std::string path);
void SaveGamesToBinaryFile(std::vector<GameInfo>& games);
std::vector<GameInfo> LoadGamesFromBinary(std::string path);
void writeToBinaryFile();

void main()
{
	std::vector<GameInfo> games = LoadAllGamesFromFile("games.txt");
	SaveGamesToBinaryFile(games);
	writeToBinaryFile();
	std::vector<GameInfo> loadedgames = LoadGamesFromBinary("games.dat");
	system("pause");
}

GameInfo LoadGameFromTextFile(std::fstream & file)
{
	GameInfo game;
	char buffer[1024] = { 0 };

	//Read in the game name
	file.getline(buffer, 1023);
	//game.name = buffer;
	strcpy(game.name, buffer);

	//Read in the games publisher
	file.getline(buffer, 1023);
	strcpy(game.publisher, buffer);

	//Read and ignore the char at the start of the line
	char c; file.get(c);
	//Read in the game price
	file >> game.cost;
	//Read in the extra characters after the first char and move to the next line
	file.getline(buffer, 1023);

	//Read the game status
	int i = 0;
	//Store the loaded value in the temp variable
	file >> i;
	game.status = (GameInfo::OwnedStatus)i;
	//Move the 'read pointer' to the next line
	file.getline(buffer, 1023);

	//Read in the game score
	file >> game.score;
	//Store the loaded value in the temp variable
	file.getline(buffer, 1023);

	//Store the loaded value in the temp variable
	file.getline(buffer, 1023);
	return game;
}

std::vector<GameInfo> LoadAllGamesFromFile(std::string path)
{
	//Try and load the file at 'path' for input
	std::fstream inputFile(path, std::ios_base::in);

	if (!inputFile.is_open())
	{
		//Display error
		cout << "Unable to open " << path << ". Please check the file and try again" << endl;
		system("pause");
		return std::vector<GameInfo>();
	}

	//Otherwise, create a new array to store our games
	std::vector<GameInfo> games;

	//While we haven't reached the end of the file
	while (!inputFile.eof() && !inputFile.eof() && inputFile.peek() != EOF)
	{
		//Load a single game from the file and store it in the vector
		games.push_back(LoadGameFromTextFile(inputFile));
	}

	//Close the input file when we are done reading from it;
	inputFile.close();

	//Return the vector back to the caller
	return games;
}

void SaveGamesToBinaryFile(std::vector<GameInfo>& games)
{
	std::fstream outputFile("games.dat", std::ios_base::out |
		std::ios_base::binary);

	if (!outputFile.is_open())
	{
		std::cout << "Something went wrong - please make sure that "
			<< "the games.dat file is not being accessed." << std::endl;
		system("pause");
		return;
	}

	int numberOfGames = games.size();
	outputFile.write((char*)&numberOfGames, sizeof(int));

	for (GameInfo& game : games)
	{
		outputFile.write((char*)&game, sizeof(GameInfo));
	}

	//Close the input file when we are done reading from it;
	outputFile.close();
}

std::vector<GameInfo> LoadGamesFromBinary(std::string path)
{
	//open the file at 'path' as a binary file
	std::fstream inputFile(path, std::ios_base::in | std::ios_base::binary);
	if (!inputFile.is_open())
	{
		std::cout << "Something went wrong - please make sure that "
			<< "the games.dat file is not being accessed." << std::endl;
		return std::vector<GameInfo>();
	}

	//read the number of games currently in the file
	int numberOfGames;
	inputFile.read((char*)&numberOfGames, sizeof(int));
	//Create a new vector to store our loaded games
	std::vector<GameInfo> games; //1
	for (int i = 0; i < numberOfGames; ++i)
	{
		GameInfo info; //create a temp game object
					   //fill the temp game object from the binary data in the file
		inputFile.read((char*)&info, sizeof(GameInfo));
		//Copy the temp object into our array
		games.push_back(info);//2
	}

	//return the list of games
	return games; //3
}

void writeToBinaryFile()
{
	std::fstream outputFile("games.dat", std::ios_base::app |
		std::ios_base::binary);
	std::fstream outputTextFile("games.txt", std::ios_base::app);

	//outputFile.write((char*)'\n', sizeof(1));
	//outputTextFile.write((char*)'\n', sizeof(1));

	char tempName[64]{ 0 };
	std::cout << "What is the name?" << std::endl;
	std::cin.getline(tempName, INT_MAX);
	outputFile.write((char*)&tempName, sizeof(tempName));
	outputTextFile.write((char*)&tempName, sizeof(tempName));

	std::cout << "Who is the publisher?" << std::endl;
	std::cin.getline(tempName, INT_MAX);
	outputFile.write((char*)&tempName, sizeof(tempName));
	outputTextFile.write((char*)&tempName, sizeof(tempName));

	std::cout << "What is the price?" << std::endl;
	std::cin.getline(tempName, INT_MAX);
	outputFile.write((char*)&tempName, sizeof(tempName));
	outputTextFile.write((char*)&tempName, sizeof(tempName));

	std::cout << "What is the current status?" << std::endl;
	std::cin.getline(tempName, INT_MAX);
	outputFile.write((char*)&tempName, sizeof(tempName));
	outputTextFile.write((char*)&tempName, sizeof(tempName));

	std::cout << "What is the rating?" << std::endl;
	std::cin.getline(tempName, INT_MAX);
	std::cin.clear();
	outputFile.write((char*)&tempName, sizeof(tempName));
	outputTextFile.write((char*)&tempName, sizeof(tempName));

	outputFile.close();
}