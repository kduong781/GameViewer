#include "ConnectFourBoard.h"
#include <iostream>
ConnectFourBoard::ConnectFourBoard() {
	mNextPlayer = Y;
	mValue = 0;
	mPassCount = 0;
	for (int i = 0; i < BOARD_SIZEX; i++) {
		for (int j = 0; j < BOARD_SIZEY; j++) {
			mBoard[i][j] = EMPTY;
		}
	}
}

/*
Fills in a vector with all possible moves on the current board state for
the current player. The moves should be ordered based first on row, then on
column. Example ordering: (0, 5) (0, 7) (1, 0) (2, 0) (2, 2) (7, 7)
If no moves are possible, then a single OthelloMove representing a Pass is
put in the vector.
Any code that calls ApplyMove is responsible for first checking that the
requested move is among the possible moves reported by this function.

Precondition: the vector is empty.
Postcondition: the vector contains all valid moves for the current player.
*/
void ConnectFourBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
	for (int y1 = 0; y1 < BOARD_SIZEY; y1++) {
	for (int x1 = 0; x1 < BOARD_SIZEX; x1++) {
		if (mBoard[x1][y1] == EMPTY) {

			list->push_back(new ConnectFourMove(x1,y1));
			break;
		}
				//list->size() == 0 ? list->push_back(new ConnectFourMove()) : false;
			}
		}
	}
//}


/*
Applies a valid move to the bodard, updating the board state accordingly.
You may assume that this move is valid, and is consistent with the list
of possible moves returned by GetAllMoves. Make sure you account for changes
to the current player, pass count, and board value.
*/
void ConnectFourBoard::ApplyMove(GameMove *move) {
	int pConsec = 0; //player
	int cConsec = 0; // computer
	int four = 4;
	ConnectFourMove *m = dynamic_cast<ConnectFourMove*>(move);
	if (m->mCol == -1) {
		mPassCount = 2;
		mNextPlayer == R ? mNextPlayer = Y : mNextPlayer = R;
	//	delete m;
	}

	else {
		mValue++;
		
		mPassCount = 0;
		for (int x = BOARD_SIZEX - 1; x > 0; x--) {
			if (mBoard[x][m->mCol] == EMPTY) {
				//std::cout << x << "mcol " << m->mCol << std::endl;
				mBoard[x][m->mCol] = mNextPlayer;
				mValue = mNextPlayer;
				for (int x1 = 0; x1 < BOARD_SIZEX; x1++) {
					for (int y1 = 0; y1 < BOARD_SIZEY; y1++)
						for (int row = -1; row < 2; row++) {
							for (int column = -1; column < 2; column++) {
								int x = x1, y = y1, pConsec = 0, cConsec = 0, counter = 0, tempX = -1, tempY = -1;
								bool check = false;
								while (check == false) {
									while (mBoard[x][y] == mNextPlayer && x >= 0 && y >= 0) {
										if (mBoard[x][y] == mNextPlayer && x >= 0 && y >= 0) {
											if ((x >= 0 && x<BOARD_SIZEX) && (y >= 0 && y<BOARD_SIZEY)) {
												pConsec++;
											}
											tempX = x, tempY = y;
											x = x + row;
											y = y + column;
											if (tempX == x && tempY == y && x >= 0 && y >= 0) {
												pConsec--;
												break;
											}
										}
										if (pConsec == four) {
											mPassCount = 2;
							
											check = true;
										}
									}

									x += row;
									y += column;
									counter++;
									if (counter>BOARD_SIZEY*BOARD_SIZEX) {
										break;
									}

								}
							}
						}
				}
				m->mRow = x;
				GameMove *edit = dynamic_cast<GameMove*>(m);
				this->mHistory.push_back(edit);
				if (mPassCount == 2) {
					if (mNextPlayer == 1) {
						std::cout << "Y is the winner!" << std::endl;
					}
					else {
						std::cout << "R is the winner!" << std::endl;
					}
				}
				if (mValue == BOARD_SIZEX*BOARD_SIZEY) {
					mPassCount = 2;
					std::cout << "It's a tie!" << std::endl;
				}
				mNextPlayer == R ? mNextPlayer = Y : mNextPlayer = R;
				//std::cout << "TESST!!!!";
				break;
			}

		}

	}
}

/*
Undoes the last move applied to the board, restoring it to the state it was
in prior to the most recent move (including whose turn it is, what the
board value is, and what the pass count is).
*/
void ConnectFourBoard::UndoLastMove() {
	mPassCount--;
	if (mHistory.size() > 0) {
		mNextPlayer == R ? mNextPlayer = Y : mNextPlayer = R; // black
		char flip = (mNextPlayer == Y ? R : Y);
		//GameMove *move = this->mHistory.back();
		GameMove *m = this->mHistory.back();
		ConnectFourMove *move = dynamic_cast<ConnectFourMove *>(m);
		int size = mHistory.size();
		int x = move->mRow;
		int y = move->mCol;
		mBoard[move->mRow][move->mCol] = EMPTY;
		mValue--;
		delete mHistory.back();
		this->mHistory.pop_back();
	}

}



//GameMove *m = this->mHistory.back();
//OthelloMove *move = dynamic_cast<OthelloMove *>(m);




