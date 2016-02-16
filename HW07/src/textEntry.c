#include "textEntry.h"

//Program Variables
const u16 *spriteTiles = cursorTiles;
const u16 *spritePalette = cursorPal;
//Sprite Variables
ObjAttr shadowOAM[128];
Sprite sprites[NUMSPRITES] = {{8,0,SPRITEOFFSET16(0,0),ATTR0_SQUARE,ATTR1_SIZE8,8,8,1,8}};
int left = 1;
int right = 1;
int press = 1;
int endInput = 0;
int letterIndex = 0;
int letterColumn = 0;

//Timer Variables
int theTime = 0;
unsigned int vblankcount = 0;
unsigned int start;    // At which vlankcount was beep started
unsigned int startBG;  // At which vlankcount was background (bg) started
int play = FALSE;   // When set to TRUE tells us to start beep
int playBG = FALSE; // This tell us if the BG is supposed to be playing
int BGplaying = FALSE; // This tells us if it is playing

// Duration in vlanks...there are 59.727 vlanks per second
int duration = BEEPLENGTH*59.727/11025;
int durationBG = FLUTELEN*59.727/FLUTEFREQ-1;

//Draws Keyboard
void drawKeyboard()
{
	int i,c;
	c = 0;
	char letter[] = "A";
	for(i = 0; i < 26; i++)
	{
		putText(0,c,letter);
		c++;
		letter[0] = 'A' + i + 1;
	}

	putText(0,27,"END");
	putText(3,0,"USE LEFT AND RIGHT");
	putText(4,0,"TO MOVE CURSOR");
	putText(5,0,"PRESS ENTER TO SELECT LETTER");
	putText(6,0,"15 CHARACTER LIMIT");
}

//Begins Text Input
void getText(char *buffer)
{
	setRegister();
	setupInterrupts();
	initializeTiles();
	initializeSprites();
	drawKeyboard();
	playBG = TRUE;	
	while(1)
	{
		if(playBG && !BGplaying)
        {
            // play the bg music
            DMA[2].cnt |= DMA_ON;
            REG_TM1CNT |= TM_ON;
            startBG = vblankcount;
            BGplaying = TRUE;
            DMA[2].src = flute;
        }
		checkMovement();
		if(!endInput)
		{
			checkSelection(buffer);
		}
		else
		{
			DMA[2].cnt &= ~DMA_ON;
            REG_TM1CNT &= ~TM_ON;
			playBG = FALSE;
			waitForVblank();
		}
		copyShadow();
		waitForVblank();
		moveSpriteToMem();
	}
}

//Sets Up Tiles
void initializeTiles()
{
	int i;
	u16 myPalette[] = {BLACK, WHITE};

    for(i=0; i<16384/4; i++)
	{
    	CHARBLOCKBASE[0].tileimg[i] = fontdata_8x8[i*4] |
								   (fontdata_8x8[i*4+1]<<4) |
								   (fontdata_8x8[i*4+2]<<8) |
								   (fontdata_8x8[i*4+3]<<12);
	}

    for(i=0; i < 1024; i++)
	{
		SCREENBLOCKBASE[31].tilemap[i] = 0;
	}

    for(i=0; i<2; i++)
	{
    	PALETTE[i] = myPalette[i];
	}
}

//Sets Up Sprites
void initializeSprites()
{
	int i;

	// Load sprite palette
    for(i=0; i<256; i++)
    {
        SPRITEPAL[i] = spritePalette[i];
    }

	// Load sprite images
    for(i=0; i<64/2; i++)
    {
        CHARBLOCKBASE[4].tileimg[i] = spriteTiles[i];
    }
		for(i=0; i<NUMSPRITES; i++)
	{
		shadowOAM[i].attr0 = sprites[i].row | ATTR0_8BPP | sprites[i].shape;
		shadowOAM[i].attr1 = sprites[i].col | sprites[i].size;
		shadowOAM[i].attr2 = sprites[i].start | ATTR2_PALETTE_BANK(0);
	}

		
	//Hide Sprites
	for(i=1; i<128; i++)
	{
		shadowOAM[i].attr0 = ATTR0_HIDE;
	}

	waitForVblank();
	for(i=0; i<128; i++)
	{
		SPRITEMEM[i] = shadowOAM[i];
	}

}

