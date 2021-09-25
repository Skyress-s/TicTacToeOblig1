#include <iostream>
#include <vector>


/// <summary>
/// Menu to select duos, vs AI or quit
/// </summary>
void Menu();

/// <summary>
/// The main gameloop logic
/// </summary>
/// <param name=""></param>
void MainGameLoop(bool);

/// <summary>
/// Draws the board that is inputtet
/// </summary>
/// <param name="a_board"></param>
void DrawBoard(std::vector<char> a_board); 

/// <summary>
/// func for switching the active player
/// </summary>
void SwitchActivePlayer(char&);

/// <summary>
/// Gets the player input and checks if its an accepted answer, of not asks again
/// </summary>
/// <returns></returns>
int PlayerInput(std::vector<char>, char);

/// <summary>
/// Resets the global scope board to standard values, 1, 2, 3, 4, ...
/// </summary>
void ResetBoard(std::vector<char>&);

/// <summary>
/// Checks if the gamestate is a win,
/// advice for making the check better was given from Anders from the class
/// </summary>
/// <returns></returns>
bool WinCheck(std::vector<char>);

/// <summary>
/// Clears the cin buffer for input and errors
/// </summary>
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
int AIInput(std::vector<char>, int, bool);

/// <summary>
/// Converts the input the AI gives from the rotated board and converts it to the unrotated board
/// </summary>
/// <param name="rotInput"> Rotated input from AI</param>
/// <param name="rotate amount"> How many rotations of the board</param>
/// <returns></returns>
int ConvertInputFromRotation(int , int);

/// <summary>
/// function to determine how many rotation the board needs to be rotated for the AI to understand it.
/// It return how many 90 degree turns is needed
/// </summary>
/// <returns></returns>
int HowManyRotations(std::vector<char>, bool&);

/// <summary>
/// Rotates a copy of the board gives to it clockwise once
/// </summary>
/// <param name="a_board"> The board to rotate and return </param>
/// <returns>Returns the rotated board</returns>
std::vector<char> RotateBoard90Deg(std::vector<char>);

//a blueprint for an empty board, usefor for quickly resetting a gameboard
const std::vector<char> boardBlueprint = { '1','2','3','4','5','6','7','8','9' }; 

// main func
int main() {
	Menu();
	return 0;
}

void Menu() {
	bool AIisOn{ false };

	while (true)
	{
		//Clears the space incase someting is left in the console window
		system("cls");

		//introduction
		std::cout << std::endl;
		std::cout << "   Hello and Welcome to TicTacToe!!   " << std::endl;
		std::cout << "______________________________________" << std::endl << std::endl;
		std::cout << "  Please select from the menu below : " << std::endl;

		//scenes / options
		std::cout << "1. Play duos" << std::endl;
		std::cout << "2. Play agenst computer" << std::endl;
		std::cout << "q. Quit" << std::endl << std::endl;
		
		//The players input
		std::cout << "Input : ";
		std::string input{};
		std::cin >> input;
		ClearCin();
		char charInput{};

		//if string inputted is over 1 -> invalid answer
		if (input.size() > 1) {
			charInput = {};
		}
		else { // convert first element of string to char
			charInput = input[0];
		}

		switch (charInput) // switchCase for which gamemode to enter 
		{
		case'1': // duos
			AIisOn = false;
			MainGameLoop(AIisOn);
			break;
			
		case '2': // vs AI
			AIisOn = true;
			MainGameLoop(AIisOn);
			break;

		case 'q': // exit
			exit(3);
			break;

		default: // else do nothing
			break;
		}
	}
}

