/*
Date:				3 May 2016
Authour:			Nathan Egan
Filename:			piece.h
Latest Edit:		3 May 2016
File Description:	header file for piece class, from which we will derive classes for individual 
	pieces for the multiboard class 
*/

#ifndef PIECE_H
#define PIECE_H

#include<string>
#include<iostream> //used in all the derived classes, so I put it here
#include<cctype> //used in both checkers.cc and piece.cc

class piece
{
public:
	enum piece_type {RED, RED_KING, BLACK, BLACK_KING, EMPTY}; 
	
	virtual ~piece() {}
	virtual bool is_legal(const std::string &move) const = 0; 
		//will determine whether or not a certain move is allowed
	virtual void output() const = 0;
		//will show what type of piece it is
	virtual bool legal_jump(const std::string& move) const = 0;
		//will be used for when it needs to jump another piece
	virtual piece *clone() const = 0;
		//returns a pointer to a new piece with the same attributes
	piece_type ptype() const {return pt;} 
		//will return the enumerated value
	void setnum(int x){pnum = x;}
		//will set the piece's number
	int getnum(){return pnum;}
		//will return the piece's number
protected:
	piece_type pt;
	int pnum; //this will allow us to keep track of each piece individually
};

#endif
