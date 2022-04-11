#pragma once
#include "Board.h"
#include <fstream>
#include <iostream>
#include "Warrior.h"
#include "Mage.h"
#include "King.h"
#include "Theif.h"

class Controller {
public:
	Controller();
	void run();
	bool handleRegularKey(int c);
	void relevantClass(int& c);
private:
	size_t m_level=0;//in board?????
	//end of level
	bool m_KingFoundThrone = false;
	Board m_board;
	King m_k;
	Theif m_t;	
	Warrior m_w;
	Mage m_m;
	size_t m_currIndex=0;
};