//Set Control Registers for Video and Timers
void setRegister()
{
	REG_DISPCTL = MODE0 | BG0_ENABLE;
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;

	REG_BG0CNT = BG_SIZE0 | SBB(31) |  CBB(0);
	REG_DISPCTL = MODE0 | BG0_ENABLE | OBJ_ENABLE;

	REG_TM2CNT = 0;
    REG_TM2D = -0x4000;
    REG_TM2CNT = TM_FREQ_1024 | TM_IRQ;
	

	
	// Setup sound
    REG_SOUNDCNT_X = SND_ENABLED;
    
    REG_SOUNDCNT_L = 0;
    REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 |
                        DSA_OUTPUT_RATIO_100 |
                        DSA_OUTPUT_TO_RIGHT |
                        DSA_TIMER0 |
                        DSA_FIFO_RESET |
                        DSB_OUTPUT_RATIO_100 |
                        DSB_OUTPUT_TO_LEFT |
                        DSB_TIMER1 |
                        DSB_FIFO_RESET;
    // DMA to play sound on DSA
    DMA[1].src = beep;
    DMA[1].dst = REG_FIFO_A;
    DMA[1].cnt = DMA_DESTINATION_FIXED |
                    DMA_REPEAT |
                    DMA_AT_REFRESH;

    // Timer 0 is used to play the beeps (DSA)
    REG_TM0D = -1522; // Value for 11025 Hz
    REG_TM0CNT = TM_FREQ_1;
	//DMA to play sound on DSB
    DMA[2].src = flute;
    DMA[2].dst = REG_FIFO_B;
    DMA[2].cnt = DMA_DESTINATION_FIXED |
                    DMA_REPEAT |
                    DMA_AT_REFRESH;
	// Timer 1 is used to play the background music (DSB)
    REG_TM1D = -380; // Value for 44100 Hz
    REG_TM1CNT = TM_FREQ_1;
}

//Copy Sprites to Shadow
void copyShadow()
{
	int i;
	for(i=0; i<NUMSPRITES; i++)
	{
		shadowOAM[i].attr0 = sprites[i].row | ATTR0_8BPP | sprites[i].shape;
		shadowOAM[i].attr1 = sprites[i].col | sprites[i].size;
		shadowOAM[i].attr2 = sprites[i].start | ATTR2_PALETTE_BANK(0);
	}

}

//Copy Shadow to Memory
void moveSpriteToMem()
{
	int i;
	//Move Sprites to Mem
	for(i=0; i<128; i++)
	{
		SPRITEMEM[i] = shadowOAM[i];
	}
}

//Checks Movement for Keyboard
void checkMovement()
{
	//Check for Movement and change direction
	if(KEY_DOWN_NOW(BUTTON_LEFT) && left)
	{
		if(letterIndex == 26)
		{
			sprites[0].col -= sprites[0].cdel;
		}
		sprites[0].col -= sprites[0].cdel;		
		left = 0;
		letterIndex -= 1;
	}

	if(KEY_DOWN_NOW(BUTTON_RIGHT) && right)
	{
		sprites[0].col += sprites[0].cdel;
		right = 0;
		letterIndex += 1;
		if(letterIndex >= 26)
		{
			sprites[0].col += sprites[0].cdel;
		}
	}
	if(!KEY_DOWN_NOW(BUTTON_LEFT))
	{
		left = 1;
	}
	if(!KEY_DOWN_NOW(BUTTON_RIGHT))
	{
		right = 1;
	}
	if(sprites[0].col < 0)
	{
		sprites[0].col = 0;
		letterIndex = 0;
	}
	if(sprites[0].col > MAXWIDTH-16)
	{
		sprites[0].col = MAXWIDTH - 24;
		letterIndex = 26;
	}
	
}

//Determines Output and Stores in Buffer
void checkSelection(char *buffer)
{
	
	if(KEY_DOWN_NOW(BUTTON_START) && press)
	{
		press = 0;
	}
	if(!KEY_DOWN_NOW(BUTTON_START) && !press)
	{
		char input[] = "A";
		input[0] = 'A' + letterIndex;
		press = 1;
		if(letterIndex != 26)
		{
			if(letterColumn < CHARACTERLIMIT)
			{
				putText(15,letterColumn,input);
				buffer[letterColumn] = input[0];
				// Play the beep
				DMA[1].cnt |= DMA_ON;
				REG_TM0CNT |= TM_ON;
			}
		}
		else
		{				
			DMA[1].cnt &= ~DMA_ON;
			REG_TM0CNT &= ~TM_ON;
			playBG = FALSE;
			endInput = 1;
		}
		
		letterColumn += 1;
	}
	
}

void setupInterrupts()
{
    REG_IME = 0;
    REG_INTERRUPT = (u32)myInterruptHandler;
    enableTimer2Interrupt();
    enableVblankInterrupts();
    REG_IME = 1;
}

void enableTimer2Interrupt()
{
    REG_IE = REG_IE | INT_T2;
}

void enableVblankInterrupts()
{
    REG_DISPSTAT = INT_VBLANK_ENABLE; // Tell video to start interrupting
    REG_IE = REG_IE | INT_VB; // Start paying attention to vblanks
}

void myInterruptHandler()
{
    REG_IME = 0;
    if(REG_IF == INT_T2)
    {
        theTime++;
        play = TRUE;
    }
    if(REG_IF == INT_VB)
    {
        vblankcount++;
        if(vblankcount - start > duration)
        {
            // Turn off beeps
            DMA[1].cnt &= ~DMA_ON;
            REG_TM0CNT &= ~TM_ON;
        }

        if(vblankcount - startBG > durationBG)
        {
            // Turn off bg and set flag to tell game loop to
            // restart it
            DMA[2].cnt &= ~DMA_ON;
            REG_TM1CNT &= ~TM_ON;
            BGplaying = FALSE;
        }
            
    }
    REG_IF = REG_IF;
    REG_IME = 1;
}
