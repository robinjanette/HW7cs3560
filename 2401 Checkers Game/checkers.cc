/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Name:		Robin Kelby
	Class:		CS 2401
	File:		checkers.cc
	Description:	This is the implementation file for the checkers
			class
	Date:		4/7/15

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>
#include "colors.h"
#include "game.h"
#include "checkers.h"
#include "space.h"
using namespace std;

namespace main_savitch_14 {
/* * * * * * * * * *
Precondition: none
Postcondition: Creates an [8][8] array of spaces and sets the spaces to 
		have correct attributes
* * * * * * * * * */
checkers::checkers(){
	restart();
}

/* * * * * * * * * *
Precondition: none
Postcondition: Sets the board spaces with the correct attributes
* * * * * * * * * */
void checkers::restart(){
	int i = 0, j = 0;
	space::piece_color cn = space::NONE;
	//Sets playable and king accross the board
	while(i < 8){//Runs for each row of the board
		if(i%2 == 0){//Runs if the row is even
			j = 0;
			while(j < 8){//Runs for square in the row
				if(j%2 == 1){//Runs if space is odd
					board[i][j].set_playable(true);
					board[i][j].set_king(false);
					board[i][j].set_piece(false);
					board[i][j].set_piece_color(cn);
				}
				else {//Runs if space is even
					board[i][j].set_playable(false);
					board[i][j].set_king(false);
					board[i][j].set_piece(false);
					board[i][j].set_piece_color(cn);
				}
			j++;
			}
		}
		else {
			j = 0;
			while(j < 8){
				if(j%2 == 0){//Runs if space is even
					board[i][j].set_playable(true);
					board[i][j].set_king(false);
					board[i][j].set_piece_color(cn);
					board[i][j].set_piece(false);
				}
				else {//Runs if space is odd
					board[i][j].set_playable(false);
					board[i][j].set_king(false);
					board[i][j].set_piece(false);
					board[i][j].set_piece_color(cn);
				}
			j++;
			}
		}
		i++;
	}

	//Sets RED pieces
	i = 0;
	j = 0;
	cn = space::RED;
	while(i < 3){
		j = 0;
		while(j < 8){
			if(board[i][j].is_playable()){
				board[i][j].set_piece(true);
				board[i][j].set_piece_color(cn);
			}
			j++;
		}
		i++;
	}

	//Sets BLACK pieces
	i = 5;
	j = 0;
	cn = space::BLACK;
	while(i < 8){
		j = 0;
		while(j < 8){
			if(board[i][j].is_playable()){
				board[i][j].set_piece(true);
				board[i][j].set_piece_color(cn);
			}
			j++;
		}
		i++;
	}	
	game::restart();
}

/* * * * * * * * * *
Precondition: none
Postcondition: Displays the checkerboard to the screen
* * * * * * * * * */
void checkers::display_status()const{
	int i = 0, j = 0;
	cout << "   " << "  A  " << "  B  " << "  C  " << "  D  " << "  E  " << "  F  ";
		cout << "  G  " << "  H  " << endl;
	while(i < 8){
		cout << "   ";
		for(j = 0; j < 8; j++){
			if(board[i][j].is_playable()){
				cout << B_BLUE << "     " << RESET;
			}
			else {
				cout << B_GREEN << "     " << RESET;
			}
		}
		cout << RESET << endl;
		cout << " " << i + 1 << " ";
		for(j = 0; j < 8; j++){
			if(board[i][j].is_piece()){
				if(board[i][j].which_piece_color() == space::RED && !board[i][j].is_king()){
					cout << B_BLUE << "  " << RED << "@" << RESET << B_BLUE << "  " << RESET;
				}
				else if(board[i][j].which_piece_color()== space::RED && board[i][j].is_king()){
					cout << B_BLUE << "  " << RED << "K" << RESET << B_BLUE << "  " << RESET;
				}
				else if(board[i][j].which_piece_color() == space::BLACK && board[i][j].is_king()){
					cout << B_BLUE << "  " << BLACK << "K" << RESET << B_BLUE << "  " << RESET;	
				}
				else {
					cout << B_BLUE << "  " << BLACK << "@" << RESET << B_BLUE << "  " << RESET;
				}
			}
			else {
				if(board[i][j].is_playable()){
					cout << B_BLUE << "     " << RESET;
				}
				else {
					cout << B_GREEN << "     " << RESET;
				}
			}
		}
		cout << RESET << endl;
		cout << "   ";
		for(j = 0; j < 8; j++){
			if(board[i][j].is_playable()){
				cout << B_BLUE << "     " << RESET;
			}
			else {
				cout << B_GREEN << "     " << RESET;
			}
		}
		cout << RESET << endl;
		i++;
	}		
}

/* * * * * * * * * *
Precondition: a string move
Postcondition: Function checks to see if move is a legal move
* * * * * * * * * */
bool checkers::is_legal(const string& move)const{
	//move is of the form 1A2B or 1A2B3C
	int x1, y1, x2, y2;
	int x3, y3;
	if(move.size() < 4 || move.size() > 6){
		return false;//Move is not of correct form
	}
	x1 = int(move[0] - '1');
	y1 = int(toupper(move[1]) - 'A');
	x2 = int(move[2] - '1');
	y2 = int(toupper(move[3]) - 'A');
	bool multiple_jump = false;
	
	if(move.size() > 4 && move.size() <= 6){
		x3 = int(move[4] - '1');
		y3 = int(toupper(move[5]) - 'A');
		multiple_jump = true;
	}
		
	if(x1 < 0 || x1 > 7 || x1 < 0 || x1  > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7){
		return false;//Move is not on the board
	}

	if(multiple_jump && (x3 < 0 || x3 > 7 || y3 < 0 || y3 > 7)){
		return false;
	}

	if(!board[x1][y1].is_playable()){
		return false;//Move is not on a playable space
	}

	if(!board[x2][y2].is_playable()){
		return false;//Move is not on a playable space
	}

	if(!board[x1][y1].is_piece()){
		return false;//No piece on space
	}

	game::who next_mover_check = next_mover();
	if(board[x1][y1].which_piece_color() == space::RED && next_mover_check == HUMAN){
		return false;//Not the player's piece
	}

	if(board[x1][y1].which_piece_color() == space::BLACK && next_mover_check == COMPUTER){
		return false;//Not the player's piece
	}

	if(board[x1][y1].is_king()){
		if(!board[x2][y2].is_piece() && !multiple_jump){
			if(((x1+1 == x2)||(x1-1 == x2)) && ((y1+1 == y2)||(y1-1 == y2))){
				return(true);
			}
			else if(((y1+2 == y2)||(y1-2 == y2)) && ((x1+2 == x2)||(x1-2 == x2))){
				if(board[x1][y1].which_piece_color() == space::BLACK){
					if((x1+2==x2)&&(y1+2==y2)&& board[x1+1][y1+1].which_piece_color() == space::RED){
						return true;
					}
				  else if((x1+2==x2)&&(y1-2==y2)&& board[x1+1][y1-1].which_piece_color() == space::RED){
						return true;
					}
					else if((y1+2 == y2) && board[x1-1][y1+1].which_piece_color() == space::RED){
						return true;
					}
					else if((y1-2 == y2) && board[x1-1][y1-1].which_piece_color() == space::RED){
						return true;
					}
					else {
						return false;
					}
				}
				else {
				   if((x1+2==x2)&&(y1+2==y2)&& board[x1+1][y1+1].which_piece_color() == space::BLACK){
					return true;
					}
				else if((x1+2==x2)&&(y1-2==y2)&& board[x1+1][y1-1].which_piece_color() == space::BLACK){
					return true;
					}
				   else if((y1+2 == y2) && board[x1-1][y1+1].which_piece_color() == space::BLACK){
					return true;
					}
				   else if((y1-2 == y2) && board[x1-1][y1-1].which_piece_color() == space::BLACK){
					return true;
					}
				   else {
					return false;
					}
				}
			}
			else {
				return(false);
			}
		}
		else if(multiple_jump){
			if(board[x1][y1].which_piece_color() == space::RED){
				if(!board[x2][y2].is_piece() && !board[x3][y3].is_piece()){
					if(x1 == x3){
						if(y1 + 2 == y2){
							if(x1 + 2 == x2){
								if(multi_jump_black(x1+1, y1+1, x2-1, y2+1)){
									return true;
								}
								else {
									return false;
								}
							}
							else if(x1 - 2 == x2){
								if(multi_jump_black(x1-1, y1+1, x2+1, y2+1)){
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else if(y1 - 2 == y2){
							if(x1 + 2 == x2){
								if(multi_jump_black(x1+1, y1-1, x2-1, y2-1)){
									return true;
								}
								else {
									return false;
								}
							}
							else if(x1 - 2 == x2){
								if(multi_jump_black(x1-1, y1-1, x2+1, y2-1)){
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else if(y1 == y3){
						if(x1 + 2 == x2){
							if(y1 + 2 == y2){
								if(multi_jump_black(x1+1, y1+1, x2+1, y2-1)){
									return true;
								}
								else {
									return false;
								}
							}
							else if(y1 - 2 == y2){
								if(multi_jump_black(x1+1, y1-1, x2+1, y2+1)){
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else if(x1 - 2 == x2){
							if(y1 + 2 == y2){
								if(multi_jump_black(x1-1, y1+1, x2-1, y2-1)){
									return true;
								}
								else {
									return false;
								}
							}
							else if(y1 - 2 == y2){
								if(multi_jump_black(x1-1, y1-1, x2-1, y2+1)){
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else if(x1 + 4 == x3){
						if(y1 + 4 == y3){
							if(multi_jump_black(x1+1, y1+1, x2+1, y2+1)){
								return true;
							}
							else {
								return false;
							}
						}
						else if(y1 - 4 == y3){
							if(multi_jump_black(x1+1, y1-1, x2+1, y2-1)){
								return true;
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else if(x1 - 4 == x3){
						if(y1 + 4 == y3){
							if(multi_jump_black(x1-1, y1+1, x2-1, y2+1)){
								return true;
							}
							else {
								return false;
							}
						}
						else if(y1 - 4 == y3){
							if(multi_jump_black(x1-1, y1-1, x2-1, y2-1)){
								return true;
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else if(board[x1][y1].which_piece_color() == space::BLACK){
				if(!board[x2][y2].is_piece() && !board[x3][y3].is_piece()){
					if(x1 == x3){
						if(y1 + 2 == y2){
							if(x1 + 2 == x2){
								if(multi_jump_red(x1+1, y1+1, x2-1, y2+1)){
									return true;
								}
								else {
									return false;
								}
							}
							else if(x1 - 2 == x2){
								if(multi_jump_red(x1-1, y1+1, x2+1, y2+1)){
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else if(y1 - 2 == y2){
							if(x1 + 2 == x2){
								if(multi_jump_red(x1+1, y1-1, x2-1, y2-1)){
									return true;
								}
								else {
									return false;
								}
							}
							else if(x1 - 2 == x2){
								if(multi_jump_red(x1-1, y1-1, x2+1, y2-1)){
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else if(y1 == y3){
						if(x1 + 2 == x2){
							if(y1 + 2 == y2){
								if(multi_jump_red(x1+1, y1+1, x2+1, y2-1)){
									return true;
								}
								else {
									return false;
								}
							}
							else if(y1 - 2 == y2){
								if(multi_jump_red(x1+1, y1-1, x2+1, y2+1)){
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else if(x1 - 2 == x2){
							if(y1 + 2 == y2){
								if(multi_jump_red(x1-1, y1+1, x2-1, y2-1)){
									return true;
								}
								else {
									return false;
								}
							}
							else if(y1 - 2 == y2){
								if(multi_jump_red(x1-1, y1-1, x2-1, y2+1)){
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else if(x1 + 4 == x3){
						if(y1 + 4 == y3){
							if(multi_jump_red(x1+1, y1+1, x2+1, y2+1)){
								return true;
							}
							else {
								return false;
							}
						}
						else if(y1 - 4 == y3){
							if(multi_jump_red(x1+1, y1-1, x2+1, y2-1)){
								return true;
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else if(x1 - 4 == x3){
						if(y1 + 4 == y3){
							if(multi_jump_red(x1-1, y1+1, x2-1, y2+1)){
								return true;
							}
							else {
								return false;
							}
						}
						else if(y1 - 4 == y3){
							if(multi_jump_red(x1-1, y1-1, x2-1, y2-1)){
								return true;
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		if(board[x1][y1].which_piece_color() == space::RED && !multiple_jump){
			if(((y1 + 1 == y2) || (y1 - 1 == y2)) && (x1 + 1 == x2) && !board[x2][y2].is_piece()){
				return true;
			}
			else if(((y1 + 2 == y2) || (y1 - 2 == y2)) && (x1 + 2 == x2) && !board[x2][y2].is_piece()){
				if((y1 + 2 == y2) && board[x1 + 1][y1 + 1].which_piece_color() == space::BLACK){
					return true;
				}
				else if((y1 - 2 == y2) && board[x1 + 1][y1 - 1].which_piece_color() == space::BLACK){
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else if(board[x1][y1].which_piece_color() == space::BLACK && !multiple_jump){
			if(((y1 + 1 == y2) || (y1 - 1 == y2)) && (x1 - 1 == x2) && !board[x2][y2].is_piece()){
				return true;
			}
			else if(((y1 + 2 == y2) || (y1 - 2 == y2)) && (x1 - 2 == x2) && !board[x2][y2].is_piece()){
				if((y1 + 2 == y2) && board[x1 - 1][y1 + 1].which_piece_color() == space::RED){
					return true;
				}
				else if((y1 - 2 == y2) && board[x1 - 1][y1 - 1].which_piece_color() == space::RED){
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else if(board[x1][y1].which_piece_color() == space::RED && multiple_jump){
			
			if(!board[x2][y2].is_piece() && !board[x3][y3].is_piece()){
				if((x1 + 4 == x3) && ((y1 + 4 == y3)||(y1 - 4 == y3))){
					if(y1+4 == y3){
						if(board[x1 + 1][y1 + 1].which_piece_color() == space::BLACK &&
							board[x2 + 1][y2 + 1].which_piece_color() == space::BLACK){
							return true;
						}
						else {
							return false;
						}
					}
					else if(y1 - 4 == y3){
						if(board[x1 + 1][y1 - 1].which_piece_color() == space::BLACK &&
							board[x2 + 1][y2 - 1].which_piece_color() == space::BLACK){
							return true;
						}
						else {
							return false;
						}
					}
				}
				else if((x1 + 4 == x3) && (y1 == y3)){
					if(y1 + 2 == y2){
						if(board[x1 + 1][y1 + 1].which_piece_color() == space::BLACK &&
							board[x2 + 1][y2 - 1].which_piece_color() == space::BLACK){
							return true;
						}
						else {
							return false;
						}
					}
					else if(y1 - 2 == y2){
						if(board[x1 + 1][y1 - 1].which_piece_color() == space::BLACK &&
							board[x2 + 1][y2 + 1].which_piece_color() == space::BLACK){
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else if(board[x1][y1].which_piece_color() == space:: BLACK && multiple_jump){
			if(!board[x2][y2].is_piece() && !board[x3][y3].is_piece()){
				if((x1 - 4 == x3) && ((y1 + 4 == y3)||(y1 - 4 == y3))){
					if(y1+4 == y3){
						if(board[x1 - 1][y1 + 1].which_piece_color() == space::RED &&
							board[x2 - 1][y2 + 1].which_piece_color() == space::RED){
							return true;
						}
						else {
							return false;
						}
					}
					else if(y1 - 4 == y3){
						if(board[x1 - 1][y1 - 1].which_piece_color() == space::RED &&
							board[x2 - 1][y2 - 1].which_piece_color() == space::RED){
							return true;
						}
						else {
							return false;
						}
					}
				}
				else if((x1 - 4 == x3) && (y1 == y3)){
					if(y1 + 2 == y2){
						if(board[x1 - 1][y1 + 1].which_piece_color() == space::RED &&
							board[x2 - 1][y2 - 1].which_piece_color() == space::RED){
							return true;
						}
						else {
							return false;
						}
					}
					else if(y1 - 2 == y2){
						if(board[x1 - 1][y1 - 1].which_piece_color() == space::RED &&
							board[x2 - 1][y2 + 1].which_piece_color() == space::RED){
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}	
}

/* * * * * * * * * *
Precondition: a string move
Postcondition: Makes the move contained in the string
* * * * * * * * * */
void checkers::make_move(const string& move){
	//move is of the form 1A2B or 1A2B3C
	game::make_move(move);
	int x1, y1, x2, y2;
	int x3, y3;
	x1 = int(move[0] - '1');
	y1 = int(toupper(move[1]) - 'A');
	x2 = int(move[2] - '1');
	y2 = int(toupper(move[3]) - 'A');
	bool multiple_jump = false;

	if(move.size() > 4){
		x3 = int(move[4] - '1');
		y3 = int(toupper(move[5]) - 'A');
		multiple_jump = true;
	}

	if((((x1 - x2) == 1) || ((x1 - x2) == -1)) && (((y1 - y2) == 1) || ((y1 - y2) == -1))){
		//Move has no jumps
		board[x2][y2].set_piece(true);
		board[x2][y2].set_king(board[x1][y1].is_king());
		board[x2][y2].set_piece_color(board[x1][y1].which_piece_color());
	
		board[x1][y1].set_piece(false);
		board[x1][y1].set_king(false);
		board[x1][y1].set_piece_color(space::NONE);
	}
	else if((((x1-x2) == 2) || ((x1-x2) == -2)) && (((y1-y2 == 2) || ((y1-y2) == -2))) && !multiple_jump){
		//Move has one jump
		board[x2][y2].set_piece(true);
		board[x2][y2].set_king(board[x1][y1].is_king());
		board[x2][y2].set_piece_color(board[x1][y1].which_piece_color());

		board[x1][y1].set_piece(false);
		board[x1][y1].set_king(false);
		board[x1][y1].set_piece_color(space::NONE);

		if(y1 + 2 == y2 && x1 + 2 == x2){
			board[x1 + 1][y1 + 1].set_piece(false);
			board[x1 + 1][y1 + 1].set_king(false);
			board[x1 + 1][y1 + 1].set_piece_color(space::NONE);
		}
		else if(y1 + 2 == y2 && x1 - 2 == x2){
			board[x1 - 1][y1 + 1].set_piece(false);
			board[x1 - 1][y1 + 1].set_king(false);
			board[x1 - 1][y1 + 1].set_piece_color(space::NONE);
		}
		else if(y1 - 2 == y2 && x1 + 2 == x2){
			board[x1 + 1][y1 - 1].set_piece(false);
			board[x1 + 1][y1 - 1].set_king(false);
			board[x1 + 1][y1 - 1].set_piece_color(space::NONE);
		}
		else {
			board[x1 - 1][y1 - 1].set_piece(false);
			board[x1 - 1][y1 - 1].set_king(false);
			board[x1 - 1][y1 - 1].set_piece_color(space::NONE);
		}
	}
	else {
		//Move has two jumps
		board[x3][y3].set_piece(true);
		board[x3][y3].set_king(board[x1][y1].is_king());
		board[x3][y3].set_piece_color(board[x1][y1].which_piece_color());

		board[x1][y1].set_piece(false);
		board[x1][y1].set_king(false);
		board[x1][y1].set_piece_color(space::NONE);

		if(y1 == y3){
			if(x1 + 4 == x3 && y1 + 2 == y2){
				board[x1 + 1][y1 + 1].set_piece(false);
				board[x1 + 1][y1 + 1].set_king(false);
				board[x1 + 1][y1 + 1].set_piece_color(space::NONE);
				board[x2 + 1][y2 - 1].set_piece(false);
				board[x2 + 1][y2 - 1].set_king(false);
				board[x2 + 1][y2 - 1].set_piece_color(space::NONE);
			}
			else if(x1 + 4 == x3 && y1 - 2 == y2){
				board[x1 + 1][y1 - 1].set_piece(false);
				board[x1 + 1][y1 - 1].set_king(false);
				board[x1 + 1][y1 - 1].set_piece_color(space::NONE);
				board[x2 + 1][y2 + 1].set_piece(false);
				board[x2 + 1][y2 + 1].set_king(false);
				board[x2 + 1][y2 + 1].set_piece_color(space::NONE);
			}
			else if(y1 + 2 == y2){
				board[x1 - 1][y1 + 1].set_piece(false);
				board[x1 - 1][y1 + 1].set_king(false);
				board[x1 - 1][y1 + 1].set_piece_color(space::NONE);
				board[x2 - 1][y2 - 1].set_piece(false);
				board[x2 - 1][y2 - 1].set_king(false);
				board[x2 - 1][y2 - 1].set_piece_color(space::NONE);
			}
			else {
				board[x1 - 1][y1 - 1].set_piece(false);
				board[x1 - 1][y1 - 1].set_king(false);
				board[x1 - 1][y1 - 1].set_piece_color(space::NONE);
				board[x2 - 1][y2 + 1].set_piece(false);
				board[x2 - 1][y2 + 1].set_king(false);
				board[x2 - 1][y2 + 1].set_piece_color(space::NONE);
			}
		}
		else {
			if(x1 + 4 == x3 && y1 + 4 == y3){
				board[x1 + 1][y1 + 1].set_piece(false);
				board[x1 + 1][y1 + 1].set_king(false);
				board[x1 + 1][y1 + 1].set_piece_color(space::NONE);
				board[x2 + 1][y2 + 1].set_piece(false);
				board[x2 + 1][y2 + 1].set_king(false);
				board[x2 + 1][y2 + 1].set_piece_color(space::NONE);
			}
			else if(x1 + 4 == x3 && y1 - 4 == y3){
				board[x1 + 1][y1 - 1].set_piece(false);
				board[x1 + 1][y1 - 1].set_king(false);
				board[x1 + 1][y1 - 1].set_piece_color(space::NONE);
				board[x2 + 1][y2 - 1].set_piece(false);
				board[x2 + 1][y1 - 1].set_king(false);
				board[x2 + 1][y2 - 1].set_piece_color(space::NONE);
			}
			else if(y1 + 4 == y3){
				board[x1 - 1][y1 + 1].set_piece(false);
				board[x1 - 1][y1 + 1].set_king(false);
				board[x1 - 1][y1 + 1].set_piece_color(space::NONE);
				board[x2 - 1][y2 + 1].set_piece(false);
				board[x2 - 1][y2 + 1].set_king(false);
				board[x2 - 1][y2 + 1].set_piece_color(space::NONE);
			}
			else {
				board[x1 - 1][y1 - 1].set_piece(false);
				board[x1 - 1][y1 - 1].set_king(false);
				board[x1 - 1][y1 - 1].set_piece_color(space::NONE);
				board[x2 - 1][y2 - 1].set_piece(false);
				board[x2 - 1][y2 - 1].set_king(false);
				board[x2 - 1][y2 - 1].set_piece_color(space::NONE);
			}
		}
	}

	if(multiple_jump){
		if(board[x3][y3].which_piece_color() == space::BLACK && x3 == 0){
			board[x3][y3].set_king(true);
		}
		else if(board[x3][y3].which_piece_color() == space::RED && x3 == 7){
			board[x3][y3].set_king(true);
		}
	}
	else if(!multiple_jump){
		if(board[x2][y2].which_piece_color() == space::BLACK && x2 == 0){
			board[x2][y2].set_king(true);
		}
		else if(board[x2][y2].which_piece_color() == space::RED && x2 == 7){
			board[x2][y2].set_king(true);
		}
	}
}

/* * * * * * * * * *
Precondition: none
Postcondition: Returns true if there are no more legal moves, otherwise returns false
* * * * * * * * * */
bool checkers::is_game_over()const{
	int black_pieces(0), red_pieces(0), black_kings(0), red_kings(0);
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].which_piece_color() == space::RED){
				++red_pieces;
				if(board[i][j].is_king()){
					++red_kings;
				}
			}
			else if(board[i][j].which_piece_color() == space::BLACK){
				++black_pieces;
				if(board[i][j].is_king()){
					++black_kings;
				}
			}
		}
	}

	if(black_pieces == 0 || red_pieces == 0){
		return true;//Run out of pieces
	}
	else if(black_kings == 1 && red_kings == 1){
		return true;//Stalemate
	}
	else {
		return false;
	}
}

/* * * * * * * * * *
Precondition: none
Postcondition: Returns who won
* * * * * * * * * */
game::who checkers::who_won() {
	int black_pieces(0), red_pieces(0), black_kings(0), red_kings(0);
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].which_piece_color() == space::RED){
				++red_pieces;
				if(board[i][j].is_king()){
					++red_kings;
				}
			}
			else if(board[i][j].which_piece_color() == space::BLACK){
				++black_pieces;
				if(board[i][j].is_king()){
					++black_kings;
				}
			}
		}
	}

	if(black_pieces == 0){
		return COMPUTER;//Human ran out of pieces
	}
	else if(red_pieces == 0){
		return HUMAN;//Computer ran out of pieces
	}
	else if(black_kings == 1 && red_kings == 1){
		return NEUTRAL;//Stalemate
	}
	else {
		return NEUTRAL;
	}
}

game* checkers::clone() const{return new checkers(*this);}

int checkers::evaluate()const{
	int evaluation = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].which_piece_color() == space::RED){
				++evaluation;
				if(board[i][j].is_king()){
					++evaluation;
				}
			}
			else if(board[i][j].which_piece_color() == space::BLACK){
				--evaluation;
				if(board[i][j].is_king()){
					--evaluation;
				}
			}
		}
	}
	return evaluation;
}

void checkers::compute_moves(std::queue<std::string>& moves) {
	string test_move;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].is_piece()){
				//Checking non-jump moves first
				test_move = move_2_to_string(i, j, i + 1, j + 1);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_2_to_string(i, j, i - 1, j + 1);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_2_to_string(i, j, i + 1, j - 1);
				if(is_legal(test_move)){
					moves.push(test_move);
				}
				
				test_move = move_2_to_string(i, j, i - 1, j - 1);
				if(is_legal(test_move)){
					moves.push(test_move);
				}
				
				//Now the four jump moves
				test_move = move_2_to_string(i, j, i + 2, j + 2);
				if(is_legal(test_move)){
					moves.push(test_move);
				}
				
				test_move = move_2_to_string(i, j, i - 2, j + 2);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_2_to_string(i, j, i + 2, j - 2);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_2_to_string(i, j, i - 2, j - 2);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				//Finally the multiple jumps
				test_move = move_3_to_string(i, j, i - 2, j - 2, i - 4, j - 4);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i - 2, j - 2, i - 4, j);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i - 2, j + 2, i - 4, j);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i - 2, j + 2, i - 4, j + 4);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i - 2, j + 2, i, j + 4);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i + 2, j + 2, i, j + 4);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i + 2, j + 2, i + 4, j + 4);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i + 2, j + 2, i + 4, j);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i + 2, j - 2, i + 4, j);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i + 2, j - 2, i + 4, j - 4);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i + 2, j - 2, i, j - 4);
				if(is_legal(test_move)){
					moves.push(test_move);
				}

				test_move = move_3_to_string(i, j, i - 2, j - 2, i, j - 4);
				if(is_legal(test_move)){
					moves.push(test_move);
				}
			}
		}
	}	
}

string checkers::move_2_to_string(int x1, int y1, int x2, int y2){
	string temp;
	temp = static_cast<char>(x1 + 49);
	temp += static_cast<char>(y1 + 65);
	temp += static_cast<char>(x2 + 49);
	temp += static_cast<char>(y2 + 65);
	return temp;
}

string checkers::move_3_to_string(int x1, int y1, int x2, int y2, int x3, int y3){
	string temp;
	temp = static_cast<char>(x1 + 49);
	temp += static_cast<char>(y1 + 65);
	temp += static_cast<char>(x2 + 49);
	temp += static_cast<char>(y2 + 65);
	temp += static_cast<char>(x3 + 49);
	temp += static_cast<char>(y3 + 65);
	return temp;
}
bool checkers::multi_jump_black(int x1, int y1, int x2, int y2) const{
	space::piece_color blah = space::BLACK;
	if(board[x1][y1].which_piece_color() == blah && board[x2][y2].which_piece_color() == blah){
		return true;
	}
	else {
		return false;
	}
}

bool checkers::multi_jump_red(int x1, int y1, int x2, int y2) const{
	space::piece_color blah = space::RED;
	if(board[x1][y1].which_piece_color() == blah && board[x2][y2].which_piece_color() == blah){
		return true;
	}
	else {
		return false;
	}
}
}
