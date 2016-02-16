///////////////////////////////////////////////////////////////////////
// Name: Rahmaan Lodhia//
// Prism Account: rlodhia3//
// Collaboration: //
// "I received outside aid on this assigned from the following //
// person(s): //
///////////////////////////////////////////////////////////////////////

#include "myLib.h"
#include "ball.h"
#include "linkedlist.h"

//Screen Variables
#define WIDTHMIN 0	
#define WIDTHMAX 240

#define HEIGHTMIN 0
#define HEIGHTMAX 160

//Sprite Macros
#define MASK (0x1FF)
#define SPRITEOFFSET16(r,c) (r)*32+(c)

//Program Variables
const u16 *spriteTiles = ballTiles;
const u16 *spritePalette = ballPal;
//Sprite Variables
ObjAttr shadowOAM[128];

int numBall = 0; //Number of Ball indicating when it was created
int press = 1; //Checks if button has been pushed before
LLNODE *head = NULL; //Initialize Head Pointer


//Prototypes
void setRegister();
void initializeTiles();
void drawSpots();
void initializeSprites();
Sprite *allocateBall(LLNODE *head);
Sprite *createBall(Sprite *b);
Sprite *inputCreateBall();
void drawBalls(void *ball);
void moveSpriteToMem();
void moveBalls(void *ball);

//Tiles
const unsigned char tiles[256] = 
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,

	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,

	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,

	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
};


int main(void)
{
	//Setup Environment
	setRegister();
	initializeTiles();
	drawSpots();
	initializeSprites();
	
	//Create First Ball
	Sprite *b = NULL;
	b = allocateBall(head);
	head = addToFront(head,b);

	while(FOREVER)
	{	
		//Check for Input
		if(KEY_DOWN_NOW(BUTTON_A) && press)
		{
			press = 0;
		}
		if(!KEY_DOWN_NOW(BUTTON_A) && !press)
		{
			head = addToFront(head,inputCreateBall());
			press = 1;
		}
		//Traverse through balls if they exist
		if(head != NULL)
		{
			traverse(head, moveBalls);
			traverse(head, drawBalls);
			waitForVblank();
			moveSpriteToMem();
		}
	}
	
	return 0;
}

//Allocate Memory for first ball
Sprite *allocateBall(LLNODE *head)
{
	Sprite *b;
	numBall += 1;
	b = malloc(sizeof(Sprite));
	b->number = numBall;
	b->row = 0;
	b->col = 0;
	b->start = SPRITEOFFSET16(0,0);
	b->shape = ATTR0_SQUARE;
	b->size = ATTR1_SIZE8;
	b->height = 8;
	b->width = 8;
	b->rdel = 1;
	b->cdel = 1;
	return b;
}

//Allocate Memory for Created ball
Sprite *createBall(Sprite *last)
{
	Sprite *b;
	numBall += 1;
	b = malloc(sizeof(Sprite));
	b->number = numBall;
	b->row = (last->row)+8*-(last->rdel);
	b->col = (last->col)+8*-(last->cdel);
	b->start = SPRITEOFFSET16(0,0);
	b->shape = ATTR0_SQUARE;
	b->size = ATTR1_SIZE8;
	b->height = 8;
	b->width = 8;
	b->rdel = -(last->rdel);
	b->cdel = -(last->cdel);
	return b;
}

//Allocate Memory for Input Created Ball
Sprite *inputCreateBall()
{
	Sprite *b;
	numBall += 1;
	b = malloc(sizeof(Sprite));
	b->number = numBall;
	b->row = 0;
	b->col = rand()%100+20;
	b->start = SPRITEOFFSET16(0,0);
	b->shape = ATTR0_SQUARE;
	b->size = ATTR1_SIZE8;
	b->height = 8;
	b->width = 8;
	b->rdel = 1;
	b->cdel = 1;
	return b;
}

//Copy Shadow to Sprite Memory
void moveSpriteToMem()
{
	int i;
	//Move Sprites to Mem
	for(i=0; i<128; i++)
	{
		SPRITEMEM[i] = shadowOAM[i];
	}
}

//Take Ball Sprites and place them in ShadowOAM
void drawBalls(void *ball)
{
	shadowOAM[(((Sprite *)ball)->number)-1].attr0 = ((Sprite *)ball)->row | ATTR0_4BPP | ((Sprite *)ball)->shape;
	shadowOAM[(((Sprite *)ball)->number)-1].attr1 = (MASK&(((Sprite *)ball)->col)) | ((Sprite *)ball)->size;
	shadowOAM[(((Sprite *)ball)->number)-1].attr2 = ((Sprite *)ball)->start | ATTR2_PALETTE_BANK(0);
}

