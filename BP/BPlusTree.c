#include "BPlusTree.h"


BOOL CompareKeys(const void*node1, const void*node2)
{
	BPlusTreeNode *temp1Node = node1;
	BPlusTreeNode *temp2Node = node2;

	return temp1Node->key < temp2Node->key;
}

BPlusTreeNode* getNewBPlusTreeNode()
{
	BPlusTreeNode* ptr = malloc(sizeof(BPlusTreeNode));

	if (ptr != NULL)
	{
		ptr->childrens = NULL;
		ptr->key = 0;
		ptr->parent = NULL;
		ptr->data = NULL;
	}

	return ptr;
}

BPlusTree* getNewBPlusTree(int size)
{
	BPlusTree* ptr = malloc(sizeof(BPlusTree));

	if (ptr != NULL)
	{
		ptr->size = size;
		ptr->root = NULL; 
	}
}


BOOL addToBPlusTree(BPlusTree* root,BPlusTreeNode* node)
{

	//If tree is empty
	if (root->root == NULL)
	{
		root->root = node;

		return TRUE;
	}

	if (root->root->childrens == NULL)
		root->root->childrens = GetNewLinkedList();

	if (root->root->childrens == NULL)
		return FALSE;

	if (root->root->childrens->Count < root->size)
	{
		AddOrderlyToLinkedList(root->root->childrens, node, CompareKeys);
		return TRUE;
	}

}