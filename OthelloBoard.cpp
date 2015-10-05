#include "OthelloBoard.h"
#include <iostream>
OthelloBoard::OthelloBoard() {
	mNextPlayer = BLACK;
	mValue = 0;
	mPassCount = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			mBoard[i][j] = EMPTY;
		}
	}
	mBoard[3][3] = WHITE;
	mBoard[4][4] = WHITE;
	mBoard[4][3] = BLACK;
	mBoard[3][4] = BLACK;
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
void OthelloBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {

	char flip = (this->mNextPlayer == BLACK ? WHITE : BLACK);
	for (int x1 = 0; x1 < BOARD_SIZE; x1++) {
		for (int y1 = -0; y1 < BOARD_SIZE; y1++) {
			if (mBoard[x1][y1] == EMPTY) {
				for (int row = -1; row < 2; row++) {
					for (int column = -1; column < 2; column++) {
						int x = x1, y = y1, opposite = 0;
						for (;;) {
							x += row;
							y += column;
							if (mBoard[x][y] == EMPTY || !(InBounds(x, y))) {
								break;
							}
							else if (mBoard[x][y] == mNextPlayer) {
								while (opposite > 0){
									int counter = 0; x -= row;	y -= column;
									list->push_back(new OthelloMove(x1, y1));
									column = 2;
									row = 2;
									opposite--;
								}
								break;
							}
							else {
								opposite++;
							}

						}
					}
				}
			}
		}
	}//*/
	list->size() == 0 ? list->push_back(new OthelloMove()) : false;
	//}
}


/*
Applies a valid move to the bodard, updating the board state accordingly.
You may assume that this move is valid, and is consistent with the list
of possible moves returned by GetAllMoves. Make sure you account for changes
to the current player, pass count, and board value.
*/
void OthelloBoard::ApplyMove(GameMove *move) {
	OthelloMove *m = dynamic_cast<OthelloMove*>(move);
	if (m->mRow == -1 && m->mCol == -1) {
		mPassCount++;
		mNextPlayer == WHITE ? mNextPlayer = BLACK : mNextPlayer = WHITE;

	}
	else {
		mPassCount = 0;
		char flip = (mNextPlayer == BLACK ? WHITE : BLACK);
		mBoard[m->mRow][m->mCol] = mNextPlayer;

		mValue = mValue + mNextPlayer;
		for (int row = -1; row < 2; row++) {
			for (int column = -1; column < 2; column++) {
				if (mBoard[m->mRow + row][m->mCol + column] == flip) {
					int x = m->mRow + row, y = m->mCol + column, count = 0;
					for (;;) {
						x += row;
						y += column;
						count++;
						if (mBoard[x][y] == EMPTY || !(InBounds(x, y))) {
							break;
						}
						if (mBoard[x][y] == mNextPlayer) {
							m->AddFlipSet(OthelloMove::FlipSet(count, row, column));
							x = m->mRow, y = m->mCol;
							for (int z = 0; z < count; z++) {
								mValue = mValue + (mNextPlayer * 2);
								mBoard[x += row][y += column] = mNextPlayer;
								OthelloMove::FlipSet(count, x, y);
							}
							break;
						}
					}
				}
			}

		}
		this->mHistory.push_back(move);
		mNextPlayer == WHITE ? mNextPlayer = BLACK : mNextPlayer = WHITE;
	}

}

/*
Undoes the last move applied to the board, restoring it to the state it was
in prior to the most recent move (including whose turn it is, what the
board value is, and what the pass count is).
*/
void OthelloBoard::UndoLastMove() {
	mPassCount--;
	if (mHistory.size() > 0) {
		mNextPlayer == WHITE ? mNextPlayer = BLACK : mNextPlayer = WHITE; // black
		char flip = (mNextPlayer == BLACK ? WHITE : BLACK);
		//GameMove *move = this->mHistory.back();
		GameMove *m = this->mHistory.back();
		OthelloMove *move = dynamic_cast<OthelloMove *>(m);
		int size = mHistory.size();
		int x = move->mRow;
		int y = move->mCol;
		mBoard[move->mRow][move->mCol] = EMPTY;
		mValue = mValue + flip;
		for (int a = 0; a < move->mFlips.size(); a++) {
			x = move->mRow;
			y = move->mCol;
			for (int z = 0; z < move->mFlips.at(a).switched; z++) {
				mValue = mValue + (flip * 2);
				mBoard[x += move->mFlips.at(a).rowDelta]
					[y += move->mFlips.at(a).colDelta] = flip;
			}
		}
		delete mHistory.back();
		this->mHistory.pop_back();
	}

}



		//GameMove *m = this->mHistory.back();
		//OthelloMove *move = dynamic_cast<OthelloMove *>(m);




