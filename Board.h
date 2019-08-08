/******************************************************************************/
/*!
\file   Board.h
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #2
\date   02/02/2017
\brief  
  This is the header file for all member functions
  of a class called Board.
  
 Hours spent on this assignment: 2hrs
 
 Specific portions that gave you the most trouble: Nil
  
*/
/******************************************************************************/

/******************************************************************************/
/*!
  \class Board
  \brief  
    The Board class implements playing board with member function to enable 
    configuration to the board

    Operations include:

  - Calculating grid number
  - Changing player turn
  - Checking end of cirection
  - Flipping in a direction
  - Counting the tiles on board
  - Making a new board
  - Deleting a board
  - Checking if there is a legal move
  - Making a move
  - Collecting board stats
  - Printing the board

*/
/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef BOARD_H
#define BOARD_H
////////////////////////////////////////////////////////////////////////////////

#include "Othello.h" // ShotStats

namespace CS170
{
namespace Othello
{
// The attributes of the Board
class Board
{
public:
    void dump(int width = 3, bool extraline = false) const;
    int grid_no(int x, int y, int xmax);
    void count_board(void);
    MoveResult make_move(const Position &pos, const PLAYER_MOVE & playturn);
    bool possess_legal_move(const PLAYER_MOVE &playturn);
    const BoardStats & get_board_stats(void);
    Board(int, int);
    ~Board();
private:
    int x_quadrants;  // Board size along x-axis
    int y_quadrants;  // Board size along y-axis
    int *grid;        // The 2D board
    BoardStats stats;  // Status of the attack
    PLAYER_MOVE turn;  //current turn
};

} // namespace Othello
} // namespace CS170

#endif // BOARD_H
////////////////////////////////////////////////////////////////////////////////