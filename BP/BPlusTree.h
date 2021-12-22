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
	/*
	|	|	|	|
	|1	|2	|3	|
	|	|	|	|
	*/
	/*se n„ı for nullo signifca que È o inicio do ramo, por exemplo o 1*/
	struct BPlusTreeNode_st** Siblings;/* nodes next to current */
	struct BPlusTreeNode_st* Child;/*Chieldes nodes, contais all the bpp chieldres*/
	int CurrentSize;
}BPlusTreeNode;


typedef struct BPlusTree_st {
	BPlusTreeNode *root;
	int size;
}BPlusTree;

BPlusTreeNode* getNewBPlusTreeNode();
BPlusTree* getNewBPlusTree(int size);
BOOL addToBPlusTree(BPlusTreeNode** paramRoot, BPlusTreeNode* node, int size);
