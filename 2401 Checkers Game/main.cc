#include "game.h"
#include "checkers.h"
#include "space.h"
#include <iostream>
using namespace std;
using namespace main_savitch_14;

int main(){
	checkers mygame;
	game::who winner;
	bool choice = true;
	char c1;

	while(choice){
		winner = mygame.play();
		if(winner == game::HUMAN){
			cout << "Human has won" << endl;
		}
		else if(winner == game::COMPUTER){
			cout << "Computer has won" << endl;
		}
		else {
			cout << "Neither player has won" << endl;
		}
		cout << "Enter y to play again, n to quit" << endl;
		cin >> c1;
		if(c1 == 'y' || c1 == 'Y'){
			choice = true;
		}
		else {
			choice = false;
		}
		mygame.restart();
	}

	return 0;
}
