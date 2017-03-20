#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include "GameInfo.h"

//bitbucket.org/DoddzyCodes/2017_Firstyeartutorials

GameInfo loadGameFromTextFile(std::fstream &aFile);
std::vector<GameInfo> loadAllGamesFromFile(std::string aPath);
void saveGamesToBinaryFile(std::vector<GameInfo>& games);
std::vector<GameInfo> LoadGamesFromBinary(std::string path);

void main()
{
	std::vector<GameInfo> games = loadAllGamesFromFile("games.txt");
	saveGamesToBinaryFile(games);
}

GameInfo loadGameFromTextFile(std::fstream &aFile)
{
	GameInfo game;
	char buffer[1024];
	aFile.getline(buffer, 1023);
	strcpy(game.m_sName, buffer);

	aFile.getline(buffer, 1023);
	strcpy(game.m_sPublisher, buffer);

	//read the $ sign and ignore it.
	char c; aFile.get(c);
	aFile >> game.m_fCost;
	aFile.getline(buffer, 1023);

	int i = 0;
	aFile >> i;
	game.m_eStatus = (GameInfo::OwnedStatus)i;
	aFile.getline(buffer, 1023);

	aFile >> game.m_fScore;
	aFile.getline(buffer, 1023);

	aFile.getline(buffer, 1023);
	return game;
}

std::vector<GameInfo> loadAllGamesFromFile(std::string aPath)
{
	//try and load the file at "path" for input
	std::fstream inputFile(aPath, std::ios_base::in);
	if (inputFile.bad())
	{
		//if the file is bad, display an error
		std::cout << "Unable to open " << aPath << ". Please check the file"
			<< " and try again" << std::endl;
		return std::vector<GameInfo>();
	}
	std::vector<GameInfo> games;
	while (!inputFile.eof())
	{
		games.push_back(loadGameFromTextFile(inputFile));
	}
	inputFile.close();
	return games;
}

void saveGamesToBinaryFile(std::vector<GameInfo>& games)
{
	std::fstream outputFile("games.dat", std::ios_base::out ||
		std::ios_base::binary);
	if (!outputFile.is_open())
	{
		std::cout << "something went wrong - please make sure that "
			<< "the games.dat file is not being accessed." << std::endl;
		return;
	}
	int numberofGames = games.size();
	outputFile.write((char*)&numberofGames, sizeof(int));

	for (GameInfo& game : games)
	{
		outputFile.write((char*)&game, sizeof(GameInfo));
	}

	outputFile.close();
}

std::vector<GameInfo> LoadGamesFromBinary(std::string path)
{
	std::fstream inputFile(path, std::ios_base::in || std::ios_base::binary);

	if (!inputFile.is_open())
	{
		std::cout << "something went wrong - please make sure that "
			<< "the games.dat file is not being accessed." << std::endl;
		return std::vector<GameInfo>();
	}
	int numberOfGames = 0;
	inputFile.read((char*)numberOfGames, sizeof(int));
	std::vector < GameInfo> games;
	for (int i = 0; i < numberOfGames; i++)
	{
		GameInfo info;
		inputFile.read((char*)&info, sizeof(GameInfo));

		games.push_back(info);
	}

	return games;
}