//Move Balls and Check for collisions
void moveBalls(void *ball)
{
	(((Sprite *)ball)->col) += (((Sprite *)ball)->cdel);
	(((Sprite *)ball)->row) += (((Sprite *)ball)->rdel);

	//Collision Detection
	if((((Sprite *)ball)->row) < HEIGHTMIN)
	{
	   (((Sprite *)ball)->row) = HEIGHTMIN;
	   (((Sprite *)ball)->rdel) = -(((Sprite *)ball)->rdel);
	}

	if((((Sprite *)ball)->col) < WIDTHMIN)
	{
	   (((Sprite *)ball)->col) = WIDTHMIN;
	   (((Sprite *)ball)->cdel) = -(((Sprite *)ball)->cdel);
	}

	if((((Sprite *)ball)->row) + (((Sprite *)ball)->height) > HEIGHTMAX)
	{
	   (((Sprite *)ball)->row) = HEIGHTMAX - (((Sprite *)ball)->height);
	   (((Sprite *)ball)->rdel) = -(((Sprite *)ball)->rdel);
	}

	if((((Sprite *)ball)->col) + (((Sprite *)ball)->width) > WIDTHMAX)
	{
	   (((Sprite *)ball)->col) = WIDTHMAX - (((Sprite *)ball)->width);
	   (((Sprite *)ball)->cdel) = -(((Sprite *)ball)->cdel);
	}

	//Check for Spot Collision
	
	//Double Spot
	if((((Sprite *)ball)->col) + (((Sprite *)ball)->width)/2 > 208 &&
		(((Sprite *)ball)->col) + (((Sprite *)ball)->width)/2 < 216 &&
		(((Sprite *)ball)->row) + (((Sprite *)ball)->height)/2 > 64 &&
		(((Sprite *)ball)->row) + (((Sprite *)ball)->height)/2 < 72)
	{
		(((Sprite *)ball)->col) += 8 * (((Sprite *)ball)->cdel);
		(((Sprite *)ball)->row) += 8 * (((Sprite *)ball)->rdel);
		head = addToFront(head,createBall((Sprite *)ball));
	}

	//Erase Spot
	if((((Sprite *)ball)->col) + (((Sprite *)ball)->width)/2 > 24 &&
		(((Sprite *)ball)->col) + (((Sprite *)ball)->width)/2 < 32 &&
		(((Sprite *)ball)->row) + (((Sprite *)ball)->height)/2 > 64 &&
		(((Sprite *)ball)->row) + (((Sprite *)ball)->height)/2 < 72)
	{
		shadowOAM[(((Sprite *)ball)->number)-1].attr0 = ATTR0_HIDE;
		deleteElement(head, (((Sprite *)ball)->number));
		
	}
}

//Initialize Tile Variables and Tile Map
void initializeTiles()
{
	int i;
	u16 myPalette[] = {BLACK, WHITE, RED, BLUE};

    for(i=0; i<256/2; i++) //Stores Tiles
	{
		CHARBLOCKBASE[0].tileimg[i] = tiles[i*2] | (tiles[i*2+1]<<8);
	}
	
	for(i=0; i < 1024; i++) //Create Map
	{
		SCREENBLOCKBASE[31].tilemap[i] = 0;
	}
	
    for(i=0; i<4; i++) //Store Palette
	{
    	PALETTE[i] = myPalette[i];
	}
}

//Set Video Registers
void setRegister()
{
	REG_DISPCTL = MODE0 | BG0_ENABLE;
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;

	REG_BG0CNT = BG_SIZE0 | SBB(31) | COLOR256 |  CBB(0);
	REG_DISPCTL = MODE0 | BG0_ENABLE | OBJ_ENABLE;
}

//Draw Spots on Screen
void drawSpots()
{
		SCREENBLOCKBASE[31].tilemap[8*32 + 3] = 2;
		SCREENBLOCKBASE[31].tilemap[8*32 + 26] = 3;
}

//Initialize Sprites and Variables
void initializeSprites()
{
	int i;

	// Load sprite palette
    for(i=0; i<256; i++)
    {
        SPRITEPAL[i] = spritePalette[i];
    }

	// Load sprite images
    for(i=0; i<32/2; i++)
    {
        CHARBLOCKBASE[4].tileimg[i] = spriteTiles[i];
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

