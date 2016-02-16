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

void main()
{
	//Test Variables
	int year, leap, num, num2, month, day, bitCount;
	month = 2;
	num = 22;
	num2 = 37;
	year = 2004;
	day = daysInMonth(month, year);
	bitCount = countOnes(num);
	leap = isLeap(year);

	//Testing countOnes
	printf("The number of bits in %u is %d\n", num, bitCount);

	//Testing isEven
	if (isEven(num))
	{
		printf("%d is an even number\n", num);
	}
	else
	{
		printf("%d is not an even number\n", num);
	}

	//Testing isOdd
	if (isOdd(num2))
	{
		printf("%d is an odd number\n", num2);
	}
	else
	{
		printf("%d is not an odd number\n", num2);
	}

	//Testing isLeap
	if (leap == 1)
	{
		printf("The year %d is a leap year\n",year);
	}
	else
	{
		printf("The year %d is not a leap year\n",year);
	}

	//Testing daysInMonth
	printf("Febuary has %d days in the year %d\n",day, year);
	
	//Testing packChars
	printf("Packing %d and %d together forms 0x%x\n", 3, 5, packChars(3,5));

	getchar();
}