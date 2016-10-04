/*
Date:				3 May 2016
Authour:			Nathan Egan
Filename:			checkers.cc
Latest Edit:		19 August 2016
File Description:	implementation file for checkers class, which wil implement a fully functioning checkers
						game intended for use with multiboard class. 
*/

#include "checkers.h"
#include <cstdlib>
#include <limits.h>

using namespace std;

//constructor
checkers::checkers()
{
	current_player = P1;
	other_player = COMP;
	num_levels = 4;
	num_red = num_black = num_red_kings = num_black_kings = num_turns = 0;
	for(int j = 0; j < 8; j++) //the vertical axis
	{
		for(int i = 0; i < 8; i++) //the horizontal axis
		{
			board[i][j] = new empty_piece;
		}
	}
	for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			red_locations[i][j] = -1;
			black_locations[i][j] = -1;
		}
	}
}

//destructor
checkers::~checkers()
{
	for(int j = 0; j < 8; j++) 
		for(int i = 0; i < 8; i++) 
			delete board[i][j];
}

//copy constructor
checkers::checkers(const checkers &other)
{
	current_player = other.current_player;
	other_player = other.other_player;
	num_red = other.num_red;
	num_black = other.num_black;
	num_red_kings = other.num_red_kings;
	num_black_kings = other.num_black_kings;
	num_turns = other.num_turns;
	num_levels = other.num_levels;
	for(int j = 0; j < 8; j++) //the vertical axis
	{
		for(int i = 0; i < 8; i++) //the horizontal axis
		{
			board[i][j] = other.board[i][j] -> clone();
		}
	}

	for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			red_locations[i][j] = other.red_locations[i][j];
			black_locations[i][j] = other.black_locations[i][j];
		}
	}
}

checkers checkers::operator = (const checkers &other)
{
	current_player = other.current_player;
	num_red = other.num_red;
	num_black = other.num_black;
	num_red_kings = other.num_red_kings;
	num_black_kings = other.num_black_kings;
	num_turns = other.num_turns;
	num_levels = other.num_levels;
	for(int j = 0; j < 8; j++) //the vertical axis
	{
		for(int i = 0; i < 8; i++) //the horizontal axis
		{
			delete board[i][j];
			board[i][j] = other.board[i][j] -> clone();
		}
	}	
	
	for(int i = 0; i < 12; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			red_locations[i][j] = other.red_locations[i][j];
			black_locations[i][j] = other.black_locations[i][j];
		}
	}
	return *this;
}

//create a starting board
void checkers::new_board()
{
	int rcount = 0, bcount = 0;
	num_black = num_red = num_black_kings = num_red_kings = num_turns = 0;
	current_player = P1;
	for(int j = 0; j < 8; j++) //the vertical axis
	{
		for(int i = 0; i < 8; i++) //the horizontal axis
		{
			//this section will clear each piece, in case the user chooses to reset the game
			delete board[i][j];
			board[i][j] = new empty_piece;
			
			if(j < 3 && (i+j)%2 == 1) //if we are in the top three rows of the board, every second square
			{
				delete board[i][j];
				board[i][j] = new red_piece;
				board[i][j] -> setnum(rcount);
				rcount++;
				red_locations[num_red][0] = i;
				red_locations[num_red][1] = j;
				num_red++;
			}
			else if(j > 4 && (i+j)%2 == 1) //if bottom three rows, every second square
			{
				delete board[i][j];
				board[i][j] = new black_piece;
				board[i][j] -> setnum(bcount);
				bcount++;
				black_locations[num_black][0] = i;
				black_locations[num_black][1] = j;
				num_black++;
			}
		}
	}
}

 
//this will show every piece on the board
void checkers::output() const
{
	char row = '1';
	cout << "   A "  << " B " << " C " << " D " << " E " << " F " << " G " << " H \n"; 
	for(int j = 0; j < 8; j++) //the vertical axis
	{
		cout << row << " ";
		row++;		
		for(int i = 0; i < 8; i++) //the horizontal axis
		{
			if((i+j)%2 == 1) 		//the playable squares
				cout << "\e[46m"; 	//sets the background color to blue
			else 					//the unplayable squares
				cout << "\e[47m";	//sets the background color to white
			
			board[i][j] -> output();
			cout << "\e[0m"; 		//resets the background color
		}
		cout << endl;
	}
}


