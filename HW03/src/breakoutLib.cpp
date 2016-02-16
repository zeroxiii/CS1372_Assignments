/*-------------------------------------------------------------------
* Library for Breakout Functions
*------------------------------------------------------------------*/
#include "breakoutLib.h"
#include "myLib.h"
#include "text.h"

void gameEnviroment(BRICK theBricks[], unsigned short pcolor)
{
	//Drawing Walls
	drawRect3(WSTARTROW, WSTARTCOL, WHEIGHT, WWIDTH, WHITE);
	drawRect3(WSTARTROW, WSTARTCOL + 220, WHEIGHT, WWIDTH, WHITE);

	//Drawing Bricks
	for(int k = 0; k<NUMBRICKS; k++)
	{
		drawRect3(theBricks[k].row, theBricks[k].col, BHEIGHT, BWIDTH, theBricks[k].color);
	}
	
	//Initial Paddle
	drawRect3(PSTARTROW, PSTARTCOL, PHEIGHT, PWIDTH, pcolor);
	
}

void gameTitle()
{
	//Draw Text
	unsigned char title[] = "Breakout";
	drawString3(70, 95, title, WHITE);
	unsigned char text[] = "Press Down to Begin";
	drawString3(85, 65, text, WHITE);
	//Waits for Input
	while(!KEY_DOWN_NOW(BUTTON_DOWN))
	{
	}
	//Erase Text
	drawString3(70, 95, title, BLACK);
	drawString3(85, 65, text, BLACK);
}

void winScreen()
{
	//Draw Text
	unsigned char win[] = "You Win";
	unsigned char playAgain[] = "Press Down to Play Again";
	drawString3(70, 95, win, WHITE);
	drawString3(85, 50, playAgain, WHITE);
	//Waits for Input
	while(!KEY_DOWN_NOW(BUTTON_DOWN))
	{
	}
	//Erase Text
	drawString3(70, 95, win, BLACK);
	drawString3(85, 50, playAgain, BLACK);
}

void loseScreen()
{
	//Draw Text
	unsigned char win[] = "You Lose";
	unsigned char playAgain[] = "Press Down to Play Again";
	drawString3(70, 95, win, WHITE);
	drawString3(85, 50, playAgain, WHITE);
	//Waits for Input
	while(!KEY_DOWN_NOW(BUTTON_DOWN))
	{
	}
	//Erase Text
	drawString3(70, 95, win, BLACK);
	drawString3(85, 50, playAgain, BLACK);
}

int paddleInputAndCollision(int pcol)
{
	if(KEY_DOWN_NOW(BUTTON_LEFT))
	{
		pcol -= PCOLDEL;
	}
	if(KEY_DOWN_NOW(BUTTON_RIGHT))
	{
		pcol += PCOLDEL;
	}
	if(pcol < RIGHTWALL)
	{
		pcol = RIGHTWALL;
	}
	if(pcol + PWIDTH > LEFTWALL)
	{
		pcol = LEFTWALL-PWIDTH;
	}
	return pcol;
}

void ballMovementAndCollision(BALL theBalls[], BRICK theBricks[], int pcol, int prow, int i, int k)
{
	
	for(i=0; i< NUM; i++)
	{
		int brickHit = 0;

		// Move ball
		theBalls[i].row += theBalls[i].rdelta;
		theBalls[i].col += theBalls[i].cdelta;

		// Check for collisions

		//At Top and Bottom
		if(theBalls[i].row < 0) //At Top
		{
			theBalls[i].row = 0;
			theBalls[i].rdelta = -theBalls[i].rdelta;
		}
		if(theBalls[i].row > 160-theBalls[i].size) //At Bottom
		{
			theBalls[i].row = 160-theBalls[i].size;
			theBalls[i].rdelta = -theBalls[i].rdelta;
			if(theBalls[i].visible == 1)
			{
				theBalls[i].visible = 0;
			}

		}

		//At Walls
		if(theBalls[i].col < RIGHTWALL)
		{
			theBalls[i].col = RIGHTWALL;
			theBalls[i].cdelta = -theBalls[i].cdelta;
		}
		if(theBalls[i].col>LEFTWALL-theBalls[i].size)
		{
			theBalls[i].col = LEFTWALL-theBalls[i].size;
			theBalls[i].cdelta = -theBalls[i].cdelta;
		}

		//At Paddle
		if(theBalls[i].col+theBalls[i].size > pcol &&
		theBalls[i].col < pcol +PWIDTH &&
		theBalls[i].row + theBalls[i].size > prow &&
		theBalls[i].row + theBalls[i].size < prow + PHEIGHT &&
		theBalls[i].rdelta > 0)
		{
			theBalls[i].rdelta = -theBalls[i].rdelta;
		}

		//At Bricks and Changes Brick Variables if they are hit
		k = 0;
		while(brickHit != 1 && k < NUMBRICKS)
		{
			if(theBricks[k].visible == 1)
			{
				//At top of current Brick
				if(theBalls[i].col + theBalls[i].size > theBricks[k].col &&
				theBalls[i].col < theBricks[k].col + BWIDTH &&
				theBalls[i].row + theBalls[i].size > theBricks[k].row &&
				theBalls[i].row + theBalls[i].size < theBricks[k].row + BHEIGHT &&
				theBalls[i].rdelta > 0 && theBalls[i].visible &&
				!brickHit)
				{
					theBalls[i].rdelta = -theBalls[i].rdelta;
					brickHit = 1;
					theBricks[k].visible = 0;
					drawRect3(theBricks[k].row, theBricks[k].col, BHEIGHT, BWIDTH, BLACK);
				}
				//At bottom of current Brick
				if(theBalls[i].col + theBalls[i].size  > theBricks[k].col &&
				theBalls[i].col < theBricks[k].col + BWIDTH &&
				theBalls[i].row > theBricks[k].row &&
				theBalls[i].row < theBricks[k].row + BHEIGHT &&
				theBalls[i].rdelta < 0 && theBalls[i].visible &&
				!brickHit)
				{
					theBalls[i].rdelta = -theBalls[i].rdelta;
					brickHit = 1;
					theBricks[k].visible = 0;
					drawRect3(theBricks[k].row, theBricks[k].col, BHEIGHT, BWIDTH, BLACK);
				}
				//At Right Side of current Brick
				if(theBalls[i].col < theBricks[k].col + BWIDTH &&
				theBalls[i].col > theBricks[k].col &&
				theBalls[i].row + theBalls[i].size > theBricks[k].row &&
				theBalls[i].row < theBricks[k].row + BHEIGHT &&
				theBalls[i].cdelta < 0 && theBalls[i].visible &&
				!brickHit)
				{
					theBalls[i].cdelta = -theBalls[i].cdelta;
					brickHit = 1;
					theBricks[k].visible = 0;
					drawRect3(theBricks[k].row, theBricks[k].col, BHEIGHT, BWIDTH, BLACK);
				}
				//At Left Side of current Block
				if(theBalls[i].col + theBalls[i].size > theBricks[k].col&&
				theBalls[i].col + theBalls[i].size < theBricks[k].col + BWIDTH &&
				theBalls[i].row + theBalls[i].size> theBricks[k].row &&
				theBalls[i].row < theBricks[k].row + BHEIGHT &&
				theBalls[i].cdelta > 0 && theBalls[i].visible &&
				!brickHit)
				{
					theBalls[i].cdelta = -theBalls[i].cdelta;
					brickHit = 1;
					theBricks[k].visible = 0;
					drawRect3(theBricks[k].row, theBricks[k].col, BHEIGHT, BWIDTH, BLACK);
				}
			}
			k++;
		}

	}
}