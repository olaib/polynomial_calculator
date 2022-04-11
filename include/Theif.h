#pragma once
#include "Location.h"
class Board;

class Theif {
public:
	Theif();
	void move(Board& board, int& c); //makes move if valid
	bool isValid(const char type) ;// check if warrior can step on type tile in cell
	void setLocation(const size_t col,const size_t row);
	bool getHasKey()const;
	void setHiddenChar(const char c);
	Location getLocation() const;


private:
	Location m_location{0,0}; //hold theif location
	Location m_wantedLocation;// next location of theif if valid
	char m_hidenChar; //save char to replace in board
	bool m_hasKey=false;// true if took key and didn't enter gate
};
