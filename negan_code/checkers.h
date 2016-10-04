/*
Date:				3 May 2016
Authour:			Nathan Egan
Filename:			checkers.h
Latest Edit:		19 August 2016
File Description:	header file for checkers class, which wil implement a fully functioning checkers
	game intended for use with multiboard class. 
*/

#ifndef CHECKERS_H
#define CHECKERS_H

#include "checkers_pieces.h" //this class will give the individual pieces on the board
#include <queue>

class checkers
{
public:
	enum players {P1, P2, COMP, COMP2};

	checkers();
	~checkers();
	checkers(const checkers &other);
	checkers operator = (const checkers &other); 
	
	void output() const; //will display the entire board
	void make_move(const std::string &move); //will move one piece
	bool legal(const std::string &move) const; //check if move is legal

	//displays info about black player
	void black_info_display() const;
	//red version of above function
	void red_info_display() const;
	//plays the game until it ends
	void play();
	//checks if the game is over
	bool is_game_over() const;
	//allows the creation of a non-standard board
	void test_board();
	//determines if a forced jump needs to be made
	bool force_jump() const;
	//determines if a specific piece has a jump available
	bool force_jump(const int& a, const int& b) const;
	//These will check if a specific piece needs to make a forced jump
	bool black_forced_jump(const int& a,const int& b) const;
	bool bking_forced_jump(const int& a,const int& b)const;
	bool red_forced_jump(const int& a,const int& b)const;
	bool rking_forced_jump(const int& a,const int& b)const;
	//these will check if a given move is a legal jump
	bool legal_jump(const std::string& move) const;
	bool red_legal_jump(const std::string& move) const;
	bool black_legal_jump(const std::string& move) const;
	//stuff
	void endgame() const;
	void display_menu ();
	void new_board();
	void switch_player();
	//AI functions
	int evaluate() const {return (num_red + (2 * num_red_kings)) - (num_black + (2 * num_black_kings));}
	void all_possible_red_moves(std::queue<std::string> &moves) const;
	void all_possible_black_moves(std::queue<std::string> &moves) const;
	void comp_make_move();
	void comp_make_red_move();
	int red_evaluate_possibilities(int levels, int highest);
	void comp_make_black_move();
	int black_evaluate_possibilities(int levels, int lowest);
private:
	piece* board[8][8];
	int red_locations[12][2];
	int black_locations[12][2];
	int num_red;
	int num_black;
	int num_red_kings;
	int num_black_kings;
	int num_turns;
	int num_levels;
	players current_player, other_player;
};

//helper function to convert move string to integers
void move_to_int(const std::string& move, int &a, int &b, int &x, int &y);
//helper function to build a string out of characters
std::string make_string(char a, char b, char c, char d);
#endif