void MainGameLoop(bool a_AIisOn) {
	//the gameboard to be used thorughout the game
	std::vector<char> board(9);

	// active player, this displays the active player, switches between 'X' and 'O'
	char activePlayer = 'X';

	// a bool for the AI, if true -> AI can have a garanteed win path, if false -> draw/tie path
	bool winCase = false;

	system("cls"); // clears the board of the menu text
	activePlayer = 'X';	// Defualts to X as first player
	ResetBoard(board); // resets board to { 1,2,3,4, ... }

	int totalTurns{};	//Counter for how many turns the has taken
	int rotateAmount{}; // How manye 90 degree of the board is needed for the AI to interperit it
	
	while (true) // gameplay loop, runs until break is called/run
	{
		system("cls");
		DrawBoard(board);
		std::cout << activePlayer << "'s turn : "; // displayes active players turn

		int input{};

		//Player input or AI input
		if (a_AIisOn && activePlayer == 'X') {
			//	AI input and logic
			
			//when we are at the third turn (total turns starts at 0) check how many roations of the board are needed
			//for the ai to understand the board correctly
			//saves this in rotate amount for later use

			if (totalTurns == 2){
				rotateAmount = HowManyRotations(board, winCase);
			}

			//defines and rotates the rotateboard
			std::vector<char> rotatedBoard = board;
			for (int i = 0; i < rotateAmount; i++) 
			{
				rotatedBoard = RotateBoard90Deg(rotatedBoard);
			}


			//gives the rotated board to the AI
			input = AIInput(rotatedBoard, totalTurns, winCase);

			//Converts to input from to rotated board to the unrotated board
			input = ConvertInputFromRotation(input, rotateAmount);

		}
		else {
			//player input
			input = PlayerInput(board, activePlayer);
		}

		//succsesfull input logic
		board[input - 1] = activePlayer;	
		
		//win check and what happens if a win is detected
		if (WinCheck(board)){
			system("cls");
			DrawBoard(board);
			std::cout << "Player " << activePlayer << " has won!" << std::endl;
			system("pause");
			break; // break the game loop and return to menu
		}
		
		//add one to the total turns each turn
		totalTurns++;

		//if 9 turns is taken, and nobody with this round, its always a draw
		if (totalTurns == 9)
		{
			system("cls");
			DrawBoard(board);
			std::cout << "It's a draw!" << std::endl;
			system("pause");
			break; // break the game loop and return to menu
		}

		//Switches the active player at the end of turn
		SwitchActivePlayer(activePlayer);
	}
}

std::vector<char> RotateBoard90Deg(std::vector<char> a_board) {
	//Hardcoded way to rotate board 90 degres

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

	return a_board; //returns rotated board
}

void DrawBoard(std::vector<char> a_board) {
	//Draws the board

	for (int i = 0; i < 3; i++) // goes though each collum (outside vector)
	{
		std::cout << ' ';
		for (int j = 0; j < 3; j++) // goes though each item in collum (inner vector)
		{
			std::cout << a_board[(2 - i) * 3 + j]; // draws the bort from the last collum element and downwards (so it matches the numpad)
			if (j < 2) {
				std::cout << " | ";
			}
		}
		if (i < 2) {
			std::cout << std::endl << "---|---|---" << std::endl;
		}
	}

	std::cout << std::endl << std::endl; // two endline to ensure space to next text in console
}

void SwitchActivePlayer(char& a_activePlayer) {
	//switches between 'X' and 'O' for each call of this function
	if (a_activePlayer == 'X') {
		a_activePlayer = 'O';
	}
	else if (a_activePlayer == 'O') {
		a_activePlayer = 'X';
	}
	else {
		std::cout << "INVALID ACTIVE PLAYER, defualting to 'X' as active player" << std::endl;
		a_activePlayer = 'X';
		system("pause");
		system("cls");
	}
}

int PlayerInput(std::vector<char> a_board, char a_activePlayer) {
	// checking that the answer is inside the array/board length
	int input{};
	bool acceptedAns = false;
	while (!acceptedAns) // loop incase invalid answer, then ask again
	{
		std::cin >> input; // actual playerinput
		ClearCin();

		acceptedAns = true;
		if (input >= 1 && input <= 9) { // is input is in range
			if (a_board[input - 1] == 'X' || a_board[input - 1] == 'O') { // if input is invalid, on an 'X' or 'O'
				system("cls");
				DrawBoard(a_board);
				std::cout << "Space alleready taken, please try again" << std::endl;
				std::cout << a_activePlayer << "'s turn : ";
				acceptedAns = false;
			}
		}
		else { // If input is valid, over 9 or under 1
			system("cls");
			DrawBoard(a_board);
			std::cout << "Invalid answer, please input again: " << std::endl;
			std::cout << a_activePlayer << "'s turn : ";

			acceptedAns = false;
		}
	}
	return input;
}

