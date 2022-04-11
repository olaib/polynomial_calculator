#include "Controller.h"
#include "Conio.h"
#include "io.h"
#include <filesystem>
#include <fstream>

const auto LEVELS_FILE = "Board.txt";

const auto WELCOME_MESSAGE= "\n\nWell come :)\nReady to save the king?\nLet's find out!\n"
"To change character, press P.\nFor movement, use the arrow keys\n";
const auto END_GAME_MESSAGE = "well done! you won the game (:\n";
const auto ESCAPE_MESSAGE ="Bye :(\nhope you will try again \n";
const auto END_LEVEL_MESSAGE = "well done ! level: ";

//level.txt is the input file name which is contain the board of each level
Controller::Controller() : m_board(LEVELS_FILE) {}

//run the game
void Controller::run()
{
    std::cout << WELCOME_MESSAGE;
    std::system("cls");

       do {
        Screen::resetLocation();
        //read board from txt file
        m_board.readFile(m_board.getFile(), m_k, m_t, m_m, m_w);
        m_board.printBoard();
    
        for (auto exit = false; !exit && !m_KingFoundThrone;)
        {
            auto c = _getch();
            switch (c)
            {
            case 0:
            case SpecialKey:
                //move current player
                relevantClass(c);
                break;
            default:
                exit = handleRegularKey(c);
                break;
            }
        }
        //new level
        m_level++;
        //clear the m_board vector
        m_board.removeBoardVec();
        //read new level board
        //m_board.readFile(m_board.getFile(), m_k, m_t, m_m, m_w);
        std::system("cls");
        //print end current level message
        std::cout << END_LEVEL_MESSAGE << m_level;
        auto k = _getch();
        std::system("cls");
        m_KingFoundThrone = false;
        m_board.clearTelepotVec();
    } while (!m_board.getFile().eof());
    //end of game
    std::system("cls");
    //print end game message
    std::cout << END_GAME_MESSAGE;

}
   


bool Controller::handleRegularKey(int c)
{
    switch (c)
    {
    case KB_Escape: {
        std::cout << ESCAPE_MESSAGE;
        return true;
    }
    
    case  KB_P:
    {
        //play next player
        m_board.updateCurrentPlayer();
        m_board.printBoard();
        break;
    }
    case SpecialKey: {
        //move current player
        relevantClass(c);
        break;
    }
    }
    return false;
}


void Controller::relevantClass(int& c)
{
    //move relevant player
    switch (m_board.getChar(m_board.getCurrIndex())) {
    case KING: {
        m_k.move(m_board, c);
        //if kind in throne cell
        if (m_k.getHiddenChar() == Throne_tile) {
            m_KingFoundThrone = true;
            return;
        }
        break;
    }
    case WARRIOR: {
        m_w.move(m_board, c);
        break;
    }
    case MAGE: {
        m_m.move(m_board, c);
        break;
    }
    case THEIF: {
        m_t.move(m_board, c);
        break;
    }
    }
}

