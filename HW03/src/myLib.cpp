/*-------------------------------------------------------------------
* Library for general GBA programming
*-----------------------------------------------------------------*/
#include "myLib.h"

unsigned short *videoBuffer = VIDBUFADR;

void setPixel3(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row,col)] = color;
}


void drawRect3(int row, int col, int height, int width, unsigned short color)
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

void waitForVblank()
{
	while(SCANLINECOUNTER > 160)
	{
	}
	while(SCANLINECOUNTER < 160)
	{
	}
}