/*-------------------------------------------------------------------
 *
 * Library for general GBA programming
 *
 *-----------------------------------------------------------------*/
#include "myLib.h"

#define USE_DMA

unsigned short *videoBuffer = VIDBUFADR;

void setPixel3(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row,col)]  = color;
}

#ifndef USE_DMA

// Plain version i.e. No DMA
void drawRect3(int row, int col, int height, int width, volatile unsigned short color)
{
	int r, c;
	for(r=0; r<height; r++)
	{
		for(c=0; c<width; c++)
		{
			setPixel3(row+r, col+c, color);
		}
	}
}
#else

// DMA Version
void drawRect3(int row, int col, int height, int width, volatile unsigned short color)
{
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = videoBuffer + OFFSET(r+row, col);
		DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
	}
}
#endif

void setPixel4(int row, int col, unsigned char index)
{
	int whichPixel = OFFSET(row,col);
	int whichShort = whichPixel/2;
	if(col & 1) // Is it odd?
	{
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (index << 8);
	}
	else
	{
		// even column
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | (index);
	}
}

void drawRect4OLD(int row, int col, int height, int width, volatile unsigned char index)
{
	int r, c;
	for(r=0; r<height; r++)
	{
		for(c=0; c<width; c++)
		{
			setPixel4(row+r, col+c, index);
		}
	}
}

// Draw Rectangle using DMA
// This version always rectangles that start on even columns and are an even number 
// of pixels wide
void drawRect4(int row, int col, int height, int width, volatile unsigned char index)
{
	volatile u16 indexindex = (index << 8) | index;
	int r;
	col = col/2*2;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &indexindex;
		DMA[3].dst = videoBuffer + OFFSET(r+row, col)/2;
		DMA[3].cnt = (width/2) | DMA_SOURCE_FIXED | DMA_ON;
		
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 159)
	{
		
	}
	while(SCANLINECOUNTER < 160)
	{

	}
}

void fillScreen3(volatile unsigned short color)
{
	volatile unsigned int colorcolor = color<<16 | color;
	DMA[3].src = &colorcolor;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_SOURCE_FIXED | DMA_32 | DMA_ON;
	
}

void copyPicture4(const unsigned short *buffer)
{
	
	DMA[3].src = buffer;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_16 | DMA_ON;
	
}

void FlipPage()
{
	if(REG_DISPCTL & BUFFER1FLAG) // Is it BUFFER1
	{
		// YES
		REG_DISPCTL = REG_DISPCTL & ~BUFFER1FLAG;
		videoBuffer = BUFFER1;
	}
	else
	{
		// NO
		REG_DISPCTL = REG_DISPCTL | BUFFER1FLAG;
		videoBuffer = BUFFER0;
	}
}
