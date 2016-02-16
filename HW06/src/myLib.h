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
#define BG0_ENABLE (1<<8)
#define BG1_ENABLE (1<<9)
#define BG2_ENABLE (1<<10)
#define BG3_ENABLE (1<<11)

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

// Mode 0


#define MODE0 0

typedef struct
{
    u16 tileimg[8192];
    
} charblock;

typedef struct
{
    u16 tilemap[1024];

} screenblock;


#define CHARBLOCKBASE ((charblock *)0x6000000)
#define SCREENBLOCKBASE ((screenblock *)0x6000000)

//background offset registers
#define REG_BG0HOFS *(volatile unsigned short *)0x04000010
#define REG_BG1HOFS *(volatile unsigned short *)0x04000014
#define REG_BG2HOFS *(volatile unsigned short *)0x04000018
#define REG_BG3HOFS *(volatile unsigned short *)0x0400001C

#define REG_BG0VOFS *(volatile unsigned short *)0x04000012
#define REG_BG1VOFS *(volatile unsigned short *)0x04000016
#define REG_BG2VOFS *(volatile unsigned short *)0x0400001A
#define REG_BG3VOFS *(volatile unsigned short *)0x0400001E
//background control registers
#define REG_BG0CNT *(volatile unsigned short*)0x4000008
#define REG_BG1CNT *(volatile unsigned short*)0x400000A
#define REG_BG2CNT *(volatile unsigned short*)0x400000C
#define REG_BG3CNT *(volatile unsigned short*)0x400000E

    //macros and bit constants for setting the background control register specifics
#define SBB(num) ((num) << 8)
#define CBB(num) ((num) << 2)

#define COLOR256 1 << 7
                            // Cols x Row
#define BG_SIZE0 0<<14      // 32 x 32 tiles
#define BG_SIZE1 1<<14      // 64 x 32
#define BG_SIZE2 2<<14      // 32 x 64
#define BG_SIZE3 3<<14      // 64 x 64

// Sprites .........................................................

typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 fill;
} ObjAttr;

//Sprite definitions
#define SPRITEMEM  ((ObjAttr *)0x7000000)
#define SPRITEDATA ((u16 *)(0x6010000) )
#define SPRITEPAL  ((u16 *)0x5000200)
#define OBJ_ENABLE 0x1000
#define MODE1D (1<<6)

// ATTR0

// 0-7 Row position of the top of the sprite.

// 8-9 Object Mode
#define ATTR0_REG (0<<8)
#define ATTR0_AFF (1<<8)
#define ATTR0_HIDE (2<<8)
#define ATTR0_AFF_DBL (3<<8)

// 10-11 Graphics Mode for special effects
#define ATTR0_BLEND (1<<10) // Forbidden to use both of these
#define ATTR0_WIN (2<<10)

// 12 Mosaic Effect
#define ATTR0_MOSAIC (1<<12)

// 13 Color Mode
#define ATTR0_4BPP 0          // 16 colors
#define ATTR0_8BPP (1<<13)    // 256 colors

// 14-15 Shape
#define ATTR0_SQUARE 0
#define ATTR0_WIDE (1<<14)
#define ATTR0_TALL (2<<14)

// ATTR1

// 0-8 Column position of left hand side of sprite

// 9-13 Valid if Affine Flag (Attribute 0 Bit 8)
// Defines which OAM_AFF_ENTY this sprite uses.

// 12-13
#define ATTR1_NOFLIP 0
#define ATTR1_HFLIP (1<<12)
#define ATTR1_VFLIP (1<<13)
// Used only if the Affine Flag (Attribute 0 Bit 8) is clear

// 14-15 Size...Together with the shape bits Attribute 0 Bits 14-15
// these determine the sprite's real size, see table:

//                                          col x row
/*-------------------------------------------------------------
 *
 *       Size                   00      01      10      11
 *   Shape
 *              00              8x8     16x16   32x32   64x64
 *         Wide 01              16x8    32x8    32x16   64x32
 *         Tall 10              8x16    8x32    16x32   32x64
 *------------------------------------------------------------*/
#define ATTR1_SIZE8 0
#define ATTR1_SIZE16 (1<<14)
#define ATTR1_SIZE32 (2<<14)
#define ATTR1_SIZE64 (3<<14)

// ATTR2

//0-9 Base tile-index of sprite. Note that in bitmap modes this must
// be 512 or higher.

// 10-11 Priority. Higher priorities are drawn first (and therefore
// can be covered by later sprites and backgrounds). Sprites cover
// backgrounds of the same priority, and for sprites of the same
// priority, the higher OBJ_ATTRs are drawn first.
#define ATTR2_PRI0 0
#define ATTR2_PRI1 (1<<10)
#define ATTR2_PRI2 (2<<10)
#define ATTR2_PRI3 (3<<10)

// 12-15 Palette-bank to use when in 16-color mode. Has no effect if
//the color mode flag Attribute 0 Bit 12 is set.
#define ATTR2_PALETTE_BANK(pbn) ((pbn)<<12)

// *** Timers ========================================================

#define REG_TM0CNT *(volatile u16*)0x4000102
#define REG_TM1CNT *(volatile u16*)0x4000106
#define REG_TM2CNT *(volatile u16*)0x400010A
#define REG_TM3CNT *(volatile u16*)0x400010E

#define REG_TM0D       *(volatile u16*)0x4000100
#define REG_TM1D       *(volatile u16*)0x4000104
#define REG_TM2D       *(volatile u16*)0x4000108
#define REG_TM3D       *(volatile u16*)0x400010C

// Timer flags
//#define TM_ON (1<<7)
#define TIMER_ENABLED       0x0080
#define TM_CASCADE (1<<2)
#define TM_FREQ_1 0
#define TM_FREQ_64 1
#define TM_FREQ_256 2
#define TM_FREQ_1024 3
#define TM_IRQ (1<<6)

