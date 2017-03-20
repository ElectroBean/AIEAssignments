#include "SaveGame.h"



SaveGame::SaveGame(int a_GuessCount, bool a_winState, char* a_loseState)
{
	m_GuessCount = a_GuessCount;
	m_winState = a_winState;
	m_loserOrNah = a_loseState;
}


SaveGame::~SaveGame()
{
}
