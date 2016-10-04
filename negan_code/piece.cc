/*
Date:				3 May 2016
Authour:			Nathan Egan
Filename:			piece.cc
Latest Edit:		4 May 2016
File Description:	implementation file for piece class, from which we will derive classes for individual 
	pieces for the multiboard class 
*/

#include "piece.h"

using namespace std;

//this function will check for illegalities that are not specific to one piece type, such as selecting 
	//an area not on the board
