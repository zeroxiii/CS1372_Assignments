///////////////////////////////////////////////////////////////////////
// Name: Rahmaan Lodhia                                              //
// Prism Account: rlodhia3                                           //
// Collaboration:                                                    //
// "I worked on the homework assignment alone, using only            //
// course materials."                                                //
///////////////////////////////////////////////////////////////////////


#include "hw2Lib.h"
#include <stdio.h>
#include <stdlib.h>

int countOnes(unsigned num)
{
	int count;
	for (count = 0; num != 0; num >>= 1)
	{
		if (num & 01)
		{
			count++;
		}
	}
	return count;
}

int isLeap(int year)
{
	if ((year % 4) == 0)
		{	
		if ((year % 100) != 0) 
			return 1;
		}	
	else if ((year % 100) == 0)
	{
		if ((year % 400) == 0)
			return 1;
		else
			return 0;
	}
	return 0;
}

int daysInMonth(int month, int year)
{
	switch(month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 2:
		if (isLeap(year))
		{
			return 29;
		}
		return 28;
	case 4: case 6: case 9: case 11:
		return 30;
	default:
		return 0;
	}

}

unsigned short packChars(unsigned char n0, unsigned char n1)
{
	return((n0<<8)|(n1));
}