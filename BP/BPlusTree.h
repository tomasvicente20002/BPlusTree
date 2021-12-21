#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "linkedList.h"
#include "mylib.h"


typedef struct BPlusTreeNode_st {
	uint32_t key;/*Key*/
	void* data;/*Pointer to data*/
	struct BPlusTreeNode_st* parent; /*Parent node*/
	LinkedList* childrens;/*Chieldes nodes, contais all the bpp chieldres*/
}BPlusTreeNode;


typedef struct BPlusTree_st {
	BPlusTreeNode *root;
	int size;
}BPlusTree;

BPlusTreeNode* getNewBPlusTreeNode();
BPlusTree* getNewBPlusTree(int size);

BOOL addToBPlusTree(BPlusTree* root, BPlusTreeNode* node);
