///////////////////////////////////////////////////////////////////////
// Name: Rahmaan Lodhia												 //
// Prism Account: rlodhia3											 //
// Collaboration:													 //
// "I worked on the homework assignment alone, using only			 //
// course materials."												 //
///////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include "frogger.h"

//Game Prototypes
void initializeGameVariables(FROG froggy[], CAR cars[], LOG log[], PAD pad[], int i);
void drawBackground(FROG froggy[], PAD pads[]);
void checkMovementAndCollision(FROG froggy[], CAR cars[], LOG log[], PAD pad[], int i);
void respawnFrog(FROG froggy[]);
void titleScreen();
void playGame(FROG froggy[], CAR cars[], LOG log[], PAD pad[], int i, STATE gameState);
void loseScreen();
void winScreen();


int main()
{
	//Create Color Palette for MODE 4
	int i;
	int numcolors = sizeof(colors)/sizeof(colors[0]);
	for(i=0; i<numcolors; i++)
	{
		PALETTE[i] = colors[i];
	}

	//Initialize gameState
	gameState = TITLE;

	//Game Loop
	while(FOREVER)
	{
		switch(gameState) //Switch game state when appropiate
		{
		case TITLE:
			titleScreen();
			while(KEY_DOWN_NOW(BUTTON_START))
			{
			}
			while(!KEY_DOWN_NOW(BUTTON_START))
			{
			}
			initializeGameVariables(froggy,cars,logs,pads,i);
			gameState = PLAYING;
			drawBackground(froggy, pads);
			waitForVblank();
			FlipPage();
			break;
		case PLAYING:
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			//Lose Condition
			if(froggy[0].lives == 0)
			{
				gameState = LOSE;
				froggy[0].padCount = 0;
			}
			//Win Condition
			if(froggy[0].padCount == NUMPADS)
			{
				gameState = WIN;
				froggy[0].padCount = 0;
			}
			checkMovementAndCollision(froggy,cars,logs,pads,i);
			playGame(froggy,cars,logs,pads,i,gameState);
			waitForVblank();
			FlipPage();
			break;
		case WIN:
			winScreen();
			while(!KEY_DOWN_NOW(BUTTON_START))
			{
			}
			fillScreen3(BLACK);
			//draw winning screen
			gameState = TITLE;
			break;
		case LOSE:
			loseScreen();
			while(!KEY_DOWN_NOW(BUTTON_START))
			{
			}
			fillScreen3(BLACK);
			//Draw losing screen
			gameState = TITLE;
			break;
		}
	}
	return 0;
}

void titleScreen() //Displays Title Screen
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	fillScreen3(BLACK);
	unsigned char title[] = "Frogger";
	unsigned char subTitle[] = "Press Start to Play";
	drawString3(70,95,title,WHITE);
	drawString3(85,60,subTitle,WHITE);
}

void loseScreen() //Displays Lose Screen
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	fillScreen3(BLACK);
	unsigned char title[] = "You Lose";
	unsigned char subTitle[] = "Press Start to Play";
	drawString3(70,95,title,WHITE);
	drawString3(85,60,subTitle,WHITE);
}

void winScreen() //Displays Win Screen
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	fillScreen3(BLACK);
	unsigned char title[] = "You Win";
	unsigned char subTitle[] = "Press Start to Play";
	drawString3(70,95,title,WHITE);
	drawString3(85,60,subTitle,WHITE);
}

void drawBackground(FROG froggy[], PAD pads[]) //Draws Background for Game
{

	drawRect4(RIVERSTART, 0, RIVERHEIGHT, RIVERWIDTH, RIVERCOLOR);
	drawRect4(MEDIAN1START, 0, MEDIANHEIGHT, MEDIANWIDTH, MEDIANCOLOR);
	drawRect4(MEDIAN2START, 0, MEDIANHEIGHT, MEDIANWIDTH, MEDIANCOLOR);
	drawRect4(0,0,STATUSHEIGHT, STATUSWIDTH, STATUSCOLOR);
	int c;

	for(c = 0; c < 5; c++)
	{
		drawRect4(16,c*52,16,32,DARKERGREENINDEX);

	}

	for(c = 0; c < 4; c++)
	{
		drawRect4(17,34+c*52,14,16,DARKGREENINDEX);
		pads[c].occupied = 0;
	}
	unsigned char lives[] = "Lives: ";
	drawString4(4,0,lives,WHITEINDEX);
}

