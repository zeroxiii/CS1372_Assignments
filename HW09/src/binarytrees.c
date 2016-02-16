//Binary Tree Library //

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binarytrees.h"

int index = 0;

//Add element to right position after comparison 
void add(BSTNODE **ppcurrent, char *newdata)
{
	if(*ppcurrent == NULL)
	{
		*ppcurrent = malloc(sizeof(BSTNODE));
		if(*ppcurrent == NULL) exit(10);
		(*ppcurrent)->data = newdata;
		(*ppcurrent)->left = NULL;
		(*ppcurrent)->right = NULL;
	}
	else if(strcmp(newdata,((*ppcurrent)->data)) < 0) 
	{
		add(&((*ppcurrent)->left), newdata);
	} else {
		add(&((*ppcurrent)->right), newdata);
	}
	
}

//Print Items in Alphabetical order
void inorder(BSTNODE *current)
{
	if(current != NULL)
	{	
	
		inorder(current->left);	
		putText(index,0, current->data);
		index += 1;
		inorder(current->right);
	}
}

//Reset print index
void resetIndex()
{
	index = 0;
}

//Free tree
void freetree(BSTNODE **current)
{
	if(*current != NULL)
	{
		freetree(&((*current)->left));
		freetree(&((*current)->right));
		free(*current);
		*current = NULL;
	}
}

