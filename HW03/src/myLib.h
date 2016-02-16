/*-------------------------------------------------------------------
* myLib.h -- Header File for general GBA programming
*------------------------------------------------------------------*/
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// Useful addresses
#define REG_DISPCTL (*(u16 *)0x4000000)
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)
#define VIDBUFADR ((unsigned short *)0x6000000)

// Generally useful symbols
#define FOREVER 1
#define TRUE 1
#define FALSE 0

// Video
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define OFFSET(r,c) ((r)*240+(c))
extern unsigned short *videoBuffer;

// Colors
#define COLOR(r,g,b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31,31,31)
#define BLACK 0
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define YELLOW COLOR(31,31,0)
#define CYAN COLOR(0,31,31)
#define MAGENTA COLOR(31,0,31)

// Prototypes
void setPixel3(int, int, unsigned short);
void drawRect3(int row, int col, int height, int width, unsigned short color);
void waitForVblank();

// *** Input =========================================================
// Buttons
#define BUTTONS (*(volatile unsigned int *)0x04000130)
#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_SELECT 4
#define BUTTON_START 8
#define BUTTON_RIGHT 16
#define BUTTON_LEFT 32
#define BUTTON_UP 64
#define BUTTON_DOWN 128
#define BUTTON_R 256
#define BUTTON_L 512
#define BUTTON_INDEX_A 0
#define BUTTON_INDEX_B 1
#define BUTTON_INDEX_SELECT 2
#define BUTTON_INDEX_START 3
#define BUTTON_INDEX_RIGHT 4
#define BUTTON_INDEX_LEFT 5
#define BUTTON_INDEX_UP 6
#define BUTTON_INDEX_DOWN 7
#define BUTTON_INDEX_R 8
#define BUTTON_INDEX_L 9
#define KEY_DOWN_NOW(key) (~BUTTONS & key)
