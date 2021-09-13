#include <iostream>
#include <vector>

void Menu();
void MainGameLoop();
void DrawBoard(std::vector<char> a_board);
void SwitchActivePlayer();

int PlayerInput();

void ResetBoard();

/// <summary>
/// Checks if the gamestate is a win
/// </summary>
/// <returns></returns>
bool WinCheck();

void DisplayWinner();

void ClearCin();

//AI part

/// <summary>
/// AI always starts, and always places in the center spot
/// This AI is based on that the player can either place their 'O' in a corner or a edge, this means if we rotate the board
/// in increments of 90 degrees, and we rotate the board correct, the player only has two starting positions,
/// either down left corner or bottom edge
/// This way we only have to code two paths for the AI to play where one of them i allways winnable (edge) and 
/// one is drawable (corner)
/// </summary>
/// <param name="a_board">the board to rotate</param>
/// <param name="turn">the total turns taken</param>
/// <returns></returns>
int AIInput(std::vector<char> a_board, int turn);

int ConvertInputFromRotation(int rotIntput);

void HowManyRotations();





std::vector<char> RotateBoard90Deg(std::vector<char> a_board);

std::vector<char> boardBlueprint = { '1','2','3','4','5','6','7','8','9' };
std::vector<char> board = { '1','2','3','4','5','6','7','8','9' };
bool AIisOn{ false };
char activePlayer = 'X';

bool winCase = false;
int howManyTurns{};

int main() {

	Menu();

	return 0;
}

void Menu() {
	while (true)
	{
		//Clears the space incase someting is left in the console window
		system("cls");

		//introduction
		std::cout << "Hello and Welcome to TicTacToe!!" << std::endl;
		std::cout << "________________________________" << std::endl << std::endl;
		std::cout << "Please select from the menu below : " << std::endl;

		//scenes / options
		std::cout << "1. Play duos" << std::endl;
		std::cout << "2. Play agenst computer" << std::endl;
		std::cout << "q. Quit" << std::endl << std::endl;
		
		//The players input
		std::cout << "Input : ";
		std::string answer{};
		std::cin >> answer;
		ClearCin();
		char charAns{};

		if (answer.size() > 1){
			charAns = {};
		}
		else{
			charAns = answer[0];
		}

		switch (charAns)
		{
		case'1':
			AIisOn = false;
			MainGameLoop();
			break;
		case '2':
			AIisOn = true;
			MainGameLoop();
			break;
		case 'q':
			exit(3);
			break;
		default:
			break;
		}

	}
}


void MainGameLoop() {

	system("cls");
	activePlayer = 'X';	// Defualts to X as first player
	ResetBoard();

	int totalTurns{};	//Counter for how many turns the has taken

	
	while (true) // gameplay loop, runs until break is called
	{
		system("cls");
		DrawBoard(board);
		std::cout << activePlayer << "'s turn : ";

		int input{};

		if (AIisOn && activePlayer == 'X'){
			//	AI logic
			
			//when we are at the third turn (total turns starts at 0) check how many roations of the board are needed
			if (totalTurns == 2){
				HowManyRotations();
			}

			std::vector<char> rotatedBoard = board;
			for (int i = 0; i < howManyTurns; i++) 
			{
				rotatedBoard = RotateBoard90Deg(rotatedBoard);
			}
			
			input = AIInput(rotatedBoard, totalTurns);
			input = ConvertInputFromRotation(input);
		}
		else
		{
			input = PlayerInput();
		}


		//succsesfull input logic
		board[input - 1] = activePlayer;	

		if (WinCheck()){
			system("cls");
			DrawBoard(board);
			std::cout << "Player " << activePlayer << " has won!" << std::endl;
			system("pause");
			break;
		}
			
		totalTurns++;
		//if 9 turns is taken, and nobody with this round, its always a draw
		if (totalTurns == 9)
		{
			system("cls");
			DrawBoard(board);
			std::cout << "It's a draw!" << std::endl;
			system("pause");
			break;
		}

		SwitchActivePlayer();
	}
}


