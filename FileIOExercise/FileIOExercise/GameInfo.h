#pragma once
#include <string>

class GameInfo
{
public:
	enum OwnedStatus
	{
		No,
		Yes,
		Watched,
		InCart,
	};

	char name[256];
	char publisher[256];
	float		cost;
	OwnedStatus	status;
	float		score;
};