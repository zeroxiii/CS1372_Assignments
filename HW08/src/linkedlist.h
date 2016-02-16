#include <stdlib.h>

//Structures
typedef struct llnode
{
	void *data;
	struct llnode *next;

} LLNODE;

typedef struct {
	int number;
    int row;
    int col;
    int start;
    int shape;
    int size;
    int height;
    int width;
    int rdel;
    int cdel;
} Sprite;

//Prototype
LLNODE *addToFront(LLNODE *current, void *newdata);
void traverse(LLNODE *current, void (*doit) (void *));
void traverseI(LLNODE *current, void (*doit) (void *));
void freelist(LLNODE *current);
void freelistI(LLNODE *current);
void *getHead(LLNODE *current);
LLNODE *deleteFirst(LLNODE *current);
void deleteElement(LLNODE *head, int num);