std::vector<char> RotateBoard90Deg(std::vector<char> a_board) {
	
	//Rotates the board 90 degres
	//edges

	int edge_buffer = a_board[1];
	a_board[1] = a_board[5];
	a_board[5] = a_board[7];
	a_board[7] = a_board[3];
	a_board[3] = edge_buffer;

	//corners
	int cornerbuffer = a_board[0];
	a_board[0] = a_board[2];
	a_board[2] = a_board[8];
	a_board[8] = a_board[6];
	a_board[6] = cornerbuffer;

	return a_board;
}

void DrawBoard(std::vector<char> a_board) {
	//Draws the board
	for (int i = 0; i < 3; i++)
	{
		std::cout << ' ';
		for (int j = 0; j < 3; j++)
		{
			std::cout << a_board[(2 - i) * 3 + j];
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

	std::cout << std::endl << std::endl;
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

int PlayerInput() {
	// checking that the answer is inside the array/board length
	int input{};
	bool acceptedAns = false;
	while (!acceptedAns)
	{
		std::cin >> input;
		ClearCin();

		acceptedAns = true;
		if (input >= 1 && input <= 9) {
		}
		else {
			system("cls");
			DrawBoard(board);
			std::cout << "Invalid answer, please input again: " << std::endl;
			std::cout << activePlayer << "'s turn : ";

			acceptedAns = false;
		}

		if (board[input - 1] == 'X' || board[input - 1] == 'O') {
			system("cls");
			DrawBoard(board);
			std::cout << "Space alleready taken, please try again" << std::endl;
			std::cout << activePlayer << "'s turn : ";
			acceptedAns = false;
		}

	}

	return input;

}


void ResetBoard() {
	for (int i = 0; i < board.size(); i++)
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


int AIInput(std::vector<char> a_board, int turn) {

	if (turn == 0){
		return 5;
	}

	


	//corner route
	if (winCase)
	{

		switch (turn)
		{
		case 2:
			return 9;
			break;

		case 4: 
			if (a_board[0] == 'O'){
				return 3;
			}
			else{
				return 1;
			}
			break;

		case 6:
			if (a_board[5] == 'O'){
				return 7;
			}
			else{
				return 6;
			}

		default:
			break;
		}
	}
	else
	{
		switch (turn)
		{
		case 2:
			return 6;
			break;

		case 4:
			if (a_board[3] == 'O') {
				return 7;
			}
			else {
				return 4;
			}
			break;

		case 6:
			if (a_board[2] == 'O') {
				return 2;
			}
			else {
				return 3;
			}
			break;

		case 8:
			if (a_board[7] == 'O') {
				return 9;
			}
			else
			{
				return 8;
			}
			break;

		default:
			break;
		}
	}
}

int ConvertInputFromRotation(int rotIntput) {
	

	//creates a new defualt board and rotates it so it matches the AI's veiw
	std::vector<char> coverntBoard = boardBlueprint;
	for (int i = 0; i < howManyTurns; i++)
	{
		coverntBoard = RotateBoard90Deg(coverntBoard);
	}

	// inputs the X where the AI wanted to place it on the rotated board
	coverntBoard[rotIntput - 1] = 'X';

	//rotates the board back to the original rotation (the rotation the player sees)
	for (int i = 0; i < 4 - howManyTurns; i++)
	{
		coverntBoard = RotateBoard90Deg(coverntBoard);
	}

	//finds the poition in the vector/board where the x is
	for (int i = 0; i < coverntBoard.size(); i++)
	{
		if (coverntBoard[i] == 'X')
		{
			rotIntput = (i + 1); // input is equal the i (the position) pluss 1 (so it matches the numpad)
		}
	}

	return rotIntput;
}


void HowManyRotations(){
	//Checking corner
	if (board[6] == 'O') {
		howManyTurns = 3;
		winCase = false;
	}
	else if (board[8] == 'O') {
		howManyTurns = 2;
		winCase = false;
	}
	else if (board[2] == 'O') {
		howManyTurns = 1;
		winCase = false;
	}
	else if (board[0] == 'O') {
		howManyTurns = 0;
		winCase = false;
	}

	//checking edges
	if (board[3] == 'O') {
		howManyTurns = 3;
		winCase = true;
	}
	else if (board[7] == 'O') {
		howManyTurns = 2;
		winCase = true;
	}
	else if (board[5] == 'O')
	{
		howManyTurns = 1;
		winCase = true;
	}
	else if (board[1] == 'O')
	{
		howManyTurns = 0;
		winCase = true;
	}
}