void initializeGameVariables(FROG froggy[], CAR cars[], LOG log[], PAD pad[], int i) //Initialize Game Varialbes
{
	//Initialize Frog
	respawnFrog(froggy);
	froggy[0].lives = 3;
	froggy[0].down = 1;
	froggy[0].up = 1;
	froggy[0].left = 1;
	froggy[0].right = 1;
	froggy[0].padCount = 0;

	//Initializing Car Variables
	for(i = 0; i < NUMCARS/3; i++)
	{
		cars[i].col = CARSTARTCOL + i*CARGAP;
		cars[i].row = CARSTARTROW;
		cars[i].oldcol = 0;
		cars[i].oldoldcol = 0;
		cars[i].speed = OBJECTSPEED;
		cars[i].height = CARHEIGHT;
		cars[i].width = CARWIDTH;
		cars[i].cindex = i + 1;
		cars[i].lane = 1;
	}

	for(i = NUMCARS/3; i < NUMCARS*2/3; i++)
	{
		cars[i].col = CARSTARTCOL + (i - NUMCARS/3 + 1)*CARGAP;
		cars[i].row = CARSTARTROW + LANEGAP;
		cars[i].oldcol = 0;
		cars[i].oldoldcol = 0;
		cars[i].speed = -OBJECTSPEED;
		cars[i].height = CARHEIGHT;
		cars[i].width = CARWIDTH;
		cars[i].cindex = i + 1;
		cars[i].lane = 2;
	}

	for(i = NUMCARS*2/3; i < NUMCARS; i++)
	{
		cars[i].col = CARSTARTCOL + (i - NUMCARS*2/3)*CARGAP;
		cars[i].row = CARSTARTROW + 2*LANEGAP;
		cars[i].oldcol = 0;
		cars[i].oldoldcol = 0;
		cars[i].speed = OBJECTSPEED;
		cars[i].height = CARHEIGHT;
		cars[i].width = CARWIDTH;
		cars[i].cindex = i + 1;
		cars[i].lane = 3;
	}

	//Initializing Log Variables
	for(i = 0; i < 3; i++)
	{
		logs[i].lane = 3;
		logs[i].col = LOGSTARTCOL + i*LOGGAP3;
		logs[i].row = LOGSTARTROW + 2*LANEGAP;
		logs[i].oldcol = 0;
		logs[i].oldoldcol = 0;
		logs[i].speed = -OBJECTSPEED;
		logs[i].height = LOGHEIGHT;
		logs[i].width = LOGWIDTH;
	}

	for(i = 3; i < 7; i++)
	{
		logs[i].lane = 2;
		logs[i].col = LOGSTARTCOL + (i - 3)*LOGGAP2;
		logs[i].row = LOGSTARTROW + LANEGAP;
		logs[i].oldcol = 0;
		logs[i].oldoldcol = 0;
		logs[i].speed = OBJECTSPEED;
		logs[i].height = LOGHEIGHT;
		logs[i].width = LOGWIDTH;
	}

	for(i = 7; i < NUMLOGS; i++)
	{
		logs[i].lane = 1;
		logs[i].col = LOGSTARTCOL + (i -7)*LOGGAP1;
		logs[i].row = LOGSTARTROW;
		logs[i].oldcol = 0;
		logs[i].oldoldcol = 0;
		logs[i].speed = -OBJECTSPEED;
		logs[i].height = LOGHEIGHT;
		logs[i].width = LOGWIDTH*5/4;
	}

}

void respawnFrog(FROG froggy[])
{
	//initialize frog variables
	froggy[0].row = FROGSTARTROW;
	froggy[0].col = FROGSTARTCOL;
	froggy[0].oldrow = 0;
	froggy[0].oldcol = 0;
	froggy[0].oldoldrow = 0;
	froggy[0].oldoldcol = 0;
	froggy[0].size = FROGSIZE;
	froggy[0].speed = OBJECTSPEED;
	froggy[0].jump = FROGJUMP;
	froggy[0].cindex = FROGCOLOR;
	froggy[0].status = ALIVE;
	froggy[0].carCollide = 0;
	froggy[0].waterCollide = 0;
	froggy[0].logCollide = 0;
	froggy[0].padCollide = 0;
}

