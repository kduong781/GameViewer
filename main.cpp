#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include "TicTacToeView.h"
#include "ConnectFourBoard.h"
#include "ConnectFourView.h"
#include "ConnectFourMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "GameExceptions.h";
using namespace std;


int main(int argc, char* argv[]) {
	GameBoard *board;
	GameView *v;
	bool run = true;
	while (run) {
		std::cout << "1. Othello" << endl;
		std::cout << "2. Tic Tac Toe" << endl;
		std::cout << "3. Connect Four" << endl;
		int game;
		cin >> game;
		if (game == 1) {
			board = new OthelloBoard();
			v = new OthelloView(board);
		}
		else if (game == 2) {
			board = new TicTacToeBoard();
			v = new TicTacToeView(board);

		}
		else {
			board = new ConnectFourBoard();
			v = new ConnectFourView(board);
		}
		std::cout << endl << *v << endl;
		//cin >> game;
		//system("pause");
		string userInput;
		vector<GameMove *> possMoves;

		do {
			bool possible = true;
			//if (board->GetNextPlayer() == 1) {
					cout << board->GetPlayerString(board->GetNextPlayer()) << "'s turn" << endl;

			
			cout << "" << endl;
			board->GetPossibleMoves(&possMoves);
			for (int i = 0; i < possMoves.size(); i++) {
				cout << (string)*possMoves.at(i) << "  ";
				delete possMoves.at(i);
			}
			possMoves.clear();
			getline(cin, userInput);
			int sdf = userInput.find('m');
			if (userInput.find('m') == 0 || userInput.find("q") == 0) {

				GameMove *m = board->CreateMove();
				try {
					*m = userInput;
					board->GetPossibleMoves(&possMoves);
					bool check = false;
					if (userInput.find("q") == 0) {
						board->ApplyMove(m);
					}
					for (int i2 = 0; i2 < possMoves.size(); i2++) {
						if (*m == *possMoves.at(i2)){
							//cout << "testing if it goes through move!" << endl;
							board->ApplyMove(m);
							cout << endl << *v << endl;
							check = true;
						}

						delete possMoves.at(i2);
					}
					possMoves.clear();
					if (!check) {
						delete m;
					}
				}
				catch (GameException &e) {
					cout << e.what() << endl;
					delete m;
				}
			}
			if (userInput.find('u') == 0) {
				string undo = userInput.substr(userInput.find(' ') + 1);
				istringstream pars(undo);
				int x;
				pars >> x;
				for (int z = 0; z < x; z++){
					board->UndoLastMove();
				}
				cout << endl << *v << endl;
			}
			if (userInput == "showHistory"){
				const std::vector<GameMove *> *print = board->GetMoveHistory();
				int size = print->size();
				string s;
				for (int x = size - 1; x >= 0; x--) {
					x % 2 == 1 ? s = "White's Turn: " : s = "Black's Turn: ";
					cout << s << (string)*print->at(x) << endl;
				}
			}
			if (userInput == "showValue") {
				cout << "VALUE!!!!!!!!!!!!!!! " << board->GetValue() << endl;

			}


		} while (!board->IsFinished());
		//if (userInput.find('q') != 0) {
			for (int z = 0; z < 1000; z++){
				board->UndoLastMove();
			}
		//}
	}
}


