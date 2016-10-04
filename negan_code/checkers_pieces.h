/*
Date:				4 May 2016
Authour:			Nathan Egan
Filename:			checkers_pieces.h
Latest Edit:		4 May 2016
File Description:	header for the four checkers pieces. There are four classes here, all similar and
	simple enough I thought they warranted being put in one file. All are derived from piece class
*/

#ifndef CHECKERS_PIECES_H
#define CHECKERS_PIECES_H

#include "piece.h"

class empty_piece: public piece
{
public:
	empty_piece()
	{pt = EMPTY;
	 pnum = 0;} //constructor
	
	bool is_legal(const std::string &move) const;
	bool legal_jump(const std::string& move) const;
	void output() const {std::cout << "   ";} 
	piece *clone() const {return new empty_piece(*this);}
};

class red_piece: public piece
{
public:
	red_piece()
	{pt = RED;
	 pnum = 0;} //constructor
	
	bool is_legal(const std::string &move) const;
	bool legal_jump(const std::string& move) const;
	void output() const {std::cout << "\e[31m" << " O " << "\e[0m";} 
	piece *clone() const {return new red_piece(*this);}
};

class red_king: public piece
{
public:
	red_king(){pt = RED_KING;
	 pnum = 0;} //constructor
	
	bool is_legal(const std::string &move) const;
	bool legal_jump(const std::string& move) const;
	void output() const {std::cout << "\e[31m" << " K " << "\e[0m";} 
	piece *clone() const {return new red_king(*this);}
};

class black_piece: public piece
{
public:
	black_piece(){pt = BLACK;
	 pnum = 0;} //constructor
	
	bool is_legal(const std::string &move) const;
	bool legal_jump(const std::string& move) const;
	void output() const {std::cout << "\e[30m" << " O " << "\e[0m";} 
	piece *clone() const {return new black_piece(*this);}
};

class black_king: public piece
{
public:
	black_king(){pt = BLACK_KING;
	 pnum = 0;} //constructor
	
	bool is_legal(const std::string &move) const;
	bool legal_jump(const std::string& move) const;
	void output() const {std::cout << "\e[30m" << " K " << "\e[0m";} 
	piece *clone() const {return new black_king(*this);}
};


#endif