void playGame(FROG froggy[], CAR cars[], LOG log[], PAD pad[], int i, STATE gameState)
{
	//Checks Where Frog Is and Erases Accordingly
	//Erasing at Median
	if(froggy[0].oldrow > MEDIAN2START && froggy[0].oldrow < 160)
	{
		drawRect4(froggy[0].oldoldrow, froggy[0].oldoldcol, froggy[0].size, froggy[0].size, MEDIANCOLOR);
	}

	if(froggy[0].oldrow > MEDIAN1START && froggy[0].oldrow < MEDIAN1START + MEDIANHEIGHT)
	{
		drawRect4(froggy[0].oldoldrow, froggy[0].oldoldcol, froggy[0].size, froggy[0].size, MEDIANCOLOR);
	}

	//Erasing at Road
	if(froggy[0].oldrow > ROADSTART && froggy[0].oldrow < ROADSTART + ROADHEIGHT)
	{
		drawRect4(froggy[0].oldoldrow, froggy[0].oldoldcol, froggy[0].size, froggy[0].size, ROADCOLOR);
	}

	if(froggy[0].carCollide == 1)
	{
		froggy[0].lives -= 1;
		respawnFrog(froggy);
	}

	//Erasing at River
	if(froggy[0].waterCollide == 1)
	{
		froggy[0].lives -= 1;
		respawnFrog(froggy);
	}

	//Pad Check
	if(froggy[0].padCollide == 1)
	{
		froggy[0].padCollide = 0;
		froggy[0].padCount += 1;
		drawRect4(froggy[0].row, froggy[0].col, froggy[0].size, froggy[0].size, froggy[0].cindex);
		respawnFrog(froggy);
	}

	//Erase Cars
	for(i=0; i<NUMCARS; i++)
	{
		drawRect4(cars[i].row-1, cars[i].oldoldcol-2*cars[i].speed, cars[i].height+2,
			cars[i].width+1, BLACKINDEX);
		cars[i].col += cars[i].speed;
		if(((cars[i].lane == 1) || (cars[i].lane == 3))&& cars[i].col > 240)
		{
			cars[i].col = 0;
		}
		else if(cars[i].col + cars[i].width < 0)
		{
			cars[i].col = 240 - cars[i].width;
		}
	}

	//Erase Logs
	for(i=0; i<NUMLOGS; i++)
	{
		drawRect4(logs[i].row-1, logs[i].oldoldcol-2*logs[i].speed, logs[i].height+2,
			logs[i].width+1, BLUEINDEX);
		logs[i].col += logs[i].speed;
		if(((logs[i].lane == 2))&& logs[i].col > 240)
		{
			logs[i].col = 0;
		}
		else if(logs[i].col + logs[i].width < 0)
		{
			logs[i].col = 240 - logs[i].width;
		}

	}

	//Draw Logs and Pass Variables
	for(i = 0; i < NUMLOGS; i++)
	{
		drawRect4(logs[i].row, logs[i].col, logs[i].height, logs[i].width, LOGCOLOR);
		logs[i].oldoldcol = logs[i].oldcol;
		logs[i].oldcol = logs[i].col;
	}

	//Draw Frog and Pass Variables
	drawRect4(froggy[0].row, froggy[0].col, froggy[0].size, froggy[0].size, froggy[0].cindex);

	froggy[0].oldrow = froggy[0].row;
	froggy[0].oldcol = froggy[0].col;
	froggy[0].oldoldcol = froggy[0].oldcol;
	froggy[0].oldoldrow = froggy[0].oldrow;

	//Draw Cars and Pass Variables
	for(i = 0; i < NUMCARS; i++)
	{
		drawRect4(cars[i].row, cars[i].col, cars[i].height, cars[i].width, cars[i].cindex);
		cars[i].oldoldcol = cars[i].oldcol;
		cars[i].oldcol = cars[i].col;
	}

	//Erase Old Lives
	for(i = 0; i < 3; i++)
	{
		drawRect4(3,40+i*12,10,10,DARKERGREENINDEX);
	}

	//Draw Current Lives
	for(i = 0; i < froggy[0].lives; i++)
	{
		drawRect4(3,40+i*12,10,10,GREENINDEX);
	}
}

