/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Name:		Robin Kelby
	Class:		CS 2401
	File:		checkers.h
	Description:	This is the interface file for the checkers 
			class
	Date:		4/7/15

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef MAIN_SAVITCH_CHECKERS
#define MAIN_SAVITCH_CHECKERS
#include "game.h"
#include "space.h"
#include <iostream>

namespace main_savitch_14 {
	class checkers:public game {
		public:

		checkers();

		void make_move(const std::string& move);
		void restart();
		game* clone()const;
		void compute_moves(std::queue<std::string>& moves);
		void display_status()const;
		int evaluate()const;
		bool is_legal(const std::string& move)const;
		bool is_game_over()const;
		
		//Added functions:
		game::who who_won();
		std::string move_2_to_string(int x1, int y1, int x2, int y2);
		std::string move_3_to_string(int x1, int y1, int x2, int y2, int x3, int y3);
		bool multi_jump_red(int x1, int y1, int x2, int y2) const;
		bool multi_jump_black(int x1, int y1, int x2, int y2) const;
	
		private:
		space board[8][8];
		game::who winner;
	};
}

#endif
