#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "linkedList.h"
#include "mylib.h"


typedef struct BPlusTreeNodeContent_st {
	uint32_t Key;/*Key, alterei para pointer pare referencia em todoas o nos*/
	void* Data;/*Pointer to data*/
	struct BPlusTreeNode_st* Child;/* type of BPlusTreeNode, but wast */
}BPlusTreeNodeContent;

typedef struct BPlusTreeNode_st {

	BPlusTreeNodeContent** Contents;
	struct BPlusTreeNode_st* Parent; /*Parent node*/
	int CurrentSize;
}BPlusTreeNode;





typedef struct BPlusTree_st {
	BPlusTreeNode *root;
	int size;
}BPlusTree;
BPlusTreeNodeContent* getNewBPlusTreeNodeContent();
BPlusTreeNodeContent** getNewBPlusTreeArray(int size);
BPlusTreeNode* getNewBPlusTreeNode();
BPlusTree* getNewBPlusTree(int size);
BPlusTreeNodeContent* getNewBPlusTreeSetContent(void* data, uint32_t key);
BOOL isleafNode(BPlusTreeNode *root);
BPlusTreeNode* getNode(BPlusTreeNode *root, uint32_t key);

BOOL addNewChild(BPlusTree* paramRoot, BPlusTreeNode* root, BPlusTreeNode* node);
BPlusTreeNode* Split(BPlusTree* paramRoot, BPlusTreeNode* root);
BOOL addToNode(BPlusTree* paramRoot, BPlusTreeNode* root, void* data, uint32_t key);
BOOL addToBPlusTree(BPlusTree* paramRoot, void* data, uint32_t key);

