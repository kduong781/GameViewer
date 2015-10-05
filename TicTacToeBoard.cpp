#include "TicTacToeBoard.h"
#include <iostream>
TicTacToeBoard::TicTacToeBoard() {
	mNextPlayer = X;
	mValue = 0;
	mPassCount = 0;
	for (int i = 0; i < BOARD_SIZE2; i++) {
		for (int j = 0; j < BOARD_SIZE2; j++) {
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
void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {

	for (int x1 = 0; x1 < BOARD_SIZE2; x1++) {
		for (int y1 = -0; y1 < BOARD_SIZE2; y1++) {
			if (mBoard[x1][y1] == EMPTY) {

				list->push_back(new TicTacToeMove(x1, y1));
				list->size() == 0 ? list->push_back(new TicTacToeMove()) : false;
			}
		}
	}
}


			/*
			Applies a valid move to the bodard, updating the board state accordingly.
			You may assume that this move is valid, and is consistent with the list
			of possible moves returned by GetAllMoves. Make sure you account for changes
			to the current player, pass count, and board value.
			*/
void TicTacToeBoard::ApplyMove(GameMove *move) {
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move);
	int pConsec = 0; //player
	int cConsec = 0; // 
	if (m->mRow == -1 && m->mCol == -1) {
		mPassCount = 2;
		mNextPlayer == O ? mNextPlayer = X : mNextPlayer = O;
		//delete m;
	}
	else {
	//	mPassCount = 0;
		mBoard[m->mRow][m->mCol] = mNextPlayer;
		this->mHistory.push_back(move);
		mValue++;
		bool check = false;
		char flip = (this->mNextPlayer == X ? O : X);
		for (int x1 = 0; x1 < BOARD_SIZE2; x1++) {
			for (int y1 = 0; y1 < BOARD_SIZE2; y1++)
				for (int row = -1; row < 2; row++) {
					for (int column = -1; column < 2; column++) {
						int x = x1, y = y1, pConsec = 0, cConsec = 0, counter = 0, tempX = -1, tempY = -1;
						check = false;
						while (check == false) {
							while (mBoard[x][y] == mNextPlayer && x>=0 && y >= 0) {
								if (mBoard[x][y] == mNextPlayer && x >= 0 && y >= 0) {
									if ((x >= 0 && x<BOARD_SIZE2) && (y >= 0 && y<BOARD_SIZE2)) {
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
									if (pConsec == BOARD_SIZE2) {
											mPassCount = 2;
										
										check = true;
									}
								}

								x += row;
							y += column;
							counter++;					
							if (counter>BOARD_SIZE2) {
								break;
							}
						
						}
					}
				}
		}
		if (mPassCount == 2) {
			if (mNextPlayer == 1) {
				std::cout << "X is the winner!" << std::endl;
			}
			else {
				std::cout << "O is the winner!" << std::endl;
			}
		}
		if (mValue == 9) {
			mPassCount = 2;
			std::cout << "It's a tie!" << std::endl;
		}
		mNextPlayer == O ? mNextPlayer = X : mNextPlayer = O;
	}

}
/*
Undoes the last move applied to the board, restoring it to the state it was
in prior to the most recent move (including whose turn it is, what the
board value is, and what the pass count is).
*/
void TicTacToeBoard::UndoLastMove() {
	mPassCount--;
	if (mHistory.size() > 0) {
		mNextPlayer == O ? mNextPlayer = X : mNextPlayer = O; // black
		char flip = (mNextPlayer == X ? O : X);
		//GameMove *move = this->mHistory.back();
		GameMove *m = this->mHistory.back();
		TicTacToeMove *move = dynamic_cast<TicTacToeMove *>(m);
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




