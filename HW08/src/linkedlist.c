#include "linkedlist.h"

//Add element to Front of list
LLNODE *addToFront(LLNODE *current, void *newdata)
{
	LLNODE *temp;
	temp = malloc(sizeof(LLNODE));
	if(temp == NULL)
	{
		printf("Malloc failure\n");
		exit(77);
	}
	temp->data = newdata;
	temp->next = current;
	return temp;
}

//Traverse through elements doing function recursively
void traverse(LLNODE *current, void (*doit) (void *))
{
	if(current != NULL)
	{
		doit(current->data);
		traverse(current->next, doit);
	}
}

//Traverse through Elements iteratively
void traverseI(LLNODE *current, void (*doit) (void *))
{
	while(current != NULL)
	{
		doit(current->data);
		current = current->next;
	}
}

//Free List recursively
void freelist(LLNODE *current)
{
	if(current != NULL)
	{
		freelist(current->next);
		free(current->data);
		free(current);
		
	}
}

//Free List Iteratively
void freelistI(LLNODE *current)
{
	LLNODE *temp;
	while(current != NULL)
	{
		temp = current->next;
		free(current->data);
		free(current);
		current = temp;
	}
}

//Get head pointer
void *getHead(LLNODE *current)
{
	if(current == NULL)
	{
		return NULL;
	}
	else
	{
		return current->data;
	}
}

//Delete First Element
LLNODE *deleteFirst(LLNODE *current)
{	
	LLNODE *temp = current;
	current = current->next;
	free(temp->data);
	free(temp);
	return current;
}

//Delete Specified Element with data number num
void deleteElement(LLNODE *head, int num)
{
	int found = 0;
	LLNODE *probe = head;
	LLNODE *prev = head;
	LLNODE *temp;
	//Check if head case
	if((((Sprite *)(head->data))->number) == num)
	{
		head = deleteFirst(head);
	}
	else
	{
		//Search through list for element
		while(probe != NULL && !found)
		{
			probe = probe->next;
			if((((Sprite *)(probe->data))->number) == num)
			{
				prev->next = probe->next;
				free(probe->data);
				free(probe);
				found = 1;
			}
			else
			{
				prev = probe;
			}
		}
	}
}


