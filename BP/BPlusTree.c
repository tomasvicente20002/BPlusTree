#include "BPlusTree.h"


BOOL CompareKeys(const void* node1, const void* node2)
{
	const BPlusTreeNode* temp1Node = node1;
	const BPlusTreeNode* temp2Node = node2;

	return temp1Node->key < temp2Node->key;
}

BPlusTreeNode* getNewBPlusTreeNode()
{
	BPlusTreeNode* ptr = malloc(sizeof(BPlusTreeNode));

	if (ptr != NULL)
	{
		ptr->key = -1;
		ptr->parent = NULL;
		ptr->data = NULL;
		ptr->CurrentSize = 0;
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
		//ptr->root = getNewBPlusTreeNode();
	}


	return ptr;
}


BOOL addToBPlusTree(BPlusTreeNode** paramRoot, BPlusTreeNode* node, int size)
{
	BPlusTreeNode* root = *paramRoot;

	//Arvore vazia
	if (root == NULL)
	{

		root = node;

		*paramRoot = root;

		//Alocar o tamanho para os irmãos
		root->Siblings = malloc(sizeof(BPlusTreeNode) * size);

		if (root->Siblings == NULL)
			return FALSE;

		//O primeiro elemento é o root, inicio do array 
		root->Siblings[0] = node;


		root->CurrentSize = 1;

		return TRUE;
	}

	//A arvore não está vazia
	//Procurar o local da arvore
	if (root->CurrentSize < size)
	{
		for (int idx = 0; idx < root->CurrentSize; idx++)
		{

			if (root->Siblings[idx]->key > node->key)
			{
				//Mover os no para a frente
				for (int idx2 = (root->CurrentSize - 1); idx2 >= idx; idx2--)
				{
					root->Siblings[idx2 + 1] = root->Siblings[idx2];
				}

				
				root->Siblings[idx] = node;

				//Significa que é o primeiro da ordenação logo o root passa a ser o novo nó
				//temos que copiar os valores do root e apagar o valores , porque vão para o novo root
				if (idx == 0)
				{
					node->Siblings = root->Siblings;
					node->CurrentSize = root->CurrentSize;
					

					root->Siblings = NULL;
					root->CurrentSize = 0;

					*paramRoot = node;
					root = *paramRoot;
				}

				root->CurrentSize += 1;

				return TRUE;

			}

			//Se chegamos aqui é porque não foi encontrado nenhuma posição no array ja existente 
			//adionamos ao fim
			root->Siblings[root->CurrentSize] = node;
			return TRUE;
		}


	}


	return FALSE;
}