//the function to move a piece.
void checkers::make_move(const string &move)
{
	int a, b, x, y;
	move_to_int(move, a, b, x, y);

	piece *tmp;
	tmp = board[a][b];         //I swap here because the only legal moves are a piece to an empty
	board[a][b] = board[x][y];
	board[x][y] = tmp; 
	
	//this will update the locations array
	if(board[x][y] -> ptype() == piece::BLACK || board[x][y] -> ptype() == piece::BLACK_KING)
	{
		black_locations[board[x][y] -> getnum()][0] = x;
		black_locations[board[x][y] -> getnum()][1] = y;
	}
	else if (board[x][y] -> ptype() == piece::RED || board[x][y] -> ptype() == piece::RED_KING)
	{
		red_locations[board[x][y] -> getnum()][0] = x;
		red_locations[board[x][y] -> getnum()][1] = y;
	}
	
	//this will delete a piece that has been jumped over
	if(a - x == 2 || a - x == -2) //any time it moves two units it is jumping a piece
	{
		//updating the appropriate locations array, will set to -1, -1
		if(board[x][y] -> ptype() == piece::BLACK || board[x][y] -> ptype() == piece::BLACK_KING)
		{			
			red_locations[board[(x+a)/2][(y+b)/2] -> getnum()][0] = red_locations[board[(x+a)/2][(y+b)/2] -> getnum()][1] = -1;
			num_red--;
			if(board[(x+a)/2][(y+b)/2] -> ptype() == piece::RED_KING)
				num_red_kings--;
		}	
		else if (board[x][y] -> ptype() == piece::RED || board[x][y] -> ptype() == piece::RED_KING)
		{
			black_locations[board[(x+a)/2][(y+b)/2] -> getnum()][0] = black_locations[board[(x+a)/2][(y+b)/2] -> getnum()][1] = -1;
			num_black--;
			if(board[(x+a)/2][(y+b)/2] -> ptype() == piece::BLACK_KING)
				num_black_kings--;
		}	

		delete board[(a+x)/2][(b+y)/2];
		board[(a+x)/2][(b+y)/2] = new empty_piece;
		
		//this will check to see if the piece can jump multiple times
		if(force_jump(x, y))
		{

			string move2;
			bool cheat = false;

			do
			{
				cheat = false;
				if(current_player == P1 || current_player == P2)
				{						
					output();
					cout << "Jump again!\n";
					cin >> move2;
				}
				else
				{
					queue<string> moves2;
					if(current_player == COMP)
						all_possible_red_moves(moves2);
					else
						all_possible_black_moves(moves2);
					while(moves2.front()[0] != move[2] && moves2.front()[1] != move[3])
						moves2.pop();
					move2 = moves2.front();
				}
				if(move2[0] != move[2] || move2[1] != move[3]) //checks that the piece that jumped is the one moving
				{
					cout << "You must move the same piece.\n";
					cheat = true; //to reset the loop if this if statement runs
				}
			}
			while(cheat || !legal(move2)); //this will check to ensure that the piece can only continue jumping	
			 make_move(move2);
		}
	}

	//this will turn a piece into a king
	if(y == 0 && board[x][y] -> ptype() == piece::BLACK)
	{
		int temp = board[x][y] -> getnum();
		delete board[x][y];
		board[x][y] = new black_king;
		board[x][y] -> setnum(temp);
		num_black_kings++;
		return;
	}
	else if(y == 7 && board[x][y] -> ptype() == piece::RED)
	{
		int temp = board[x][y] -> getnum();
		delete board[x][y];
		board[x][y] = new red_king;
		board[x][y] -> setnum(temp);
		num_red_kings++;
		return;
	}
	
}

