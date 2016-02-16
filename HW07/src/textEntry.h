#include "myLib.h"
#include "texttile.h"
#include <stdio.h>
#include "cursor.h"
#include "beep.h"
#include "flute.h"

#define MAXWIDTH 240
#define MAXHEIGHT 159
#define CHARACTERLIMIT 15
#define NUMSPRITES 1
#define MASK (0x1FF)

#define SPRITEOFFSET16(r,c) (r)*32+(c)

extern char *buffer;

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


//Prototypes
void drawKeyboard();
void getText(char *buffer);
void initializeTiles();
void initializeSprites();
void setRegister();
void copyShadow();
void moveSpriteToMem();
void checkMovement();
void checkSelection(char *buffer);
void setupInterrupts();
void enableTimer2Interrupt();
void myInterruptHandler();
void enableVblankInterrupts();
