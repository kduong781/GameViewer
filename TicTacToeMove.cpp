#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include <iostream>
#include <sstream>
#include <string>
int TicTacToeMove::mOnHeap = 0;
TicTacToeMove::TicTacToeMove(){
	mRow = -1;
	mCol = -1;
}
TicTacToeMove::TicTacToeMove(int row, int col) {
	mRow = row;
	mCol = col;
}
GameMove& TicTacToeMove::operator=(const std::string &lhs) {

	if (lhs == "quit") {
		mRow = -1;
		mCol = -1;
	}
	else {
		std::string row = lhs.substr(lhs.find('(') + 1);
		char temp;
		std::istringstream pars(row);
		pars >> mRow >> temp >> mCol;

	}
	return *this;

}
bool TicTacToeMove::Equals(const GameMove &other) const {
	const TicTacToeMove *move = dynamic_cast<const TicTacToeMove *>(&other);
	return (mRow == move->mRow && mCol == move->mCol) ? true : false;
}


TicTacToeMove::operator std::string() const {
	std::ostringstream str;
	str << "(" << mRow << "," << mCol << ")";
	return str.str();
}
