///////////////////////////////////////////////////////////////////////
// Name: Rahmaan Lodhia												 //
// Prism Account: rlodhia3											 //
// Collaboration: 													 //
// "I worked on the homework assignment alone, using only 			 //
// course materials." 												 //
///////////////////////////////////////////////////////////////////////


#include "myLib.h"
#include "textTile.h"
#include "dice.h"
#include <stdio.h>

#define MAXWIDTH 239
#define MAXHEIGHT 159

typedef enum { TITLE, CHOOSELINE, PASSLINEBET, DONTPASSLINEBET, WIN, LOSE} STATE; //Creat Gamestates

//prototypes
void titleScreen();
void loseScreen();
void winScreen(int payOut);
void chooseLineScreen();
void passLineScreen();
void dontPassLineScreen();
int rollDice(int row, int col, int duration);
void clearMainScreen();
void clearTextScreen();

int main(void)
{
    int i;
	int diceRoll = 0;
	int diceRoll2 = 0;
	int bet = 0;
	int payOut = 0;
	int count = 0;

	u16 myPalette[] = {BLACK, WHITE, RED, GREEN, BLUE}; //Make Colors

	for(i=0; i<16384/2; i++) //Stores Text Tiles
	{
	 CHARBLOCKBASE[1].tileimg[i] = fontdata_8x8[i*2] | (fontdata_8x8[i*2+1]<<8);
	}

	for(i=0; i<1600/2; i++) //Stores Dice Tiles
	{
	 CHARBLOCKBASE[0].tileimg[i] = dice_8x8[i*2] | (dice_8x8[i*2+1]<<8);
	}

	for(i=0; i<5; i++) //Stores Palette Colors
	{
	 PALETTE[i] = myPalette[i];
	}

    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;

    REG_BG0CNT = BG_SIZE0 | SBB(30) | COLOR256 | CBB(0);  //Layer for Dice
    REG_BG1CNT = BG_SIZE0 | SBB(31) | COLOR256 | CBB(1);  //Layer for Text

    STATE gameState = TITLE; //Sets Initial Game State

    while(1)
    {
    	switch(gameState)
    	{
    	case TITLE:
    		titleScreen();
    		while(KEY_DOWN_NOW(BUTTON_START)){};
			while(!KEY_DOWN_NOW(BUTTON_START))
			{
				count++; //Time Count for Seeding
			}
			srand(count);//Random Seed
    		gameState = CHOOSELINE;
    		clearTextScreen();
    		waitForVblank();
    		break;
    	case CHOOSELINE:
    		chooseLineScreen();
    		//Checks for Bet Type
    		while(!KEY_DOWN_NOW(BUTTON_A) && !KEY_DOWN_NOW(BUTTON_B)){}
    		if(KEY_DOWN_NOW(BUTTON_A))
			{
				gameState = PASSLINEBET;
			}

			if(KEY_DOWN_NOW(BUTTON_B))
			{
				gameState = DONTPASSLINEBET;
			}
    		while(KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_B)){}
			clearTextScreen();
    		waitForVblank();
    		break;
    	case PASSLINEBET:
    		passLineScreen();
    		//Checks for Bet Amount
    		while(!KEY_DOWN_NOW(BUTTON_A) && !KEY_DOWN_NOW(BUTTON_B)){}

			if(KEY_DOWN_NOW(BUTTON_A))
			{
				bet = 5;
			}

			if(KEY_DOWN_NOW(BUTTON_B))
			{
				bet = 25;
			}

    		while(KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_B)){}

    		//Rolls Dice and Computes Results
    		putText(12,0,"Bet Accepted");
    		waitForVblank();
    		putText(14,0, "Rolling");
    		waitForVblank();
    		diceRoll = rollDice(18,2,50);
    		waitForVblank();
    		if(diceRoll == 7 || diceRoll == 11)
    		{
    			gameState = WIN;
    		}
    		else if(diceRoll == 2 || diceRoll == 3 || diceRoll == 12)
    		{
    			gameState = LOSE;
    		}
    		else
    		{
    			putText(16,0,"Press Start to Roll Again");
    			waitForVblank();
    			while(!KEY_DOWN_NOW(BUTTON_START))
				{
				}
    			diceRoll2 = rollDice(18,9,50);
    			waitForVblank();
    			if(diceRoll == diceRoll2)
    			{
    				gameState = WIN;
    			}
    			else if(diceRoll == 7)
    			{
    				gameState = LOSE;
    			}
    			else
    			{
    				gameState = LOSE;
    			}
    		}
    		putText(12,16,"Press Start");
    		putText(14,16,"to See Result");
    		waitForVblank();
    		while(!KEY_DOWN_NOW(BUTTON_START))
			{
			}
    		clearTextScreen();
    		clearMainScreen();
    		waitForVblank();
    		break;
    	case DONTPASSLINEBET:
    		dontPassLineScreen();
    		//Checks for Bet Amount
    		while(!KEY_DOWN_NOW(BUTTON_A) && !KEY_DOWN_NOW(BUTTON_B)){}

			if(KEY_DOWN_NOW(BUTTON_A))
			{
				bet = 5;
			}

			if(KEY_DOWN_NOW(BUTTON_B))
			{
				bet = 25;
			}

			while(KEY_DOWN_NOW(BUTTON_A) || KEY_DOWN_NOW(BUTTON_B)){}

			//Rolls Dice and Computes Results
			putText(12,0,"Bet Accepted");
			waitForVblank();
			putText(14,0, "Rolling");
			waitForVblank();
			diceRoll = rollDice(18,2,50);
			waitForVblank();
			if(diceRoll == 7 || diceRoll == 11)
			{
				gameState = LOSE;
			}
			else if(diceRoll == 2 || diceRoll == 3 || diceRoll == 12)
			{
				gameState = WIN;
			}
			else
			{
				putText(16,0,"Press Start to Roll Again");
				waitForVblank();
				while(!KEY_DOWN_NOW(BUTTON_START))
				{
				}
				diceRoll2 = rollDice(18,9,50);
				waitForVblank();
				if(diceRoll == diceRoll2)
				{
					gameState = LOSE;
				}
				else if(diceRoll == 7)
				{
					gameState = WIN;
				}
				else
				{
					gameState = WIN;
				}
			}
			putText(12,16,"Press Start");
			putText(14,16,"to See Result");
			waitForVblank();
			while(!KEY_DOWN_NOW(BUTTON_START))
			{
			}
			clearTextScreen();
			clearMainScreen();
			waitForVblank();
    		break;
    	case WIN:
    		payOut = 2*bet;
    		winScreen(payOut);
    		while(KEY_DOWN_NOW(BUTTON_START)){}
    		while(!KEY_DOWN_NOW(BUTTON_START))
			{
			}
			gameState = TITLE;
			clearTextScreen();
			waitForVblank();
    		break;
    	case LOSE:
    		loseScreen();
    		while(KEY_DOWN_NOW(BUTTON_START)){}
    		while(!KEY_DOWN_NOW(BUTTON_START))
			{
			}
			gameState = TITLE;
			clearTextScreen();
			waitForVblank();
    		break;
    	}
    }

   return 0;
}

