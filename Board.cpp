/******************************************************************************/
/*!
\file   Board.cpp
\author Lur Bing Huii
\par    email: lurbh\@hotmail.com
\par    DigiPen login: binghuii.lur
\par    Course: CS170
\par    Assignment #2
\date   02/02/2017
\brief  
  This is the implementation file for all functions
  for the Othello assignment.
  
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
  
 Hours spent on this assignment: 2hrs
 
 Specific portions that gave you the most trouble: Nil
  
*/
/******************************************************************************/
#include "Othello.h"
#include "Board.h"
#include <iostream> // cout, endl
#include <iomanip>  // setw

namespace CS170
{
namespace Othello
{
/******************************************************************************/
/*!
  \brief
    Prints the grid (ocean) to the screen.

  \param field_width
    How much space each position takes when printed.

  \param extraline
    If true, an extra line is printed after each row. If false, no extra
    line is printed.
*/
/******************************************************************************/
void Board::dump(int field_width, bool extraline) const
{
    // For each row
    for (int y = 0; y < y_quadrants; y++)
    {
        // For each column
        for (int x = 0; x < x_quadrants; x++)
        {
            const char *strings[] = { "X", "B", "W" };
            int value = grid[y * x_quadrants + x];

            std::cout << std::setw(field_width) << strings[value];
        }
        std::cout << std::endl;
        if (extraline)
            std::cout << std::endl;
    }
}

/*
 * ALL STUDENT IMPLEMENTATION GOES HERE
 */
/******************************************************************************/
/*!
  \brief
    Constructor that creates a new board

  \param x
    Number of x quadrants of board to create.

  \param y
    Number of y quadrants of board to create.
*/
/******************************************************************************/
Board::Board(int x, int y)
{
  x_quadrants = x;
  y_quadrants = y;
  // Creates memory for the grid
  grid = new int[x*y];
  // Sets stats for the board
  stats = {2,2,x*y-4,0,0,0,0,0};
  turn = BLACK;
  // Sets all grid to Blank
  for(int i = 0; i < x_quadrants * y_quadrants; ++i)
  {
    *(grid + i) = BLANK;
  }
  // Sets centre of grids to black and white
  *(grid + grid_no(x_quadrants/2,y_quadrants/2,x_quadrants)) = BLACK;
  *(grid + grid_no(x_quadrants/2 - 1,y_quadrants/2,x_quadrants)) = WHITE;
  *(grid + grid_no(x_quadrants/2,y_quadrants/2 - 1,x_quadrants)) = WHITE;
  *(grid + grid_no(x_quadrants/2 -1 ,y_quadrants/2 -1,x_quadrants)) = BLACK;
}

/******************************************************************************/
/*!
  \brief
    Destructor to delete all memory that is created
*/
/******************************************************************************/
Board::~Board(void)
{
  // Deletes memory created for the grid
  delete grid;
}
/******************************************************************************/
/*!
  \brief
    Calculates the grid number.

  \param x
    X columns of the board.

  \param y
    Y rows of the board.

  \param xmax
    Total number X columns on the board.
    
  \return 
    The number representing the grid.
*/
/******************************************************************************/
int Board::grid_no(int x, int y, int xmax)
{
  // Formula for checking grid number
  return (xmax * y + x);
}

/******************************************************************************/
/*!
  \brief
    Changes the turn.

  \param turn
    The current turn.

  \return 
    The opposite of turn.
*/
/******************************************************************************/
PLAYER_MOVE change_turn(PLAYER_MOVE turn)
{
  // Returns White if turn is Black
  if(turn == BLACK)
    return WHITE;
  // Returns Black if turn is White
  else if(turn == WHITE)
    return BLACK;
  // Returns Blank if turn is Blank
  else
    return BLANK;
}

/******************************************************************************/
/*!
  \brief
    Checks if it is able to flip in a given direction.

  \param grid
    Pointer to start of the grid.

  \param no
    The starting grid number.

  \param addno
    The direction that is being checked.
    
  \param max
    Total number of boxes in the grid
    
  \param xmax
    Total number X columns on the board.
    
  \param turn
    The current turn.
    
  \return 
    1 to signify there is an end and 0 when there is no end.
*/
/******************************************************************************/
int checkend(int * grid, int no, int addno, int max, int xmax, PLAYER_MOVE turn)
{
  int i;
  // Loops till it finds the end
  for(i=1;;i++)
  {
    // If grid number is within the board
    if(no + addno * i < max && no + addno * i >= 0)
    {
      // If tile on the grid belongs to other player
      if(*(grid + no + addno * i) == change_turn(turn))
      {
        // If grid location is at x limits
        if((no + addno * i) % xmax == xmax - 1 || (no + addno * i) % xmax == 0)
        {
          // If not checking in an up or down position
          if(abs(addno) != xmax)
          {
            return 0;
          }
          // Continues loop if requirements not met
        } 
      }
      // If tile on the grid belongs to other player
      else if(*(grid + no + addno * i) == turn)
      {
        return 1;
      }
      // If tile on the grid is blank
      else if(*(grid + no + addno * i) == BLANK)
      {
        return 0;
      }
    }
    else
      return 0;
  }
}

/******************************************************************************/
/*!
  \brief
    Flips the tiles in a given direction.

  \param gridptr
    Pointer to start of the grid.

  \param gridno
    The starting grid number.

  \param gridmax
    Total number of boxes in the grid
    
  \param addno
    The direction that is being checked.
  
  \param xmax
    Total number X columns on the board.
    
  \param turn
    The current turn.
    
  \return 
    The number of flips made.
*/
/******************************************************************************/
int flip_grid(int * gridptr, int gridno, int gridmax, 
int addno, int xmax, PLAYER_MOVE turn)
{
  int i, noofflips = 0;
  // Changes the position to the player colour
  *(gridptr + gridno) = turn;// Loops till it finds the end
  // Loops till it finds the end
  for(i=1;;i++)
  {
    // If grid number is within the board
    if(gridno + addno * i < gridmax && gridno + addno * i >= 0)
    {
      // If grid location is at x limits
      if((gridno + addno * i) % xmax == xmax - 1 
      && (gridno + addno * i) % xmax == 0)
      {
        // If tile on the grid belongs to other player 
        if(*(gridptr + gridno + addno * i) == change_turn(turn))
        {
          // Flips the tile to player turn
          *(gridptr + gridno + addno * i) = turn;
          // Increase the flipcount
          noofflips++;
        }
      }
      // If tile on the grid belongs to other player
      else if(*(gridptr + gridno + addno * i) == change_turn(turn))
      {
        // Flips the tile to player turn
        *(gridptr + gridno + addno * i) = turn;
        // Increase the flipcount
        noofflips++;
      }
      // If tile on the grid belongs to player
      else if(*(gridptr + gridno + addno * i) == turn)
      {
        // Breaks the loop
        break;
      }
    }
  }
  return noofflips;
}

/******************************************************************************/
/*!
  \brief
    Counts the board to check the number of blank, white or black tiles.
*/
/******************************************************************************/
void Board::count_board(void)
{
  int * & gridptr = grid;
  int i;
  int blank = 0,black = 0,white = 0;
  // Loops to every tile on the board
  for(i=0;i<x_quadrants*y_quadrants;i++)
  {
    // Increase blank count if tile is blank
    if(*(gridptr + i) == BLANK)
      blank++;
    // Increase blank count if tile is black
    if(*(gridptr + i) == BLACK)
      black++;
    // Increase blank count if tile is white
    if(*(gridptr + i) == WHITE)
      white++;
  }
  // Set board stats
  stats.num_of_white = white;
  stats.num_of_black = black;
  stats.num_of_blanks = blank;
}

/******************************************************************************/
/*!
  \brief
    Checks if there is an available move for a specific turn.

  \param playturn
    Which player turn to check.

  \return
    Returns true if there is a legal move and false if there are no 
    moves available.
*/
/******************************************************************************/
bool Board::possess_legal_move(const PLAYER_MOVE & playturn)
{
  int i,x,y,addno;
  int gridmax = x_quadrants * y_quadrants;
  // If the board still has blank tiles
  if(stats.num_of_blanks)
  {
    // Checks every grid for blank tiles
    for(i=0;i<gridmax;i++)
    {
      if(*(grid + i) == BLANK)
      {
        // Checks the surrounding of the blank tile
        for(x=-1;x<2;x++)
        {
          if(i%x_quadrants == 0 && x == -1)
          {
            x = 0;
          }
          if((i%x_quadrants == (x_quadrants - 1)) && (x == 1))
          {
            break;
          }
          for(y=-1;y<2;y++)
          {
            // Checks if within the grid
            if((i + y*x_quadrants) < gridmax && (i - y*x_quadrants) >= 0)
            {
              addno = grid_no(x,y,x_quadrants);
              // Checks if there is a tile to turn around the blank
              if(*(grid + i + addno) == change_turn(playturn))
              {
                // Checks if there is a end in the direction
                if(checkend(grid,i,addno,gridmax,x_quadrants,playturn))
                  return true;
              }
            }
          }
        }
      }
    }
  }
  return false;
}

/******************************************************************************/
/*!
  \brief
    Makes a move with the given position and turn.

  \param pos
    The position that the move is being made on.

  \param playturn
    Who is making the move.
  
  \return
    The result of the move.
*/
/******************************************************************************/
MoveResult Board::make_move(const Position &pos, const PLAYER_MOVE & playturn)
{
  int noofflips = 0, gridmax = x_quadrants * y_quadrants;
  int x, y, gridno, addno;
  // Checks if it's the right player turn
  if(turn != playturn)
  {
    stats.num_of_wrong_turns++;
    return E_WRONG_TURN;
  }
  gridno = grid_no(pos.x,pos.y,x_quadrants);
  // Checks if the position is off the grid
  if(gridno >= gridmax || gridno < 0)
  {
    stats.num_off_board_moves++;
    return E_OFF_BOARD;
  }
  // Checks if the position is not a blank
  if(*(grid + gridno) != BLANK)
  {
    stats.num_of_moves_on_occupied_space++; 
    return E_OCCUPIED;
  }
  // Checks the surrounding of the position
  for(x=-1;x<2;x++)
  {
    if(gridno%x_quadrants == 0 && x == -1)
    {
      x = 0;
    }
    if((gridno%x_quadrants == (x_quadrants - 1)) && (x == 1))
    {
       break;
    }
    for(y=-1;y<2;y++)
    {
      // Checks if within the grid
      if((gridno + y*x_quadrants) < gridmax && (gridno + y*x_quadrants) >= 0)
      {
        
        addno = grid_no(x,y,x_quadrants);
        // Checks if there is a tile to turn around the blank
        if(*(grid + gridno + addno) == change_turn(playturn))
        {
          // Checks if there is a end in the direction
          if(checkend(grid,gridno,addno,gridmax,x_quadrants,playturn))
          {
            // Flips the grid and counts the number of flips
            noofflips += 
            flip_grid(grid,gridno, gridmax, addno, x_quadrants, playturn);
          }
        }
      }
    }
  }
  // When there is no flips
  if(noofflips == 0)
  {
    stats.num_of_no_pieces_flipped++;
    return E_NO_PIECES_FLIPPED;
  }
  else
  {
    // If number of flips greater than stored value replace it
    if(noofflips > stats.highest_num_of_flips_so_far)
      stats.highest_num_of_flips_so_far = noofflips;
    count_board();
    // Checks if other player has a move
    if(possess_legal_move(change_turn(playturn)))
      turn = change_turn(playturn);
    return SUCCESS;
  }
}

/******************************************************************************/
/*!
  \brief
    Collects the stats of the board.

  \return
    The stats of the board.
*/
/******************************************************************************/
const BoardStats & Board::get_board_stats(void)
{
  BoardStats & returnstats = stats;
  return returnstats;
}
 
 
} // namespace Othello
} // namespace CS170


