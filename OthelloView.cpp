#include "OthelloView.h"
#include<iostream>
using namespace std;
void OthelloView::PrintBoard(std::ostream &s) const{
	cout << "- 0 1 2 3 4 5 6 7" << endl;
	for (int x = 0; x < BOARD_SIZE; x++) {
		cout << x << " ";
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (mOthelloBoard->mBoard[x][y] == mOthelloBoard->EMPTY) {
				cout << ". ";
			}
			else if (mOthelloBoard->mBoard[x][y] == mOthelloBoard->BLACK) {
				cout << "B ";
			}
			else if (mOthelloBoard->mBoard[x][y] == mOthelloBoard->WHITE) {
				cout << "W ";
			}
		}
		cout << endl;
	}
}