//check if the move is legal. Will call a specific is_legal function after determining that the move will not trigger seg fault
bool checkers::legal(const string &move) const
{
	//checks the bounds of the area for the selected piece
	if(toupper(move[0]) < 'A' || toupper(move[0]) > 'H' || move[1] < '1' || move[1] > '8')
	{
		if(current_player != COMP && current_player != COMP2)
			cout << "You cannot select a piece that is not on the board\n";
		return false;
	}
	//checks the bounds of the array for the spot being moved to
	else if(toupper(move[2]) < 'A' || toupper(move[2]) > 'H' || move[3] < '1' || move[3] > '8')
	{
		if(current_player != COMP && current_player != COMP2)
			cout << "You can not move off the board\n";
		return false;
	}
	int a, b, x, y;
	move_to_int(move, a, b, x, y); //converts the move into integers for the array indexes
	
	//checks if the space being moved to is occupied
	if(board[x][y] -> ptype() != piece::EMPTY)
	{
		if(current_player != COMP && current_player != COMP2)
			cout << "You can not land on another piece\n";
		return false;
	}
	
	//checks to see if the current player is trying to move the wrong color piece
	if((current_player == P1 && board[a][b] -> ptype() == piece::RED) || (current_player == P2 && board[a][b] -> ptype() == piece::BLACK))
	{
		cout << "That is not your piece\n";
		return false;
	}
	
	if(force_jump()) //will check to see if there is a jump available, uses different rules
	{
		return legal_jump(move);		 
	}
	else
		return board[a][b] -> is_legal(move); //if it gets this far it checks the rules of the individual piece
}



//helper function to convert a move string to integers
void move_to_int(const string& move, int &a, int &b, int &x, int &y) 
{
	string tmp = "";
	
	for(unsigned int i = 0; i < move.length(); i++)
		 tmp += toupper(move[i]);
	a = (tmp[0] - 65);
	b = (tmp[1] - 49);
	x = (tmp[2] - 65);
	y = (tmp[3] - 49);

}

//will show all the locations and the number of black pieces (for testing)
void checkers::black_info_display() const
{
	cout << "Black has: " << num_black << " pieces and " << num_black_kings << " kings\nThey are located at: ";
	for(int i = 0; i < 12; i++)
	{
		cout << "(" << black_locations[i][0] << "," << black_locations[i][1] << ") ";
	}
	cout << endl;
}

//will show all the locations and the number of red pieces (for testing)
void checkers::red_info_display() const
{
	cout << "Red has: " << num_red << " pieces and " << num_red_kings << " kings\nThey are located at: ";
	for(int i = 0; i < 12; i++)
	{
		cout << "(" << red_locations[i][0] << "," << red_locations[i][1] << ") ";
	}
	cout << endl;
}

//will play the game until it concludes
void checkers::play()
{
	string move;
	other_player = COMP;
	current_player = COMP2;
	//test_board(); //uncomment this to play on an atypical board
	output();
	
	cout << "Black moves first\n";
	while(!is_game_over())
	{
		if(current_player == P1 || current_player == P2)
		{
			cout << "Make move: ";
			cin >> move;
			if(move == "MENU")
			{
				display_menu();
			}
			else if(legal(move))
			{
				make_move(move);
			}	
			else 
				continue;
		}
		else
		{
			cout << "The computer will move now...\n";
			comp_make_move();
		}
		
			output();
 			black_info_display();
			red_info_display();
			
			switch_player();
			
			num_turns++;
			if(current_player == P1 || current_player == COMP2)
				cout << "It is now Black's turn!\n";
			else
				cout << "It is now Red's turn!\n";

	}

	endgame();
}

//will allow the creation of a non standard board (for testing only)
void checkers::test_board()
{
	/* int i = 8;
	for(int j = 0; j < 8; j++)
	{
		for(int x = 0; x < 8; x++)
		{
			int n = board[x][j] -> getnum();
			if(board[x][j] -> ptype() == piece::RED || board[x][j] -> ptype() == piece::RED_KING)
			{
				red_locations[n][0] = red_locations[n][1] = -1;
			}
			else if(board[x][j] -> ptype() == piece::BLACK || board[x][j] -> ptype() == piece::BLACK_KING)
			{
				black_locations[n][0] = black_locations[n][1] = -1;
			}
			delete board[x][j];
			board[x][j] = new empty_piece;
		}
	}
	num_black = num_black_kings = num_red = num_red_kings = 0;
	board[3][6] = new black_piece;
	board[6][7] = new black_piece;
	board[3][4] = new red_piece;
	red_locations[0][0] = 3;
	red_locations[0][1] = 4;
	num_red = num_black = 100;
	current_player = P1;
	other_player = P2; */
}

