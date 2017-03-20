#pragma once
class GameInfo
{
public:
	enum OwnedStatus
	{
		No,
		Yes,
		InCart,
		Watched,
	};

	GameInfo();
	~GameInfo();



	char m_sName[256];
	char m_sPublisher[256];
	OwnedStatus m_eStatus;
	float m_fCost;
	float m_fScore;
};

