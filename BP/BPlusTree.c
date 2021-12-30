#include "BPlusTree.h"


BPlusTreeNodeContent* getNewBPlusTreeNodeContent()
{
	BPlusTreeNodeContent* ptr = malloc(sizeof(BPlusTreeNodeContent));

	if (ptr != NULL)
	{
		ptr->Child = NULL;
		ptr->Data = NULL;
		ptr->Key = -1;
	}

	return ptr;
}

BPlusTreeNodeContent** getNewBPlusTreeArray(int size)
{
	return  malloc(sizeof(BPlusTreeNodeContent) * size);
}

BPlusTreeNodeContent* getNewBPlusTreeSetContent(void* data, uint32_t key)
{
	BPlusTreeNodeContent* ptr = getNewBPlusTreeNodeContent();
	if (ptr != NULL)
	{
		ptr->Data = data;
		ptr->Key = key;
	}
	return ptr;
}

BPlusTreeNode* getNewBPlusTreeNode()
{
	BPlusTreeNode* ptr = malloc(sizeof(BPlusTreeNode));

	if (ptr != NULL)
	{
		ptr->Parent = NULL;
		ptr->CurrentSize = 0;
		ptr->Contents = NULL;
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

	return ptr;
}

BOOL isleafNode(BPlusTreeNode* root)
{
	for (int idx = 0; idx < root->CurrentSize; idx++)
		if (root->Contents[idx]->Child != NULL)
			return FALSE;

	return TRUE;
}

BPlusTreeNode* getNode(BPlusTreeNode* root, uint32_t key)
{
	if (isleafNode(root))
		return root;

	for (int idx = 0; idx < root->CurrentSize; idx++)
	{
		if (root->Contents[idx]->Key > key)
		{
			if (idx == 0)
				return getNode(root->Contents[0]->Child, key);
			else
			{
				return getNode(root->Contents[idx - 1]->Child, key);
			}
		}
	}

	return getNode(root->Contents[root->CurrentSize - 1]->Child, key);
}


BOOL addNewChild(BPlusTree* paramRoot, BPlusTreeNode* root, BPlusTreeNode* node)
{

	if (root->CurrentSize < paramRoot->size)
	{
		for (int idx = 0; idx < root->CurrentSize; idx++)
		{
			if (root->Contents[idx]->Key > node->Contents[0]->Key)
			{
				//Mover os no para a frente
				for (int idx2 = (root->CurrentSize - 1); idx2 >= idx; idx2--)
				{
					root->Contents[idx2 + 1] = root->Contents[idx2];
				}

				root->Contents[idx] = getNewBPlusTreeSetContent(NULL, node->Contents[0]->Key);

				root->Contents[idx]->Child = node;
				root->CurrentSize += 1;

				node->Parent = root;

				return TRUE;
			}
		}

		//Se chegamos aqui � porque n�o foi encontrado nenhuma posi��o no array ja existente 
		//adionamos ao fim
		/*
		Warning	C6386	Buffer overrun while writing to 'root->Siblings':
		the writable size is 'sizeof(BPlusTreeNode)*((size-1))' bytes, but '16' bytes might be written.
		o "if (root->CurrentSize < size )" j� garante que nunca passamos o tamanho do array
		*/
#pragma warning( push )
#pragma warning( disable : 6386 )
		root->Contents[root->CurrentSize] = getNewBPlusTreeSetContent(NULL, node->Contents[0]->Key);
		root->Contents[root->CurrentSize]->Child = node;
#pragma warning( pop )
		root->CurrentSize += 1;
		node->Parent = root;
		return TRUE;

	}
	else
	{
		Split(paramRoot, root);
	}

	return FALSE;
}

BPlusTreeNode* Split(BPlusTree* paramRoot, BPlusTreeNode* root)
{
	int index = (int)(paramRoot->size / 2) + 1;

	BOOL isParentRootNull = root->Parent == NULL;

	BPlusTreeNode* newParent = isParentRootNull ? getNewBPlusTreeNode() : root->Parent;

	if (isParentRootNull)
	{
		newParent->Contents = getNewBPlusTreeArray(paramRoot->size);	
	}

	BPlusTreeNode* child2 = getNewBPlusTreeNode();

	if (child2 == NULL)
		return NULL;

	child2->Contents = getNewBPlusTreeArray(paramRoot->size);

	if (child2->Contents == NULL)
		return NULL;


	for (int idx = 0; idx + index < paramRoot->size; idx++)
	{
		child2->Contents[idx] = root->Contents[index + idx];
		root->Contents[index + idx] = NULL;
		child2->CurrentSize++;
	}
	root->CurrentSize -= child2->CurrentSize;

	
	if (isParentRootNull)
	{
		addNewChild(paramRoot, newParent, root);
	}

	addNewChild(paramRoot, newParent, child2);

	if (isParentRootNull)
	{
		paramRoot->root = newParent;
	}

	return newParent;
}

BOOL addToNode(BPlusTree* paramRoot, BPlusTreeNode* root, void* data, uint32_t key)
{
	if (root->CurrentSize < paramRoot->size)
	{
		for (int idx = 0; idx < root->CurrentSize; idx++)
		{
			if (root->Contents[idx]->Key > key)
			{
				//Mover os no para a frente
				for (int idx2 = (root->CurrentSize - 1); idx2 >= idx; idx2--)
				{
					root->Contents[idx2 + 1] = root->Contents[idx2];
				}

				root->Contents[idx] = getNewBPlusTreeSetContent(data, key);

				root->CurrentSize += 1;

				return TRUE;
			}
		}

		//Se chegamos aqui � porque n�o foi encontrado nenhuma posi��o no array ja existente 
		//adionamos ao fim
		/*
		Warning	C6386	Buffer overrun while writing to 'root->Siblings':
		the writable size is 'sizeof(BPlusTreeNode)*((size-1))' bytes, but '16' bytes might be written.
		o "if (root->CurrentSize < size )" j� garante que nunca passamos o tamanho do array
		*/
#pragma warning( push )
#pragma warning( disable : 6386 )
		root->Contents[root->CurrentSize] = getNewBPlusTreeSetContent(data, key);
#pragma warning( pop )
		root->CurrentSize += 1;
		return TRUE;

	}
	else
	{

		if (Split(paramRoot, root) != NULL)
		{
			BPlusTreeNode* aux = getNode(paramRoot->root, key);

			return addToNode(paramRoot, aux, data, key);
		}
	}
	 
	return FALSE;
}

BOOL addToBPlusTree(BPlusTree* paramRoot, void* data, uint32_t key)
{
	if (data == NULL || paramRoot == NULL)
		return FALSE;

	//Arvore vazia e n�o tem parent
	//Porque signifa se tiver parent o root � giual ao parent
	if (paramRoot->root == NULL)
	{

		paramRoot->root = getNewBPlusTreeNode();


		//Alocar o tamanho para os irm�os
		paramRoot->root->Contents = getNewBPlusTreeArray(paramRoot->size - 1);

		if (paramRoot->root->Contents == NULL)
			return FALSE;

		//O primeiro elemento � o root, inicio do array 
		paramRoot->root->Contents[0] = getNewBPlusTreeSetContent(data, key);

		paramRoot->root->Parent = NULL;

		paramRoot->root->CurrentSize = 1;

		return TRUE;
	}

	//A arvore n�o est� vazia mas tambem n�o est� cheia , por isso podemos inserir no sitio actual
	//Procurar o local da arvore

	//Temos que procurar os nos abaixo e passar o no que � menor que o valor a ser inserido
	//S� adianta continuarmos a verificar se altura da altura for inferior ao size
	//se for igual temos que fazer split da tree

	BPlusTreeNode* aux = getNode(paramRoot->root, key);

	addToNode(paramRoot, aux, data, key);


	return FALSE;
}