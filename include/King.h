#pragma once
#include "Location.h"
class Board;

class King {
public:
	King();
	void move(Board& board,int& c);//makes move if valid
	bool isValid(const char type) const;// check if king can step on type tile in cell
	Location getLocation() const;
	void setLocation(const size_t col,const size_t row);
	void setHiddenChar(const char c);
	char getHiddenChar()const;



private:
	Location m_location;//holds king location
	Location m_wantedLocation;// next king location if valid
	char m_hidenChar = ' ';// save char to replace in board
};