//checks every piece on the board for a forced jump
bool checkers::force_jump() const
{
	if(current_player == P1 || current_player == COMP2)
	{
		for(int i = 0; i < 12; i++) //will check all 12 pieces by location
		{
			int a = black_locations[i][0], b = black_locations[i][1];
			if(a != -1) //when a piece is removed its location will be -1, -1
			{
				if(board[a][b] -> ptype() == piece::BLACK)
				{
					if(black_forced_jump(a, b))
						return true;
				}
				else if(board[a][b] -> ptype() == piece::BLACK_KING)
				{
					if(bking_forced_jump(a, b))
						return true;
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < 12; i++) //will check all 12 pieces by location
		{
			int a = red_locations[i][0], b = red_locations[i][1];
			if(a != -1) //when a piece is removed its location will be -1, -1
			{
				if(board[a][b] -> ptype() == piece::RED)
				{
					if(red_forced_jump(a, b))
						return true;	
				}
				else if(board[a][b] -> ptype() == piece::RED_KING)
				{
					if(rking_forced_jump(a, b))
						return true;
				}
			}
		}	
	}
	return false;
}

//stermines whether to force a piece to continue jumping
bool checkers::force_jump(const int& a, const int& b) const
{
		piece::piece_type tmp = board[a][b] -> ptype();
		switch (tmp)
		{
			case piece::RED:
				return red_forced_jump(a, b);
				break;
			case piece::RED_KING:
				return rking_forced_jump(a, b);
				break;
			case piece::BLACK:
				return black_forced_jump(a, b);
				break;
			case piece::BLACK_KING:
				return bking_forced_jump(a, b);
				break;
			default:
				cout << "Error, end of switch statement\n";
				return false;
		}
}

//checking the jump ruleset for a black piece
bool checkers::black_forced_jump(const int& a,const int& b) const
{
	if(b < 2) //no possible jumps this close to the edge of the board
		return false;
	//not strictly neccessary, but will cut down on lengthy if statements
	bool left_red = (a > 0 && (board[a-1][b-1] -> ptype() == piece::RED || board[a-1][b-1] -> ptype() == piece::RED_KING));
	bool right_red = (a < 7 && (board[a+1][b-1] -> ptype() == piece::RED || board[a+1][b-1] -> ptype() == piece::RED_KING));
	//this will check the spot on the left
	if(a > 1 && left_red && board[a-2][b-2] -> ptype() == piece::EMPTY)
		return true;
	//will check the spot ont he right
	else if (a < 6 && right_red && board[a+2][b-2] -> ptype() == piece::EMPTY)
		return true;
	else
		return false;
}

//checking the jump ruleset for a red piece
bool checkers::red_forced_jump(const int& a, const int& b) const
{
	if(b > 5) //no possible jumps this close to the edge of the board
		return false;
	
	//not strictly neccessary, but will cut down on lengthy if statements
	bool left_black = (a > 0 && (board[a-1][b+1] -> ptype() == piece::BLACK || board[a-1][b+1] -> ptype() == piece::BLACK_KING));
	bool right_black = (a < 7 && (board[a+1][b+1] -> ptype() == piece::BLACK || board[a+1][b+1] -> ptype() == piece::BLACK_KING));
	
	//this will check the spot on the left
	if(a > 1 && left_black && board[a-2][b+2] -> ptype() == piece::EMPTY)
		return true;
	//this will check the spot on the right
	else if(a < 6 && right_black && board[a+2][b+2] -> ptype() == piece::EMPTY)
		return true;

	else
		return false;
}

//checking the jump ruleset for a black king
bool checkers::bking_forced_jump(const int& a, const int& b) const
{
	//up-left jump
	if(b > 1 && a > 1 && (board[a-1][b-1] -> ptype() == piece::RED || board[a-1][b-1] -> ptype() == piece::RED_KING) && board[a-2][b-2] -> ptype() == piece::EMPTY) 
		return true;
	//up-right jump
	else if(b > 1 && a < 6 && (board[a+1][b-1] -> ptype() == piece::RED || board[a+1][b-1] -> ptype() == piece::RED_KING) && board[a+2][b-2] -> ptype() == piece::EMPTY)
		return true;
	//down-left jump
	else if(b < 6 && a > 1 && (board[a-1][b+1] -> ptype() == piece::RED || board[a-1][b+1] -> ptype() == piece::RED_KING) && board[a-2][b+2] -> ptype() == piece::EMPTY)
		return true;
	//down-right jump
	else if(b < 6 && a < 6 && (board[a+1][b+1] -> ptype() == piece::RED || board[a+1][b+1] -> ptype() == piece::RED_KING) && board[a+2][b+2] -> ptype() == piece::EMPTY)
		return true;
	else
		return false;
}

//checking the jump ruleset for a red king
bool checkers::rking_forced_jump(const int& a, const int& b) const
{
	//up-left jump
	if(b > 1 && a > 1 && (board[a-1][b-1] -> ptype() == piece::BLACK || board[a-1][b-1] -> ptype() == piece::BLACK_KING) && board[a-2][b-2] -> ptype() == piece::EMPTY) 
		return true;
	//up-right jump
	else if(b > 1 && a < 6 && (board[a+1][b-1] -> ptype() == piece::BLACK || board[a+1][b-1] -> ptype() == piece::BLACK_KING) && board[a+2][b-2] -> ptype() == piece::EMPTY)
		return true;
	//down-left jump
	else if(b < 6 && a > 1 && (board[a-1][b+1] -> ptype() == piece::BLACK || board[a-1][b+1] -> ptype() == piece::BLACK_KING) && board[a-2][b+2] -> ptype() == piece::EMPTY)
		return true;
	//down-right jump
	else if(b < 6 && a < 6 && (board[a+1][b+1] -> ptype() == piece::BLACK || board[a+1][b+1] -> ptype() == piece::BLACK_KING) && board[a+2][b+2] -> ptype() == piece::EMPTY)
		return true;
	else
		return false;
}

//checking to see if the game is over
bool checkers::is_game_over() const
{
	return(num_black == 0 ||  num_red == 0);
}



bool checkers::legal_jump(const string& move) const
{
	if(!board[toupper(move[0]) - 65][toupper(move[1]) - 49] -> legal_jump(move))//making sure the move CAN be a jump
		return false;
	piece::piece_type tmp = board[toupper(move[0]) -65][toupper(move[1]) -49] -> ptype();
		switch (tmp)
		{
			case piece::RED:
				return red_legal_jump(move);
				break;
			case piece::RED_KING:
				return red_legal_jump(move);
				break;
			case piece::BLACK:
				return black_legal_jump(move);
				break;
			case piece::BLACK_KING:
				return black_legal_jump(move);
				break;
			default:
				cout << "Error, end of switch statement\n";
				return false;
		}
}

bool checkers::red_legal_jump(const string& move) const
{
 	int a, b, c, d;
	move_to_int(move, a, b, c, d);
	
	//if it does not land in an empty space the move is illegal
	if(board[c][d] -> ptype() != piece::EMPTY)
	{
		if(current_player != COMP && current_player != COMP2)
			cout << "That space is occupied\n";
		return false;
	}
	
	//determining if it is jumping over a black piece
	if(board[(a+c)/2][(b+d)/2] -> ptype() == piece::BLACK || board[(a+c)/2][(b+d)/2] -> ptype() == piece::BLACK_KING)
		return true;
	else
	{
		if(current_player != COMP && current_player != COMP2)
			cout << "You must jump over a black piece\n";
		return false;
	}
}

bool checkers::black_legal_jump(const string& move) const
{
 	int a, b, c, d;
	move_to_int(move, a, b, c, d);
	
	//if it does not land in an empty space the move is illegal
	if(board[c][d] -> ptype() != piece::EMPTY)
	{
		if(current_player != COMP && current_player != COMP2)
			cout << "That space is occupied\n";
		return false;
	}
	
	//determining if it is jumping over a red piece
	if(board[(a+c)/2][(b+d)/2] -> ptype() == piece::RED || board[(a+c)/2][(b+d)/2] -> ptype() == piece::RED_KING)
		return true;
	else
	{
		if(current_player != COMP && current_player != COMP2)
			cout << "You must jump over a black piece\n";
		return false;
	}
}

//displays a message when the game finishes
void checkers::endgame() const
{
	//this is not called until the last turn has ended
	if(num_black != 0) 
	{
		cout << "Black wins with " << num_black << " pieces remaining, " << num_black_kings << " of which are kings.\n";
	}
	else if(num_red != 0)
	{
		cout << "Red wins with " << num_red << " pieces remaining, " << num_red_kings << " of which are kings\n";
	}
	else
	{
		cout << "Tie Game!\n";
	}
	cout << "The game took " << num_turns-1 << " turns to complete.\n";
}

//displays a menu and allows the user to choose an option
void checkers::display_menu ()
{
	char choice;
	do
	{
	cout << "1. Display Red Status \n2. Display Black Status \n3. Quit Game\n4. Restart\n5. Continue Playing\n";
		cin >> choice;
		switch (choice)
		{
			case '1': red_info_display(); break;
			case '2': black_info_display(); break;
			case '3': num_black = num_red = 0; choice = '5'; break;
			case '4': new_board(); output(); choice = '5'; break;
			case '5': output(); break;
			default: cout << "Please choose an option from the menu\n"; break;
		}
	}while(choice != '5');
}

//stores every legal move the computer can make on the current board in a queue
void checkers::all_possible_red_moves(queue<string> &moves) const
{
	string tmp_move = ""; 		//will be used to test each move
	char a, b, x, y; 			//these will store the locaiton of the piece and where it moves to
	int b1, b2;					//stores the location of the piece
	
	if(force_jump()) 			//checks to see if pieces can move normally, or if they must jump
	{
		for(int i = 0; i < 12; i++)			//will go through the array for locations of red pieces
		{
			b1 = red_locations[i][0]; 			//not technically neccessary: adds readability
			b2 = red_locations[i][1];
			if(b1 != -1)
			{
				//if there is a possible jump determine what the jump is and store it in the queue
				if((board[b1][b2] -> ptype() == piece::RED && red_forced_jump(b1, b2)) || (board[b1][b2] -> ptype() == piece::RED_KING && rking_forced_jump(b1, b2))) 
				{
					
					a = b1 + 65;
					b = b2 + 49;
					
					//test a jump over the piece down and left
					x = a - 2;
					y = b + 2;
					tmp_move = make_string(a, b, x, y);
					//if the jump is legal add it to the queue
					if(legal(tmp_move)) 				
					{
						//cout << "legal move: " << tmp_move << endl; //uncomment for testing
						moves.push(tmp_move);
						tmp_move = "";
					}
					
					//test a jump over the piece down and right
					x = a + 2;
					y = b + 2;
					tmp_move = make_string(a, b, x, y);
					//if the jump is legal add it to the queue
					if(legal(tmp_move)) 				
					{
						//cout << "legal move: " << tmp_move << endl; //uncomment for testing
						moves.push(tmp_move);
						tmp_move = "";
					}
					
					//if its a king, test upward jumps
					if(board[b1][b2] -> ptype() == piece::RED_KING)
					{
						//test a jump over the piece up and left
						x = a - 2;
						y = b - 2;
						tmp_move = make_string(a, b, x, y);
						//if the jump is legal add it to the queue
						if(legal(tmp_move)) 				
						{
							//cout << "legal move: " << tmp_move << endl; //uncomment for testing
							moves.push(tmp_move);
							tmp_move = "";
						}
						
						//test a jump over the piece up and right
						x = a + 2;
						y = b - 2;
						tmp_move = make_string(a, b, x, y);
						//if the jump is legal add it to the queue
						if(legal(tmp_move)) 				
						{
							//cout << "legal move: " << tmp_move << endl; //uncomment for testing
							moves.push(tmp_move);
							tmp_move = "";
						}
					}
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < 12; i++) 			//will go through the array of locations for red pieces
		{
			b1 = red_locations[i][0];			//not technically neccessary, adds readability
			b2 = red_locations[i][1];
			
			if (b1 != -1) 						//this checks if the piece has been removed
			{
				a = b1 + 65;
				b = b2 + 49; 					//converts the location into characters
			
				//testing down and left
				x = a - 1; 
				y = b + 1;
				tmp_move = make_string(a, b, x, y);
				if(legal(tmp_move)) 			//if it is a legal move, add it to the queue
				{
					//cout << "legal move: " << tmp_move << endl; //uncomment for testing
					moves.push(tmp_move);
					tmp_move = ""; 
				}
				
				//testing down and right
				x = a + 1;
				y = b + 1;
				tmp_move = make_string(a, b, x, y);
				if(legal(tmp_move)) 			//if it is a legal move, add it to the queue
				{
					//cout << "legal move: " << tmp_move << endl; //uncomment for testing
					moves.push(tmp_move);
					tmp_move = ""; 
				}			
				
				//if the piece is a king, test the upper left and upper right moves
				if(board[b1][b2] -> ptype() == piece::RED_KING)
				{
					//testing up and left
					x = a - 1;
					y = b - 1;
					tmp_move = make_string(a, b, x, y);
					if(legal(tmp_move))
					{
						//cout << "legal move: " << tmp_move << endl; //uncomment for testing
						moves.push(tmp_move);
						tmp_move = "";
					}
					
					//testing up and right
					x = a + 1;
					y = b - 1;
					tmp_move = make_string(a, b, x, y);
					if(legal(tmp_move))
					{
						//cout << "legal move: " << tmp_move << endl; //uncomment for testing
						moves.push(tmp_move);
						tmp_move = "";
					}
				}
			}	
		}
	}
} 

void checkers::all_possible_black_moves(queue<string> &moves) const
{
	string tmp_move = ""; 		//will be used to test each move
	char a, b, x, y; 			//these will store the locaiton of the piece and where it moves to
	int b1, b2;					//stores the location of the piece
	
	if(force_jump()) 			//checks to see if pieces can move normally, or if they must jump
	{
		for(int i = 0; i < 12; i++)			//will go through the array for locations of black pieces
		{
			b1 = black_locations[i][0]; 			//not technically neccessary: more readability
			b2 = black_locations[i][1];
			if(b1 != -1)
			{
				//if there is a possible jump determine what the jump is and store it in the queue
				if((board[b1][b2] -> ptype() == piece::BLACK && black_forced_jump(b1, b2)) || (board[b1][b2] -> ptype() == piece::BLACK_KING && bking_forced_jump(b1, b2))) 
				{
					
					a = b1 + 65;
					b = b2 + 49;
					
					//test a jump over the piece up and left
					x = a - 2;
					y = b - 2;
					tmp_move = make_string(a, b, x, y);
					//if the jump is legal add it to the queue
					if(legal(tmp_move)) 				
					{
						//cout << "legal move: " << tmp_move << endl; //uncomment for testing
						moves.push(tmp_move);
						tmp_move = "";
					}
					
					//test a jump over the piece up and right
					x = a + 2;
					y = b - 2;
					tmp_move = make_string(a, b, x, y);
					//if the jump is legal add it to the queue
					if(legal(tmp_move)) 				
					{
						//cout << "legal move: " << tmp_move << endl; //uncomment for testing
						moves.push(tmp_move);
						tmp_move = "";
					}
					
					//if its a king, test downward jumps
					if(board[b1][b2] -> ptype() == piece::BLACK_KING)
					{
						//test a jump over the piece down and left
						x = a - 2;
						y = b + 2;
						tmp_move = make_string(a, b, x, y);
						//if the jump is legal add it to the queue
						if(legal(tmp_move)) 				
						{
							//cout << "legal move: " << tmp_move << endl; //uncomment for testing
							moves.push(tmp_move);
							tmp_move = "";
						}
						
						//test a jump over the piece down and right
						x = a + 2;
						y = b + 2;
						tmp_move = make_string(a, b, x, y);
						//if the jump is legal add it to the queue
						if(legal(tmp_move)) 				
						{
							//cout << "legal move: " << tmp_move << endl; //uncomment for testing
							moves.push(tmp_move);
							tmp_move = "";
						}
					}
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < 12; i++) 			//will go through the array of locations for black pieces
		{
			b1 = black_locations[i][0];			//not technically neccessary, adds readability
			b2 = black_locations[i][1];
			
			if (b1 != -1) 						//this checks if the piece has been removed
			{
				a = b1 + 65;
				b = b2 + 49; 					//converts the location into characters
			
				//testing up and left
				x = a - 1; 
				y = b - 1;
				tmp_move = make_string(a, b, x, y);
				if(legal(tmp_move)) 			//if it is a legal move, add it to the queue
				{
					//cout << "legal move: " << tmp_move << endl; //uncomment for testing
					moves.push(tmp_move);
					tmp_move = ""; 
				}
				
				//testing up and right
				x = a + 1;
				y = b - 1;
				tmp_move = make_string(a, b, x, y);
				if(legal(tmp_move)) 			//if it is a legal move, add it to the queue
				{
					//cout << "legal move: " << tmp_move << endl; //uncomment for testing
					moves.push(tmp_move);
					tmp_move = ""; 
				}			
				
				//if the piece is a king, test the downward left and upper right moves
				if(board[b1][b2] -> ptype() == piece::BLACK_KING)
				{
					//testing down and left
					x = a - 1;
					y = b + 1;
					tmp_move = make_string(a, b, x, y);
					if(legal(tmp_move))
					{
						//cout << "legal move: " << tmp_move << endl; //uncomment for testing
						moves.push(tmp_move);
						tmp_move = "";
					}
					
					//testing down and right
					x = a - 1;
					y = b + 1;
					tmp_move = make_string(a, b, x, y);
					if(legal(tmp_move))
					{
						//cout << "legal move: " << tmp_move << endl; //uncomment for testing
						moves.push(tmp_move);
						tmp_move = "";
					}
				}
			}	
		}
	}
} 

//will make the move of a computer piece
void checkers::comp_make_move()
{
	if(current_player == COMP)
		comp_make_red_move();
	else
		comp_make_black_move();
}

void checkers::comp_make_red_move()
{	
	string best_move = "";
	int highest_value = INT_MIN;
	int tmp_value;
	checkers* tmp;
	queue<string> moves;

	all_possible_red_moves(moves);
	
	for ( ; !(moves.empty()); moves.pop())
	{
		tmp = new checkers(*this);
		tmp_value = tmp -> red_evaluate_possibilities(num_levels, highest_value);
		delete tmp;
		if(tmp_value > highest_value)
		{
			best_move = moves.front();
			highest_value = tmp_value;
		}
	}
	make_move(best_move);
}

int checkers::red_evaluate_possibilities(int levels, int highest)
{
	//base case
	if(levels == 0 || is_game_over())
		return evaluate();
	else
	{
		queue<string> red_moves;
		all_possible_red_moves(red_moves);
		checkers* tmp;
		int value;
		for( ; !(red_moves.empty()); red_moves.pop())
		{
			tmp = new checkers(*this);
			tmp -> make_move(red_moves.front());
			tmp -> switch_player();
			value = tmp -> black_evaluate_possibilities((levels - 1), value);
			delete tmp;
			if(value > highest)
				highest = value;
		}
		return highest;
	}
}

void checkers::comp_make_black_move()
{	
	string best_move = "";
	int lowest_value = INT_MAX;
	int tmp_value;
	checkers* tmp;
	queue<string> moves;

	all_possible_black_moves(moves);
	
	for ( ; !(moves.empty()); moves.pop())
	{
		tmp = new checkers(*this);
		tmp_value = tmp -> black_evaluate_possibilities(num_levels, lowest_value);
		delete tmp;
		if(tmp_value < lowest_value)
		{
			best_move = moves.front();
			lowest_value = tmp_value;
		}
	}
	make_move(best_move);
}

int checkers::black_evaluate_possibilities(int levels, int lowest)
{
	//base case
	if(levels == 0 || is_game_over())
		return evaluate();	
	else
	{
		queue<string> black_moves;
		all_possible_black_moves(black_moves);
		checkers* tmp;
		int value;
		for( ; !(black_moves.empty()); black_moves.pop())
		{
			tmp = new checkers(*this);
			tmp -> make_move(black_moves.front());
			tmp -> switch_player();
			value = tmp -> red_evaluate_possibilities((levels - 1),  value);
			delete tmp;
			if(value < lowest)
				lowest = value;
		}
		return lowest;
	}
}

void checkers::switch_player()
{
	players tmp;
	
	tmp = current_player;
	current_player = other_player;
	other_player = tmp;
}

string make_string(char a, char b, char c, char d)
{
	string s;
	s += a;
	s += b;
	s += c;
	s += d;
	return s;
}
