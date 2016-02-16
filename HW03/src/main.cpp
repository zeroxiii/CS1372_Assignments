///////////////////////////////////////////////////////////////////////
// Name: Rahmaan Lodhia												 //
// Prism Account: rlodhia3											 //
// Collaboration:													 //
// "I worked on the homework assignment alone, using only			 //
// course materials."												 //
///////////////////////////////////////////////////////////////////////

/*-------------------------------------------------------------------
* Breakout - main.c
*-----------------------------------------------------------------*/
#include "myLib.h"
#include "text.h"
#include "breakoutLib.h"
#include <stdlib.h>

//Creating main external variables used throughout the program
extern BRICK theBricks[NUMBRICKS];
extern BALL theBalls[NUM];
extern PADDLE paddle[1];
extern int i, k, brickCount;
extern unsigned short pcolor = RED;

//Initializing variables
BRICK theBricks[NUMBRICKS];
BALL theBalls[NUM];
PADDLE paddle[1];
int k = 0;
int i = 0;
int brickCount = 0;
int ballCount = 0;

void reset(); //Resets Game to Original Screen and Resets Variables

int main()
{
	

	/* Set display control register to Mode 3 and BG2 */
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	//Sets game up
	reset();
	
	while(FOREVER)
	{
		// Check for paddle movement & collision
		paddle[0].pcol = paddleInputAndCollision(paddle[0].pcol);
		
		//Ball Movement and Collisions
		ballMovementAndCollision(theBalls, theBricks, paddle[0].pcol, paddle[0].prow, i, k);
		
		waitForVblank();

		// Erase, Draw New Paddle, and change Paddle position values
		drawRect3(paddle[0].poldrow, paddle[0].poldcol, PHEIGHT, PWIDTH, BLACK);
		drawRect3(paddle[0].prow, paddle[0].pcol, PHEIGHT, PWIDTH, paddle[0].color);
		paddle[0].poldrow = paddle[0].prow;
		paddle[0].poldcol = paddle[0].pcol;

		//Loop through each Ball Struct
		for(i=0; i<NUM; i++)
			{
				// Erase old ball & poaddle
				drawRect3(theBalls[i].oldrow, theBalls[i].oldcol, theBalls[i].size, theBalls
				[i].size, BLACK);
				
				//Checks to see if ball is currently visible and draws it if it is
				if(theBalls[i].visible == 1)
				{
					// Draw new ball & paddle
					drawRect3(theBalls[i].row, theBalls[i].col, theBalls[i].size, theBalls[i].size,
					theBalls[i].color);
					// Transfer values
					theBalls[i].oldrow = theBalls[i].row;
					theBalls[i].oldcol = theBalls[i].col;
				}
			}
		
		//Checks to see if all balls have hit the bottom
		for(i = 0; i < NUM; i++)
			ballCount += !theBalls[i].visible;
		if(ballCount == NUM) //Lose if all balls hit the bottom
		{
			//Erases screen elements
			drawRect3(paddle[0].prow, paddle[0].pcol, PHEIGHT, PWIDTH, BLACK); 
			for(i = 0; i < NUM; i++)
				{
					drawRect3(theBalls[i].oldrow, theBalls[i].oldcol, theBalls[i].size, theBalls
					[i].size, BLACK);
					theBalls[i].visible = 0;
				}
			loseScreen(); //lose screen
			reset(); //reset game
		}
			
		else //Win if all bricks are hit
		{
			ballCount = 0;
			for(k = 0; k < NUMBRICKS; k++) //Calculates number of bricks hit
			{
				brickCount += !theBricks[k].visible;
			}
			if(brickCount == NUMBRICKS) //Checks to see if all bricks are hit
			{
				//Erase Screen Elements
				drawRect3(paddle[0].prow, paddle[0].pcol, PHEIGHT, PWIDTH, BLACK); 
				for(i = 0; i < NUM; i++)
				{
					drawRect3(theBalls[i].oldrow, theBalls[i].oldcol, theBalls[i].size, theBalls
					[i].size, BLACK);
					theBalls[i].visible = 0;
				}
				winScreen(); //win screen
				reset(); //reset game
			}
			else
				brickCount = 0;
		}

	}
	return 0;
}

void reset()
{
	//Reset game variables
	paddle[0].prow = PSTARTROW;
	paddle[0].pcol = PSTARTCOL;
	paddle[0].poldcol = 0;
	paddle[0].poldrow = 0;
	paddle[0].color = pcolor;
	brickCount = 0;
	ballCount = 0;

	//Reset Ball Struct
	for(i=0; i<NUM; i++)
	{
		theBalls[i].row = ROWSTART + rand()%20;
		theBalls[i].col = COLSTART + rand()%20;
		theBalls[i].size = SIZE;
		theBalls[i].rdelta = RDELSTART+rand()%2;
		theBalls[i].cdelta = CDELSTART+rand()%2;
		theBalls[i].oldrow = 0;
		theBalls[i].oldcol = 0;
		theBalls[i].visible = 1;
		theBalls[i].color = WHITE;
	}

	//Reset Brick Struct
	for(k=0; k<NUMBRICKS; k++)
	{
		theBricks[k].row = BSTARTROW;
		theBricks[k].col = BSTARTCOL + k*BWIDTH;
		theBricks[k].size = SIZE;
		theBricks[k].visible = 1;
		theBricks[k].color = rand()%32767;
	}

	//Reset game environment
	gameEnviroment(theBricks, paddle[0].color);

	//Display game title
	gameTitle();

	waitForVblank();
}