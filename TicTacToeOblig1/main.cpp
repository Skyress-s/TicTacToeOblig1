#include <iostream>


void MainGameLoop();
void Draw();
void SwitchActivePlayer();

bool WinCheck();


char board[9] = { '1','2','3','4','5','6','7','8','9' };

char activePlayer = 'X';

int main() {
	
	Draw();
	MainGameLoop();


	

	return 0;
}



void MainGameLoop() {
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
		}
		else
		{
			system("cls");
			std::cout << "Space alleready taken, please try again" << std::endl;
			system("pause");
			system("cls");
			Draw();
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
	/*for (size_t i = 0; i < length; i++)
	{

	}
	return  true;*/
}
