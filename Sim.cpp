/* Assignment #3 CAP4621 Intro to AI - Author: Zachary Gay 

The hexagon game involves two players, 
who gradually construct a six-vertex undirected graph with solid and dashed edges. 

Player 1 adds solid edges, whereas Player 2 uses dashes.The players begin with a six-vertex graph that has no edges (Figure 1), 
and add new edges, one by one; Player 1 makes the first move. At each move, a player has to add a new edge between two vertices that are not connected by any old edge. 

Figure 2 is an example of a mid-game position, where Player 1 has to make the next move.If Player 1 constructs a solid-line triangle, he loses the game; 
similarly, a dashed triangle means a loss of Player 2. For example, if the game ends as shown in Figure 3, 
then Player 2 has lost since he has constructed the dashed triangle “3-5-6.”Implement a program for playing the hexagon game. 

Your program should prompt the user to enter a player number (1 or 2), and then act as the specified player.
For example, if the user enters “1”, the program should make the first move.
*/
//Includes
#include <iostream>
#include <stdlib.h>
#include <time.h> 

//Namespaces
using namespace std;

//Constants
#define VERTEXES 6

//Global variables
char SIM[VERTEXES][VERTEXES];

//Function used to print a visable representation of the 2Darray data structure as the program executes. ***Line 229
void printSIM() {
  for (size_t i = 0; i < VERTEXES; i++)// for rows
  { cout << "\n";
    for (size_t j = 0; j < VERTEXES; j++) //for cols
    {
      cout << SIM[i][j] << " "; //print value
    }
  }
  cout << "\n";
}
//Function that initilizes the 2D array with 'n' values.
void initData() {
  for (size_t i = 0; i < VERTEXES; i++) //for rows
  {
    for (size_t j = 0; j < VERTEXES; j++) //for cols
    {
      SIM[i][j]= 'n'; //assign variable
    }
  }
}
//fucntion to great player to game and recieve input on which player the computer will play.
int welcome() {
  int player;
  cout << "\nWelcome to The Game of SIM! \n\n";
  cout << "How to play:\nPlayer1 uses solid lines.\nPlayer2 uses Dashed lines.\nCannot create lines to the same vertex.\nCannot overwrite an already exsiting line.\nFirst player the create a triangle loses.\n\n" ;
  cout << "Please enter the Player you wish the program to play: ";
  cin >> player;
  return player;
}
// Function that handles the computers turn. Using srand to help generate random numbers for the move.
// Checks if the move is avaialable, if not a recursive call is made to try again. due to srand numbers will only be generatd the next second(seems this way).
void compTurn(char move) {
  // generate random number between 1 and 6
  int row = rand() % 6; 
  int col = rand() % 6;
  //cout << "computer numbers: " << row << " " << col;
  if (row <= 5 && row >= 0) // ensure valeus are in range
  {
    if (col <= 5 && col >= 0) // ensure valeus are in range
    {
      if (row != col) //check that row and col are not equal, cannot draw line to the same vertex.
      {
        if (SIM[row][col] == 'n')
        {
          SIM[row][col] = move; 
          SIM[col][row] = move; 
          cout << "The computer has made a move! It drew a line between vertexes " << row+1 << " and " << col+1 << ".\n\n";
        }
        else
        {
          compTurn(move);
        }
      }
      else
      {
        compTurn(move);
      }
    }
    else
    {
      compTurn(move);
    }  
  }
  else
  {
    compTurn(move);
  }
}
//Function that ahndles the palyers turn. Recieve two vertexes from user. check if move is valid/available. If nto make a recursive call and try again.
void playerTurn(char move) {
  int row, col;

  cout << "Please enter the two vertexes you would like to draw a line between:\n";
  cout << "Vertex 1: ";
  cin >> row;
  cout << "Vertex 2: ";
  cin >> col;
  row--; //decrement for array use
  col--; //decrement for array use
  if (row <= 5 && row >= 0) //ensure value is in range
  {
    if (col <= 5 && col >= 0) // ensure value is in range
    {
      if (row != col) //check that row and col are not equal, cannot draw line to the same vertex.
      {
        if (SIM[row][col] == 'n') // chekc if no move has been made there before
        {
          SIM[row][col] = move; 
          SIM[col][row] = move; 
          cout << "The player has made a move! You drew a line between vertexes " << row+1 << " and " << col+1 << ".\n\n";
        }
        else
        {
          cout << "Sorry that move is unavailable. Please try a different move.\n\n";
          playerTurn(move);
        }
      }
      else
      {
        cout << "Sorry that move is unavailable. Same Numbers. Please try a different move.\n\n";
        playerTurn(move);
      }
    }
    else
    {
      cout << "Invalid Vertex. Please try a different move.\n\n";
      playerTurn(move);
    }  
  }
  else
  {
    cout << "Invalid Vertex. Please try a different move.\n\n";
    playerTurn(move);
  }
}
//This function is called to check the values at three points. if the values are all equal a triangle has been formed and opposing player wins.
int checkpoint(int x, int y, int z, char value) {
  if (SIM[x-1][y-1] == value && SIM[x-1][z-1] == value && SIM[y-1][z-1] == value ) // check 3 values if they are equal
  {
    if (value == 's') // player 2 wins
    {
      cout << "Player 2 Wins by Player 1's solid triangle at " << x << "-" << y << "-" << z << "\n";
    }
    else if (value == 'd') // player 1 wins
    {
      cout << "Player 1 Wins by Player 2's dashed triangle at " << x << "-" << y << "-" << z << "\n";
    }
    return 1;
  }
  return 0;
}
//This function is written as an Iteractive Dynamic Programming. It uses 3 for loops the traverse through the values X-Y-Z in a way
//That will never check the same set of 3 numbers twice. There are 20 possible triangle solutions to this game and this function checks no more than those 20.
int check(char value) {
  int xc = 1;
  int yc = 2;
  int zc = 3;
  int win = 0;

  for (int x = xc;x <= 4; x++)
  {
    for (int y = yc; y <= 5; y++) 
    {
      for (int z = zc; z <= 6; z++)
      {
        if (y != z && z > y)
        {
          win = checkpoint(x,y,z, value);
        }
        if (win == 1) 
        {
          return win;
        }
      }
    }
    zc++;
    yc++;
  }
  return 0;
}
//This functions handles the turns no matter wheather the user wnats to play player 1 or 2
void play (int player) {
  int ended = 0, turn = 1;

  while (ended != 1)
  {
    if (turn == 1 && player == 1) //If its players one turns and is the computer
    {
      compTurn('s');
    }
    else if (turn == 1 && player == 2) //If its players one turns and is the person
    {
      playerTurn('s');
    }

    ended = check('s');
    if (ended == 1)
    {
      break;
    }

    turn = 2; 

    if (turn == 2 && player == 2) //If its players one turns and is the computer
    {
      compTurn('d');
    }
    else if (turn == 2 && player == 1) //If its players one turns and is the person
    {
      playerTurn('d');
    }

    ended = check('d');
    if (ended == 1)
    {
      break;
    }

    turn = 1;
    //printSIM();
  }
}
//Main driver for program. Initialize data, get computer player and play
int main()
{
  srand(time(NULL));
  initData();
	int player = welcome();
  play(player);
}