void titleScreen() //Displays Title Screen
{
	putText(5,12,"Craps");
	putText(8,7, "Push Start to Play");
}

void loseScreen() //Displays Lose Screen
{
	putText(5,8,"Your Roll Lost");
	putText(8,3, "Push Start to Play Again");
}

void winScreen(int payOut) //Displays Win Screen
{
	putText(5,8,"Your Roll Won");
	switch(payOut) //Determines Payout
	{
	case 10:
		putText(8,5, "Your Payout is $10");
		break;
	case 50:
		putText(8,5, "Your Payout is $50");
		break;
	}
	putText(10,3, "Press Start to Play Again");
}

void chooseLineScreen() //Display Bet Types
{
	putText(5,11,"Press A");
	putText(7,3, "To Place a Pass Line Bet");
	putText(10,11,"Press B");
	putText(12,0, "To Place a Don't Pass Line Bet");
}

void clearTextScreen() //Erases Text
{
	int i;
	for(i=0; i < 1024; i++)
	 {
		 SCREENBLOCKBASE[31].tilemap[i] = 0;
	 }
}

void clearMainScreen() //Erases Dice
{
	int i;
	for(i=0; i < 1024; i++)
	 {
		 SCREENBLOCKBASE[30].tilemap[i] = 0;
	 }
}

void passLineScreen() //Displays Bets for Pass Lines
{
	putText(0,3,"Press A");
	putText(2,3, "To Place a $5 Bet");
	putText(5,3,"Press B");
	putText(7,3, "To Place a $25 Bet");
}
void dontPassLineScreen() //Displays Bets for Don't Pass Lines
{
	putText(0,3,"Press A");
	putText(2,3, "To Place a $5 Bet");
	putText(5,3,"Press B");
	putText(7,3, "To Place a $25 Bet");
}


int rollDice(int row, int col, int duration) //Rolls and Animates Dice
{
	int n;
	int d1;
	int d2;
	for(n = 0; n < duration; n++)
	{
		drawDice(row, col, rand()%6+1);
		drawDice(row, col+3, rand()%6+1);
		waitForVblank();
	}
	d1 = rand()%6+1;
	d2 = rand()%6+1;
	drawDice(row, col, d1);
	drawDice(row, col+3, d2);
	waitForVblank();
	return d1 + d2;
}



