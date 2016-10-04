/*
Date:				3 May 2016
Authour:			Nathan Egan
Filename:			main.cc
Latest Edit:		3 May 2016
File Description:	main file for multiboard.cc
*/

#include "checkers.h"

using namespace std;
int main()
{
	checkers myc;
	myc.new_board();
	myc.play();

	return 0;
}