#include <iostream>
using namespace std;
void makeAMove(char[3][3], char);
bool isWon(char, char[3][3]);
bool isDraw(char[3][3]);
void displayBoard(char[3][3]);


int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {

		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);

		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	return 0;
}

void displayBoard(char array[3][3])
{
	for (size_t i = 0; i < sizeof(array[0]); i++)
	{
		cout << "-------------" << endl;
		for (size_t j = 0; j < sizeof(array[0]); j++)
		{
			cout << "| " << array[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << "-------------" << endl;

}

bool isWon(char player, char array[3][3])
{
	if (array[0][0] == player && array[0][1] == player && array[0][2] == player) {
		return true;
	}
	else if (array[1][0] == player && array[1][1] == player && array[1][2] == player) {
		return true;
	}
	else if (array[2][0] == player && array[2][1] == player && array[2][2] == player) {
		return true;
	}
	else if (array[0][0] == player && array[1][0] == player && array[2][0] == player) {
		return true;
	}
	else if (array[0][1] == player && array[1][1] == player && array[2][1] == player) {
		return true;
	}
	else if (array[0][2] == player && array[1][2] == player && array[2][2] == player) {
		return true;
	}
	else if (array[0][0] == player && array[1][1] == player && array[2][2] == player) {
		return true;
	}
	else if (array[2][0] == player && array[1][1] == player && array[0][2] == player) {
		return true;
	}

	return false;
}

bool isDraw(char array[3][3])
{
	for (size_t i = 0; i < sizeof(array[0]); i++)
	{
		for (size_t j = 0; j < sizeof(array[0]); j++)
			if (array[i][j] == ' ') {
				return false;
			}
	}
	return true;
}

void makeAMove(char array[3][3], char player)
{
	while (true) {
		int row;
		int column;
		cout << "Enter a row (0, 1, 2) for player " << player << "   : ";
		cin >> row;
		cout << "Enter a column (0, 1, 2) for player " << player << "   : ";
		cin >> column;
		if (array[row][column] == ' ') {
			array[row][column] = player;
			cout << endl;
			break;
		}
		else {
			cout << "This cell is already occupied. Try a different cell" << endl;
		}
		
	}

}