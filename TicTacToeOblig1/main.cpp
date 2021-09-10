#include <iostream>

void Menu();
void MainGameLoop();
void DrawBoard();
void SwitchActivePlayer();
void ResetGameState();


void ResetBoard();
void DisplayWinner();
bool WinCheck();
bool WinCheck();

void ClearCin();

char boardBlueprint[9] = { '1','2','3','4','5','6','7','8','9' };
char board[9] = {};

char activePlayer = 'X';

int main() {

	ResetBoard();

	
	Menu();

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
		std::cout << "2. Play agenst computer" << std::endl;
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
	activePlayer = 'X';
	ResetBoard();
	int totalTurns{};

	while (true)
	{
		system("cls");
		DrawBoard();

		int input{};
		bool acceptedAns = false;
		// checking that the answer is inside the array/board length
		while (!acceptedAns) 
		{
			
			std::cin >> input;
			ClearCin();

			acceptedAns = true;
			if (input >= 1 && input <= 9){
			}
			else{
				DrawBoard();
				std::cout << "Invalid answer, please input again: " << std::endl;
				acceptedAns = false;
			}

			if (board[input - 1] == 'X' || board[input - 1] == 'O') {
				std::cout << "Space alleready taken, please try again" << std::endl;
				acceptedAns = false;
			}

		}
		//succsesfull turn logic
		board[input - 1] = activePlayer;	
		totalTurns++;

		if (WinCheck()){
			system("cls");
			DrawBoard();
			std::cout << "Player " << activePlayer << " has won!" << std::endl;
			system("pause");
			break;
		}

		SwitchActivePlayer();
		
		
			
		
		//if 9 turns is taken, and nobody with this round, its always a draw
		if (totalTurns == 9)
		{
			std::cout << "It's a draw!" << std::endl;
			exit(3);
		}

	}
}


void DrawBoard() {
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

	std::cout << std::endl << activePlayer << "'s turn : ";
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

void DisplayWinner() {
	std::cout << activePlayer << " has win! WINWINWIWNWINW" << std::endl;
	system("pause");
}

void ResetBoard() {
	for (int i = 0; i < sizeof(board)/sizeof(board[0]); i++)
	{
		board[i] = boardBlueprint[i];
	}
}

bool WinCheck() {
	// cheking the rows

	for (int i = 0; i < 3; i++){
		if (board[i * 3 + 0] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
			return true;
		}
	}

	//checking the collums
	for (int i = 0; i < 3; i++){
		if (board[0 + i] == board[3 + i] && board[3 + i] == board[6 + i]){
			return true;
		}
	}

	//checking the / diagonal
	if (board[0] == board[4] && board[4] == board[8]){
		return true;
	}
	//checking \\ 
	if (board[2] == board[4] && board[4] == board[6]){
		return true;
	}


	return false;

}


void ClearCin() {
	std::cin.clear();    //Clears eventual errors from buffer
	std::cin.ignore(32767, '\n');    //clears the buffer if anything is there
}
