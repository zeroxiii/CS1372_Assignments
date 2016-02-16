///////////////////////////////////////////////////////////////////////
// Name: Rahmaan Lodhia                                              //
// Prism Account: rlodhia3                                           //
// Collaboration:                                                    //
// "I worked on the homework assignment alone, using only            //
// course materials."                                                //
///////////////////////////////////////////////////////////////////////

int main() 
{
	// Setup for Mode 3 using Background 2 //

	*(unsigned short *)0x4000000 = 1027; /*Black Screen*/
	
	//Light Up Pixels//

	*((unsigned short *)0x6000000 + (240*25 + 20)) = 31; /*Red*/
	*((unsigned short *)0x6000000 + (240*47 + 60)) = 1023; /*Yellow*/
	*((unsigned short *)0x6000000 + (240*69 + 100)) = 992; /*Green*/
	*((unsigned short *)0x6000000 + (240*80 + 120)) = 32767; /*White*/
	*((unsigned short *)0x6000000 + (240*81 + 140)) = 32736; /*Cyan*/
	*((unsigned short *)0x6000000 + (240*113 + 180)) = 31744; /*Blue*/
	*((unsigned short *)0x6000000 + (240*135 + 220)) = 31775; /*Magenta*/
	
	while(1)
	{
	}
	return 0;
}