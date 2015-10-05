#include "OthelloMove.h"
#include "OthelloBoard.h"
#include <iostream>
#include <sstream>
#include <string>
int OthelloMove::mOnHeap = 0;
OthelloMove::OthelloMove(){
	mRow = -1;
	mCol = -1;
}
OthelloMove::OthelloMove(int row, int col) {
	mRow = row;
	mCol = col;
}
GameMove& OthelloMove::operator=(const std::string &lhs) {

	if (lhs == "move pass") {
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
bool OthelloMove::Equals(const GameMove &other) const {
	const OthelloMove *move = dynamic_cast<const OthelloMove *>(&other);
	return (mRow == move->mRow && mCol == move->mCol) ? true : false;
}


OthelloMove::operator std::string() const {
	std::ostringstream str;
	str << "(" << mRow << "," << mCol << ")";
	return str.str();
}
