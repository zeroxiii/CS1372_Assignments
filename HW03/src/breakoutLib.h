/*-------------------------------------------------------------------
* breakoutLib.h -- Header File for Breakout Variables and Functions
*------------------------------------------------------------------*/
#include "myLib.h"
#include "text.h"

// Ball constants
#define ROWSTART 80
#define COLSTART 120
#define SIZE 3
#define RDELSTART 1
#define CDELSTART 1
#define NUM 2

// Paddle constants
#define PSTARTROW 150
#define PSTARTCOL 100
#define PHEIGHT 3
#define PWIDTH 40
#define PCOLDEL 4

//BRICK contants
#define BSTARTROW 40
#define BSTARTCOL 30
#define BHEIGHT 4
#define BWIDTH 30
#define NUMBRICKS 6

// Wall constants
#define WSTARTROW 0
#define WSTARTCOL 0
#define RIGHTWALL 20
#define LEFTWALL 220
#define WHEIGHT 160
#define WWIDTH 20

//BALL structure
typedef struct
{
	int row;
	int col;
	int size;
	int rdelta;
	int cdelta;
	int oldrow;
	int oldcol;
	int visible;
	u16 color;
} BALL;

//BRICK structure
typedef struct
{
	int row;
	int col;
	int size;
	int visible;
	u16 color;
} BRICK;

typedef struct
{
	int prow;
	int pcol;
	int poldrow;
	int poldcol;
	u16 color;
} PADDLE;

//Breakout Functions
int paddleInputAndCollision(int pcol); //Detects Input and Moves Paddle
void ballMovementAndCollision(BALL theBalls[], BRICK theBricks[], int pcol, int prow, int i, int k); //Calculates Ball Movement and Collision
void gameEnviroment(BRICK theBricks[], unsigned short pcolor); //Draws the game environment
void gameTitle(); //Displays game title
void winScreen(); //Win Screen
void loseScreen(); //Lose Screen