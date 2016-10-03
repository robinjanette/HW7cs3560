/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Name:		Robin Kelby
	Class:		CS 2401
	File:		space.h
	Description:	This is the interface and implementation file 
			for the space class
	Date:		4/7/15

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MAIN_SAVITCH_SPACE
#define MAIN_SAVITCH_SPACE
#include <cstdlib>
using namespace std;

/* * * * * * * * * *
This class has four private variables to define the attributes of the 
space. Three are bool, and one is an enumerated type. 

playable is set as true for all the spaces the checkers can possibly 
play (all the black spaces regardless of whether the space is already occupied) 
and can be accessed by is_playable() and mutated by set_playable(). 

piece is set as true when a specific space has a piece on it and can be 
accessed by is_piece() and mutated by set_piece(). 

pcolor is set as NONE if piece is set to false and set as RED or BLACK 
if piece is set to true depending on the color of the piece; it can be 
accessed by which_piece_color() and mutated by set_piece_color().

Finally, king is set as true if piece is true and the piece has been 
kinged; it can be accessed by is_king() and mutated by set_king(). 
* * * * * * * * * */

namespace main_savitch_14 {
	class space {
		public:
		space(){pcolor = NONE;
			playable = false;
			piece = false;
			king = false;}

		enum piece_color {RED, BLACK, NONE };
		bool is_playable()const {return playable;}
		bool is_piece() const {return piece;}
		piece_color which_piece_color() const {return pcolor;}
		bool is_king() const {return king;}
		
		void set_playable(bool sw) {playable = sw;}
		void set_piece(bool sw) {piece = sw;}
		void set_piece_color(piece_color sw) {pcolor = sw;}
		void set_king(bool sw) {king = sw;}
		
		private:
		bool playable;
		bool piece;
		piece_color pcolor;
		bool king;
	};
}
		
#endif
