#pragma once
class SaveGame
{
public:
	SaveGame(int a_GuessCount, bool a_winState, char* a_loseState);
	~SaveGame();

private:
	int		m_GuessCount;
	bool	m_winState;
	char*	m_loserOrNah;
};

