/*-------------------------------------------------------------------
 *
 * myLib.h -- Header File for general GBA programming
 *
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
#define LTGRAY COLOR(25, 25, 25)
#define DARKGREEN COLOR(10,25,10)
#define BROWN COLOR(17,8,2)
#define GRAY COLOR(15,15,15)
#define DARKERGREEN COLOR(0,25,0)

// Prototypes
void setPixel3(int, int, unsigned short);
void drawRect3(int row, int col, int height, int width, volatile unsigned short color);
void waitForVblank();
void fillScreen3(volatile unsigned short color);
void setPixel4(int row, int col, unsigned char index);
void drawRect4(int row, int col, int height, int width, volatile unsigned char index);
void FlipPage();
void copyPicture4(const unsigned short *buffer);

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

#define KEY_DOWN_NOW(key)  (~BUTTONS & key)

/* DMA */

typedef struct
{								// ***********************************************************
	 const volatile void *src;	// We mark this as const which means we can assign it const
	 volatile void *dst;		// things without the compiler yelling but we can also pass it
	 volatile u32 cnt;			// things that are not const!
								// ***********************************************************
} DMAREC;

#define DMA ((volatile DMAREC *)0x040000B0)

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define START_ON_FIFO_EMPTY 0x30000000

// Mode 4
#define MODE4 4
#define PALETTE ((u16 *)0x5000000)


#define BUFFER0 ((u16 *)0x6000000)
#define BUFFER1 ((u16 *)0x600A000)

#define BUFFER1FLAG (1<<4)
