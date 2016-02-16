// Binary Tree Header //

//Tree Node
typedef struct bstnode
{
	char *data;
	struct bstnode *left;
	struct bstnode *right;

} BSTNODE;

//Prototypes
void add(BSTNODE **ppcurrent, char *newdata);
void inorder(BSTNODE *current);
void freetree(BSTNODE **current);
void indexReset();

#define FOUND 1
#define NOTFOUND 0
