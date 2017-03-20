#include <iostream>

bool winCheck(char input[][3]);
bool stalemateCheckTicTacToe(char input[][3]);

void main()
{
	bool running = true;
	int input = 0;
	const int places = 3;
	char placements[places][places];
	bool vInput = false;
	int playerTurn = 1;
	char placement;

	for (int i = 0; i < places; i++)
	{
		for (int j = 0; j < places; j++)
		{
			placements[i][j] = 49 + (i * places + j);
		}
	}

	while (running) {
		system("cls");
		vInput = false;

		if (playerTurn == 1) {
			std::cout << "\n\nPlayer 1's turn" << std::endl;
		}
		else {
			std::cout << "\n\nPlayer 2's turn" << std::endl;
		}
		for (int i = 0; i < places; i++)
		{
			std::cout << "\n\n";
			for (int j = 0; j < places; j++)
			{
				std::cout << placements[i][j] << "  ";
			}
		}
		while (!vInput)
		{
			std::cin >> input;
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');

			switch (input) {
			case 1: {
				placement = placements[0][0];
				break;
			}
			case 2: {
				placement = placements[0][1];
				break;
			}
			case 3: {
				placement = placements[0][2];
				break;
			}
			case 4: {
				placement = placements[1][0];
				break;
			}
			case 5: {
				placement = placements[1][1];
				break;
			}
			case 6: {
				placement = placements[1][2];
				break;
			}
			case 7: {
				placement = placements[2][0];
				break;
			}
			case 8: {
				placement = placements[2][1];
				break;
			}
			case 9: {
				placement = placements[2][2];
				break;
			}
			}

			if (input < 10 && input > 0 && placement == (char)(48 + input))
			{
				vInput = true;
			}
			else
			{
				std::cout << "Invalid Input\n";
				vInput = false;
			}
		}

		if (playerTurn == 1) {
			std::cout << "\n\nPlayer 1's turn" << std::endl;
			switch (input)
			{
			case 1:
			{
				placements[0][0] = 'x';
				break;
			}
			case 2:
			{
				placements[0][1] = 'x';
				break;
			}
			case 3:
			{
				placements[0][2] = 'x';
				break;
			}
			case 4:
			{
				placements[1][0] = 'x';
				break;
			}
			case 5:
			{
				placements[1][1] = 'x';
				break;
			}
			case 6:
			{
				placements[1][2] = 'x';
				break;
			}
			case 7:
			{
				placements[2][0] = 'x';
				break;
			}
			case 8:
			{
				placements[2][1] = 'x';
				break;
			}
			case 9:
			{
				placements[2][2] = 'x';
				break;
			}
			}
			playerTurn = 2;
		}
		else {
			switch (input)
			{
			case 1:
			{
				placements[0][0] = 'o';
				break;
			}
			case 2:
			{
				placements[0][1] = 'o';
				break;
			}
			case 3:
			{
				placements[0][2] = 'o';
				break;
			}
			case 4:
			{
				placements[1][0] = 'o';
				break;
			}
			case 5:
			{
				placements[1][1] = 'o';
				break;
			}
			case 6:
			{
				placements[1][2] = 'o';
				break;
			}
			case 7:
			{
				placements[2][0] = 'o';
				break;
			}
			case 8:
			{
				placements[2][1] = 'o';
				break;
			}
			case 9:
			{
				placements[2][2] = 'o';
				break;
			}
			}
			playerTurn = 1;
		}

		if (winCheck(placements))
		{
			running = false;
			if (playerTurn == 1)
			{
				playerTurn = 2;
			}
			else if (playerTurn == 2)
			{
				playerTurn = 1;
			}
		}
	}
	system("cls");
	for (int i = 0; i < places; i++)
	{
		std::cout << "\n\n";
		for (int j = 0; j < places; j++)
		{
			std::cout << placements[i][j] << "  ";
		}
	}
	std::cout << "\n\n------------------------------------------------------\n\n";
	if (winCheck(placements)) 
	{
		std::cout << "Game over! Player: " << playerTurn << " won.\n\n";
	}
	else
	{
		std::cout << "Stalemate!\n" << std::endl;
	}
	std::cout << "------------------------------------------------------\n\n";
	std::cin;

	system("pause");
}

bool winCheck(char input[][3])
{
	if (input[0][0] == input[0][1] && input[0][2] == input[0][1])
	{
		return true;
	}
	else if (input[1][0] == input[1][1] && input[1][1] == input[1][2])
	{
		return true;
	}
	else if (input[2][0] == input[2][1] && input[2][1] == input[2][2])
	{
		return true;
	}
	else if (input[0][0] == input[1][0] && input[1][0] == input[2][0])
	{
		return true;
	}
	else if (input[0][1] == input[1][1] && input[1][1] == input[2][1])
	{
		return true;
	}
	else if (input[0][2] == input[1][2] && input[1][2] == input[2][2])
	{
		return true;
	}
	else if (input[0][0] == input[1][1] && input[1][1] == input[2][2])
	{
		return true;
	}
	else if (input[0][2] == input[1][1] && input[1][1] == input[2][0])
	{
		return true;
	}

	return false;
}

bool stalemateCheckTicTacToe(char input[][3]) {
	int index = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (input[i][j] == 'o' || input[i][j] == 'x')
			{
				index++;
			}
		}
	}
	if (index == 9) {
		return true;
	}
	else {
		return false;
	}
}