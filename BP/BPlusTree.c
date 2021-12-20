#include "BPlusTree.h"

BPlusTreeNode* getNewBPlusTreeNode()
{
	BPlusTreeNode* ptr = malloc(sizeof(BPlusTreeNode));

	if (ptr != NULL)
	{
		ptr->childrens = NULL;
		ptr->key = -1;
		ptr->parent = NULL;
		ptr->data = NULL;
	}

	return ptr;
}


BOOL addToBPlusTree(BPlusTreeNode* node)
{
	return FALSE;
}