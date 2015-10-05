#include "ConnectFourMove.h"
#include "ConnectFourBoard.h"
#include <iostream>
#include <sstream>
#include <string>
int ConnectFourMove::mOnHeap = 0;
ConnectFourMove::ConnectFourMove(){
	mRow = -1;
	mCol = -1;
}
ConnectFourMove::ConnectFourMove(int row, int col) {
	mRow = row;
	mCol = col;
}
GameMove& ConnectFourMove::operator=(const std::string &lhs) {

	if (lhs == "quit") {
		mRow = -1;
		mCol = -1;
	}
	else {
		std::string row = lhs.substr(lhs.find('e') + 2);
		char temp;
		std::istringstream pars(row);
		pars >> mCol;// >> temp >> mCol;

	}
	return *this;

}
bool ConnectFourMove::Equals(const GameMove &other) const {
	const ConnectFourMove *move = dynamic_cast<const ConnectFourMove *>(&other);
	return (mCol == move->mCol) ? true : false;
}


ConnectFourMove::operator std::string() const {
	std::ostringstream str;
	str << mCol;
	return str.str();
}
