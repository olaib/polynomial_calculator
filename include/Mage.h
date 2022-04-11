#pragma once
#include "Location.h"
class Board;

class Mage {
public:
	Mage();
	void move(Board& board, int& c);// moves mage if valid
	bool isValid(char type) const;// check if mage can step on type tile in cell
	Location getLocation() const;
	void setLocation(size_t col, size_t row);
	void setHiddenChar(char c);
private:
	Location m_location = {0,0};//holds mage location
	Location m_wantedLocation;// cell that mage goes next if valid
	char m_hidenChar;// saves char to replace in board
};