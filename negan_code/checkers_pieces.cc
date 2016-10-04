/*
Date:				4 May 2016
Authour:			Nathan Egan
Filename:			checkers_pieces.cc
Latest Edit:		4 May 2016
File Description:	implementation for the four checkers pieces. There are five classes here, all similar and
	simple enough I thought they warranted being put in one file. All are derived from piece class
*/

#include"checkers_pieces.h"

using namespace std;

/*  is_legal functions: each will check a move to see if the piece is allowed to move like that. general
	conditions are covered in the parent is_legal, the functions below cover specific cases. A summary will 
	be provided	in individual comments above each function. legal_jump functions check for jumping over
	an opponents piece*/

//an empty piece can never be moved. 	
bool empty_piece::is_legal(const string &move) const
{
	cout << "There is no piece in that spot.\n";
	return false;
}

bool empty_piece::legal_jump(const string & move) const
{
	cout << "There is no piece in that spot. \n";
	return false;
}


bool red_piece::is_legal(const string &move) const
{
	//checks that it is only moving one space left or right, and one space down
	if((move[0] - move[2] != -1 && move[0] - move[2] != 1) || move[1] - move[3] != -1)
	{
		cout << "You cannot move to that space\n";
		return false;
	}
	return true;
}

bool red_piece::legal_jump(const string &move) const
{
	//checks that it is only moving two space left or right, and two space down
	if((move[0] - move[2] != -2 && move[0] - move[2] != 2) || move[1] - move[3] != -2)
	{
		cout << "There is a jump available you must take\n";
		return false;
	}
	return true;
}


bool red_king::is_legal(const string &move) const
{
	//checks that it is only moving one space left or right, and one space up or down
	if((move[0] - move[2] != -1 && move[0] - move[2] != 1) || (move[1] - move[3] != -1 && move[1] - move[3] != 1))
	{
		cout << "You cannot move to that space\n";
		return false;
	}
return true;
}

bool red_king::legal_jump(const string &move) const
{
	//checks that it is only moving two space left or right, and two space up or down
	if((move[0] - move[2] != -2 && move[0] - move[2] != 2) || (move[1] - move[3] != -2 && move[1] - move[3] != 2))
	{
		cout << "There is a jump available you must take\n";
		return false;
	}
return true;
}


bool black_piece::is_legal(const string &move) const
{
	//checks that it is only moving one space left or right, and one space up
	if((move[0] - move[2] != -1 && move[0] - move[2] != 1) || move[1] - move[3] != 1)
	{
		cout << "You cannot move to that space\n"  << endl;
		return false;
	}
	return true;
}

bool black_piece::legal_jump(const string &move) const
{
	//checks that it is only moving two space left or right, and two space up
	if((move[0] - move[2] != -2 && move[0] - move[2] != 2) || move[1] - move[3] != 2)
	{
		cout << "There is a jump available you must take\n";
		return false;
	}
	return true;
}


bool black_king::is_legal(const string &move) const
{
	//checks that it is only moving one space left or right, and one space up or down
	if((move[0] - move[2] != -1 && move[0] - move[2] != 1) || (move[1] - move[3] != -1 && move[1] - move[3] != 1))
	{
		cout << "You cannot move to that space\n";
		return false;
	}
	return true;
}

bool black_king::legal_jump(const string &move) const
{
	//checks that it is only moving two space left or right, and two space up or down
	if((move[0] - move[2] != -2 && move[0] - move[2] != 2) || (move[1] - move[3] != -2 && move[1] - move[3] != 2))
	{
		cout << "There is a jump available you must take\n";
		return false;
	}
	return true;
}
