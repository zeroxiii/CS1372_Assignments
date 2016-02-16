/*-------------------------------------------------------------------
* text.h -- Header File for Text Functions
*------------------------------------------------------------------*/

#ifndef _TEXT_H_
#define _TEXT_H_

extern const unsigned char fontdata_6x8[12288];
void drawChar3(int row, int col, unsigned char ch, unsigned short color);
void drawString3(int row, int col, unsigned char *string, unsigned short color);
void drawString4(int row, int col, unsigned char *string, unsigned char index);
void drawChar4(int row, int col, unsigned char ch, unsigned char index);
#endif