void ResetBoard(std::vector<char>& a_board) {
	//forloop for copying the global boardblueprint to inputted board
	for (int i = 0; i < a_board.size(); i++)
	{
		a_board[i] = boardBlueprint[i];
	}
}

bool WinCheck(std::vector<char> a_board) {
	// cheking the rows
	for (int i = 0; i < 3; i++)
	{
		//Cheks if each element in one row matches eachother
		// the i*3 gives the correct row.
		//example if i = 1, i*3 is 3, which is the first element on row 2,
		//then add 0, 1, 2 to get the next elements int that row
		if (a_board[i * 3 + 0] == a_board[i * 3 + 1] && a_board[i * 3 + 1] == a_board[i * 3 + 2]) {
			return true;
		}
	}

	//checking the collums
	for (int i = 0; i < 3; i++)
	{
		//Checks if each element in one collum matches eachother
		//the i gives the correct collum
		//example i = 1, i + 0 is 1, i + 3 is 4 whitch is the item above the previous one
		if (a_board[0 + i] == a_board[3 + i] && a_board[3 + i] == a_board[6 + i]){
			return true;
		}
	}

	//checking the / diagonal

	//checks each element in each diagonal if it matches eachother
	if (a_board[0] == a_board[4] && a_board[4] == a_board[8]){
		return true;
	}
	//checking \\ 
	if (a_board[2] == a_board[4] && a_board[4] == a_board[6]){
		return true;
	}

	return false;
}

void ClearCin() {
	std::cin.clear();    //Clears eventual errors from buffer
	std::cin.ignore(32767, '\n');    //clears the buffer if anything is there
}

int AIInput(std::vector<char> a_board, int turn, bool winCase) {
	if (turn == 0){
		return 5;
	}

	//AI input when the current path (wincase) is garranteed win
	if (winCase)
	{
		switch (turn)
		{
		case 2:
			return 9;
			break;

		case 4: 
			if (a_board[0] == 'O'){ // if 'O' inputted optimaly
				return 3;
			}
			else{ // if 'O' didn't input optimally, this results in a win
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
	else //AI input when the current path (wincase) is tie/draw
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
			else{
				return 8;
			}
			break;

		default:
			break;
		}
	}
}

int ConvertInputFromRotation(int rotIntput, int a_rotateAmount) {
	

	//creates a new defualt board and rotates it so it matches the AI's veiw
	std::vector<char> coverntBoard = boardBlueprint;

	for (int i = 0; i < a_rotateAmount; i++)
	{
		coverntBoard = RotateBoard90Deg(coverntBoard);
	}

	// inputs the X where the AI wanted to place it on the rotated board
	coverntBoard[rotIntput - 1] = 'X';

	//rotates the board back to the original rotation (the rotation the player sees)
	for (int i = 0; i < 4 - a_rotateAmount; i++)
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

int HowManyRotations(std::vector<char> a_board, bool& a_winCase){
	//checking all corners for where O places and return acording info -> how many rotations and wincase
	int rotAmount{};
	if (a_board[6] == 'O') {
		rotAmount = 3;
		a_winCase = false;
	}
	else if (a_board[8] == 'O') {
		rotAmount = 2;
		a_winCase = false;
	}
	else if (a_board[2] == 'O') {
		rotAmount = 1;
		a_winCase = false;
	}
	else if (a_board[0] == 'O') {
		rotAmount = 0;
		a_winCase = false;
	}

	//checking all edges for where O places and return acording info -> how many rotations and wincase
	if (a_board[3] == 'O') {
		rotAmount = 3;
		a_winCase = true;
	}
	else if (a_board[7] == 'O') {
		rotAmount = 2;
		a_winCase = true;
	}
	else if (a_board[5] == 'O'){
		rotAmount = 1;
		a_winCase = true;
	}
	else if (a_board[1] == 'O'){
		rotAmount = 0;
		a_winCase = true;
	}
	return rotAmount;
}