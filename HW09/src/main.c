///////////////////////////////////////////////////////////////////////
// Name: Rahmaan Lodhia//
// Prism Account: rlodhia3//
// Collaboration: //
//"I worked on the homework assignment alone, using only //
// course materials." //
///////////////////////////////////////////////////////////////////////

#include "textEntry.h"

//Inventory Index
int itemIndex = 0;

//Prototypes
void drawInventoryMenu();
void showInventory(BSTNODE *current);

int main(void)
{

	//Initialization
	BSTNODE *root = NULL; //Initialize Tree
	char buffer[0][CHARACTERLIMIT]; //Initialize Array of Strings
	setRegister();
	setupInterrupts();
	initializeTiles();
	int i;
	
	while(1)
	{
		//Set up Menu
		drawInventoryMenu();
		if(KEY_DOWN_NOW(BUTTON_A))
		{
			//Clear current buffer
			for(i = 0; i < CHARACTERLIMIT; i++)
				buffer[itemIndex][i] = '\0';
			//Recieve input
			getText(buffer[itemIndex]);
			//Place input into tree
			add(&root, buffer[itemIndex]);
			//Move to next item
			itemIndex += 1;
		}
		if(KEY_DOWN_NOW(BUTTON_B))
		{
			//Display Inventory
			showInventory(root);
		}
		if(KEY_DOWN_NOW(BUTTON_L))
		{
			//Delete Inventory
			freetree(&root);
			itemIndex = 0;
		}
		waitForVblank();
	}
	return 0;
}

void drawInventoryMenu() //Draw Menu
{
	putText(2,0,"Press A to Add an Item");
	putText(5,0,"Press B to View Inventory");
	putText(8,0,"Press L to Clear Inventory");
}

void showInventory(BSTNODE *current) //Display Inventory
{
	clearScreen();
	inorder(current);
	putText(0,17,"Press Start");
	putText(1,17,"To Return");
	putText(2,17,"To Menu");
	resetIndex();
	while(!KEY_DOWN_NOW(BUTTON_START)){}
	clearScreen();
}