void checkMovementAndCollision(FROG froggy[], CAR cars[], LOG log[], PAD pad[], int i)
{
	// Frog Movement
	if(!KEY_DOWN_NOW(BUTTON_UP))
	{
		froggy[0].up = 1;
	}

	if(KEY_DOWN_NOW(BUTTON_UP) && froggy[0].up)
	{
		froggy[0].row -= froggy[0].jump;
		froggy[0].up = 0;
	}


	if(KEY_DOWN_NOW(BUTTON_DOWN) && froggy[0].down)
	{
		froggy[0].row += froggy[0].jump;
		froggy[0].down = 0;
	}

	if(!KEY_DOWN_NOW(BUTTON_DOWN))
	{
		froggy[0].down = 1;
	}

	if(KEY_DOWN_NOW(BUTTON_LEFT) && froggy[0].left)
	{
		froggy[0].col -= froggy[0].jump;
		froggy[0].left = 0;
	}

	if(!KEY_DOWN_NOW(BUTTON_LEFT))
	{
		froggy[0].left = 1;
	}

	if(KEY_DOWN_NOW(BUTTON_RIGHT) && froggy[0].right)
	{
		froggy[0].col += froggy[0].jump;
		froggy[0].right = 0;
	}

	if(!KEY_DOWN_NOW(BUTTON_RIGHT))
	{
		froggy[0].right = 1;
	}

	//Checks for Side Collision
	if(froggy[0].row < 0)
	{
		froggy[0].row = 0;
	}

	if(froggy[0].row > 160)
	{
		froggy[0].row = 160 - froggy[0].size;
	}

	//Checks for Top Collision
	for(i = 0; i < 5; i++)
	{
		if(froggy[0].row < 32 &&
			froggy[0].col + froggy[0].size > i*52 &&
			froggy[0].col < 32 + i*52)
		{
			froggy[0].row = froggy[0].oldoldrow;
		}
	}

	//Checks for Pad Collision
	for(i = 0; i < 4; i++)
	{
		if(froggy[0].row < 32 &&
		froggy[0].col + froggy[0].size > 34+i*52 &&
		froggy[0].col < 50 + i*52 &&
		pads[i].occupied != 1)
		{
			froggy[0].row = 19;
			froggy[0].col = 37 + i*52;
			pads[i].occupied = 1;
			froggy[0].padCollide = 1;
		}
		else if(froggy[0].row < 32 &&
		froggy[0].col + froggy[0].size > 34+i*52 &&
		froggy[0].col < 50 + i*52 &&
		pads[i].occupied)
		{
			froggy[0].row = froggy[0].oldoldrow;
		}
	}

	//River and Log Collision
	if(froggy[0].col > 0 &&
		froggy[0].col + froggy[0].size < 240 &&
		froggy[0].row > RIVERSTART + 16 &&
		froggy[0].row + froggy[0].size < RIVERSTART + RIVERHEIGHT)
	{
		for(i = 0; i < NUMLOGS; i++)
		{
			if(froggy[0].col + froggy[0].size/2 > logs[i].col &&
				froggy[0].col < logs[i].col + logs[i].width - froggy[0].size/2 &&
				froggy[0].row + froggy[0].size > logs[i].row &&
				froggy[0].row < logs[i].row + logs[i].height)
			{
					froggy[0].col += logs[i].speed;
					froggy[0].row = logs[i].row + 1;
					froggy[0].logCollide = 1;
					if(log[i].col + logs[i].height - froggy[0].size == 240)
					{
						froggy[0].col = 0;
					}
			}
		}
		if(froggy[0].col == 0 && froggy[0].logCollide != 1)
		{
			froggy[0].status = DEAD;
			froggy[0].waterCollide = 1;
		}
		else if(froggy[0].logCollide != 1)
		{
			froggy[0].status = DEAD;
			froggy[0].waterCollide = 1;
		}

		froggy[0].logCollide = 0;
	}


	//Car Collision
	for(i = 0; i < NUMCARS; i++)
	{
		if(froggy[0].col + froggy[0].size > cars[i].col &&
			froggy[0].col < cars[i].col + cars[i].width &&
			froggy[0].row + froggy[0].size > cars[i].row &&
			froggy[0].row < cars[i].row + cars[i].height &&
			froggy[0].carCollide == 0)
		{

				froggy[0].status = DEAD;
				froggy[0].carCollide = 1;
		}
	}
}
