#include "ConnectFourView.h"
#include<iostream>
using namespace std;
void ConnectFourView::PrintBoard(std::ostream &s) const{
	cout << "0 1 2 3 4 5 6 " << endl;
	for (int x = 0; x < BOARD_SIZEX; x++) {
		//cout  << ";
		for (int y = 0; y < BOARD_SIZEY; y++) {
			if (mConnectFourBoard->mBoard[x][y] == mConnectFourBoard->EMPTY) {
				cout << "_ ";
			}
			else if (mConnectFourBoard->mBoard[x][y] == mConnectFourBoard->Y) {
				cout << "Y ";
			}
			else if (mConnectFourBoard->mBoard[x][y] == mConnectFourBoard->R) {
				cout << "R ";
			}
		}
		cout << endl;
	}
}
