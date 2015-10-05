#include "TicTacToeView.h"
#include<iostream>
using namespace std;
void TicTacToeView::PrintBoard(std::ostream &s) const{
	cout << "- 0 1 2 " << endl;
	for (int x = 0; x < BOARD_SIZE2; x++) {
		cout << x << " ";
		for (int y = 0; y < BOARD_SIZE2; y++) {
			if (mTicTacToeBoard->mBoard[x][y] == mTicTacToeBoard->EMPTY) {
				cout << "_ ";
			}
			else if (mTicTacToeBoard->mBoard[x][y] == mTicTacToeBoard->X) {
				cout << "X ";
			}
			else if (mTicTacToeBoard->mBoard[x][y] == mTicTacToeBoard->O) {
				cout << "O ";
			}
		}
		cout << endl;
	}
}
