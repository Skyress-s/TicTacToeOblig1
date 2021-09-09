#include <iostream>

void Menu();
void MainGameLoop();
void Draw();
void SwitchActivePlayer();

bool WinCheck();

void ClearCin();

char board[9] = { '1','2','3','4','5','6','7','8','9' };

char activePlayer = 'X';

int main() {
	
	Menu();
	MainGameLoop();

	return 0;
}

void Menu() {
	while (true)
	{

		//introduction
		std::cout << "Hello and Welcome to TicTacToe!!" << std::endl;
		std::cout << "________________________________" << std::endl << std::endl;
		std::cout << "Please select from the menu below : " << std::endl;

		//scenes
		std::cout << "1. Play duos" << std::endl;
		std::cout << "2. Play agenst AI" << std::endl;
		std::cout << "q. Quit" << std::endl << std::endl;
		std::cout << "Input : ";
		std::string answer{};
		std::cin >> answer;
		ClearCin();
		char charAns{};

		if (answer.size() > 1)
		{
			charAns = {};
		}
		else
		{
			charAns = answer[0];
		}

		switch (charAns)
		{
		case'1':
			MainGameLoop();
			break;
		case '2':
			break;
		case 'q':
			exit(3);
			break;
		default:
			break;
		}

		system("cls");
	}
}


void MainGameLoop() {
	system("cls");
	Draw();
	int totalTurns{};

	while (true)
	{

		int input{};
		std::cin >> input;
		system("cls");
		if (board[input - 1] != 'X' && board[input - 1] != 'O')
		{
			board[input - 1] = activePlayer;
			Draw();	

			WinCheck();
			SwitchActivePlayer();
			totalTurns++;
		}
		else
		{
			system("cls");
			std::cout << "Space alleready taken, please try again" << std::endl;
			system("pause");
			system("cls");
			Draw();
		}
		//if 9 turns is taken, and nobody with this round, its always a draw
		if (totalTurns == 9)
		{
			std::cout << "It's a draw!" << std::endl;
			exit(3);
		}

	}
}


void Draw() {
	for (int i = 0; i < 3; i++)
	{
		std::cout << ' ';
		for (int j = 0; j < 3; j++)
		{
			std::cout << board[(2 - i) * 3 + j];
			if (j < 2)
			{
				std::cout << " | ";
			}
		}
		if (i < 2)
		{
			std::cout << std::endl << "---|---|---" << std::endl;

		}

	}
	std::cout << std::endl;
}

void SwitchActivePlayer() {
	if (activePlayer == 'X')
	{
		activePlayer = 'O';
	}
	else if (activePlayer == 'O')
	{
		activePlayer = 'X';
	}
	else
	{
		std::cout << "INVALID ACTIVE PLAYER, defualting to 'X' as active player" << std::endl;
		activePlayer = 'X';
		system("pause");
		system("cls");
	}
}

bool WinCheck() {
	//checks the --- / rows
	for (int i = 0; i < 3; i++)
	{
		int win = 0;
		char c = board[i * 3];
		for (int j = 1; j < 3; j++)
		{
			char pos = board[i * 3 + j];
			if (c == pos)
			{
				win++;;
			}
			else
			{
				break;
			}			
		}
		if (win == 2)
		{
			std::cout << activePlayer<< " has win! WINWINWIWNWINW" << std::endl;
			exit(3);
		}

	}

	//checks the ||| or collums
	for (int i = 0; i < 3; i++)
	{
		int win{ 0 };
		char c = board[i];
		for (int j = 0; j < 2; j++)
		{
			char pos = board[i +3 + j*3];

			if (pos == c)
			{
				win++;
			}
			else
			{
				break;
			}
		}
		if (win == 2)
		{
			std::cout << activePlayer << " has win! WINWINWIWNWINW" << std::endl;
			exit(3);
			
			
		}
	}


	//Checks the \ and /

	//start with /
	char c = board[0];
	int win{};
	for (size_t i = 1; i < 3; i++)
	{
		char b = board[i * 4];
		if (b == c)
		{
			win++;
		}
	}
	if (win == 2)
	{
		std::cout << activePlayer << " has win! WINWINWIWNWINW" << std::endl;
		exit(3);
	}



	// checks "\"
	c = board[2];
	win = 0;
	for (int i = 1; i < 3; i++)
	{
		char b = board[2 + i * 2];
		if (b == c)
		{
			win++;
		}
	}
	if (win == 2)
	{
		std::cout << activePlayer << " has win! WINWINWIWNWINW" << std::endl;
		exit(3);
	}

	return  true;
}

void ClearCin() {
	std::cin.clear();    //Clears eventual errors from buffer
	std::cin.ignore(32767, '\n');    //clears the buffer if anything is there
}
