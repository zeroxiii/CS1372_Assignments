#include "myLib.h"
#include "background.h"
#include "tanks.h"

#define WIDTHMIN 0		// Change to negative to see bug
#define WIDTHMAX 240

#define HEIGHTMIN 0
#define HEIGHTMAX 160

#define MASK (0x1FF)

#define SPRITEOFFSET16(r,c) (r)*32+(c)

#define NUMSPRITES 8

const u16 *spriteTiles = tanksTiles;
const u16 *spritePalette = tanksPal;

typedef struct {
    int row;
    int col;
    int start;
    int shape;
    int size;
    int height;
    int width;
    int rdel;
    int cdel;
} Sprite;

int main(void)
{
	//Initializing Program variables
    int i;
	int visible = 1;
	int press = 1;
	int oldSprite = 0;
	int currentSprite = 0;
    ObjAttr shadowOAM[128];

    REG_DISPCTL = MODE0 | BG0_ENABLE | OBJ_ENABLE;

    // Load background palette
    for(i=0; i<256; i++)
    {
        PALETTE[i] = backgroundPal[i];
    }

    // Load background tile images
    for(i=0; i<backgroundTilesLen/2; i++)
    {
        CHARBLOCKBASE[0].tileimg[i] = backgroundTiles[i];
    }

	//Make Map
    for(i=0; i<1024; i++)
	{
		SCREENBLOCKBASE[28].tilemap[i] = 1;
	}

    REG_BG0CNT = SBB(28) | CBB(0) | COLOR256 | BG_SIZE0;

	//Define Sprites
    Sprite sprites[NUMSPRITES] = {{16,16,SPRITEOFFSET16(0,0),ATTR0_SQUARE,ATTR1_SIZE32,32,32,1,1},
						{0,0,SPRITEOFFSET16(0,8),ATTR0_SQUARE,ATTR1_SIZE32,32,32,1,1},
						{0,0,SPRITEOFFSET16(0,16),ATTR0_SQUARE,ATTR1_SIZE32,32,32,1,1},
						{5,100,SPRITEOFFSET16(0,24),ATTR0_SQUARE,ATTR1_SIZE32,32,32,1,1},
						{0,0,SPRITEOFFSET16(4,0),ATTR0_SQUARE,ATTR1_SIZE32,32,32,1,1},
						{0,0,SPRITEOFFSET16(4,8),ATTR0_SQUARE,ATTR1_SIZE32,32,32,1,1},
						{0,0,SPRITEOFFSET16(4,16),ATTR0_SQUARE,ATTR1_SIZE32,32,32,1,1},
						{0,0,SPRITEOFFSET16(4,16),ATTR0_SQUARE,ATTR1_SIZE32,32,32,1,1}};

    // Load sprite palette
    for(i=0; i<256; i++)
    {
        SPRITEPAL[i] = spritePalette[i];
    }

    // Load sprite images
    for(i=0; i<8192/2; i++)
    {
        CHARBLOCKBASE[4].tileimg[i] = spriteTiles[i];
    }

    
	// Set attributes for all active sprites
	for(i=0; i<NUMSPRITES; i++)
	{
		shadowOAM[i].attr0 = sprites[i].row | ATTR0_8BPP | sprites[i].shape;
		shadowOAM[i].attr1 = sprites[i].col | sprites[i].size;
		shadowOAM[i].attr2 = sprites[i].start | ATTR2_PALETTE_BANK(0);
	}

	//Hide Sprites
	for(i=0; i<128; i++)
	{
		shadowOAM[i].attr0 = ATTR0_HIDE;
	}


	waitForVblank();

	//Move Sprites to Mem
	for(i=0; i<128; i++)
	{
		SPRITEMEM[i] = shadowOAM[i];
	}

    while(FOREVER)
    {

		//Check for Movement and change direction
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			shadowOAM[currentSprite].attr0 = ATTR0_HIDE;
			sprites[currentSprite].row -= sprites[currentSprite].rdel;
			oldSprite = currentSprite;
			currentSprite = 2;
			sprites[currentSprite].col = sprites[oldSprite].col;
			sprites[currentSprite].row = sprites[oldSprite].row;
		}


		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			shadowOAM[currentSprite].attr0 = ATTR0_HIDE;
			sprites[currentSprite].row += sprites[currentSprite].rdel;
			oldSprite = currentSprite;
			currentSprite = 0;
			sprites[currentSprite].col = sprites[oldSprite].col;
			sprites[currentSprite].row = sprites[oldSprite].row;
		}

		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			shadowOAM[currentSprite].attr0 = ATTR0_HIDE;
			sprites[currentSprite].col -= sprites[currentSprite].cdel;
			oldSprite = currentSprite;
			currentSprite = 6;
			sprites[currentSprite].col = sprites[oldSprite].col;
			sprites[currentSprite].row = sprites[oldSprite].row;
			
		}

		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			shadowOAM[currentSprite].attr0 = ATTR0_HIDE;
			sprites[currentSprite].col += sprites[currentSprite].cdel;
			oldSprite = currentSprite;
			currentSprite = 5;
			sprites[currentSprite].col = sprites[oldSprite].col;
			sprites[currentSprite].row = sprites[oldSprite].row;
		}

		//Check for second sprites visibility
		if(KEY_DOWN_NOW(BUTTON_START) && press)
		{
			if(visible)
				visible = 0;
			else
				visible = 1;
			waitForVblank();
			press = 0;
		}

		if(!KEY_DOWN_NOW(BUTTON_START))
		{
			press = 1;
		}

		//Collision Detection
		if(sprites[currentSprite].row < HEIGHTMIN)
		{
		   sprites[currentSprite].row = HEIGHTMIN;
		}

		if(sprites[currentSprite].col < WIDTHMIN)
		{
		   sprites[currentSprite].col = WIDTHMIN;
		}

		if(sprites[currentSprite].row + sprites[currentSprite].height > HEIGHTMAX)
		{
		   sprites[currentSprite].row = HEIGHTMAX - sprites[currentSprite].height;
		}

		if(sprites[currentSprite].col + sprites[currentSprite].width > WIDTHMAX)
		{
		   sprites[currentSprite].col = WIDTHMAX - sprites[currentSprite].width;
		}

		//Move Sprites to Memory
		shadowOAM[currentSprite].attr0 = sprites[currentSprite].row | ATTR0_8BPP | sprites[currentSprite].shape;
		shadowOAM[currentSprite].attr1 = (MASK&sprites[currentSprite].col) | sprites[currentSprite].size;
		shadowOAM[currentSprite].attr2 = sprites[currentSprite].start | ATTR2_PALETTE_BANK(0);

		if(visible)
		{
		   shadowOAM[3].attr0 = sprites[3].row | ATTR0_8BPP | sprites[3].shape;
		   shadowOAM[3].attr1 = (MASK&sprites[3].col) | sprites[3].size;
		   shadowOAM[3].attr2 = sprites[3].start | ATTR2_PALETTE_BANK(0);
		}
		else
		{
			shadowOAM[3].attr0 = ATTR0_HIDE;
		}

		waitForVblank();

		for(i=0; i<NUMSPRITES; i++)
		{
		   SPRITEMEM[i] = shadowOAM[i];
		}
    }
    return 0;
}




