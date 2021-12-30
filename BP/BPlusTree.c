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
	/*Se não tiver filho significa que chegamos ao ultimos no onde adicionmos os nos*/
	if (isleafNode(root))
		return root;

	//Procurar o no 
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

	//Se não encontramos significa que o key é maior que ultimo no, por isso mandamos o ultimo nó
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

		//Se chegamos aqui é porque não foi encontrado nenhuma posição no array ja existente 
		//adionamos ao fim
		/*
		Warning	C6386	Buffer overrun while writing to 'root->Siblings':
		the writable size is 'sizeof(BPlusTreeNode)*((size-1))' bytes, but '16' bytes might be written.
		o "if (root->CurrentSize < size )" já garante que nunca passamos o tamanho do array
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
		if (Split(paramRoot, root) != NULL)
			return TRUE;
	}

	return FALSE;
}

BPlusTreeNode* Split(BPlusTree* paramRoot, BPlusTreeNode* root)
{
	/*Meio do array*/
	int index = (int)(paramRoot->size / 2) + 1;

	BOOL isParentRootNull = root->Parent == NULL;

	/*Se o pai do root for NULL ciramos um novo*/
	BPlusTreeNode* newParent = isParentRootNull ? getNewBPlusTreeNode() : root->Parent;

	if (isParentRootNull)
	{
		newParent->Contents = getNewBPlusTreeArray(paramRoot->size);
	}

	/* Criar um novo nó com o segundo meio da lista*/
	BPlusTreeNode* child2 = getNewBPlusTreeNode();

	if (child2 == NULL)
		return NULL;

	child2->Contents = getNewBPlusTreeArray(paramRoot->size);

	if (child2->Contents == NULL)
		return NULL;

	/*Copiar os no para o novo no*/
	for (int idx = 0; idx + index < paramRoot->size; idx++)
	{
		child2->Contents[idx] = root->Contents[index + idx];
		root->Contents[index + idx] = NULL;
		child2->CurrentSize++;
	}

	/*O tamanho passa a ser o tamanho atual menos o tamnho do novo nó*/
	root->CurrentSize -= child2->CurrentSize;

	/*Só adicionamos o root ao novo pai se o pai for null, porque se não for null significa que já está no pai*/
	if (isParentRootNull)
	{
		if (!addNewChild(paramRoot, newParent, root))
			return FALSE;
	}

	if (!addNewChild(paramRoot, newParent, child2))
		return FALSE;

	/*Se o parent era NULL signifa que era o root principal, por isso o  novo pai passa o root principal*/
	if (isParentRootNull)
	{
		paramRoot->root = newParent;
	}

	return newParent;
}

BOOL addToNode(BPlusTree* paramRoot, BPlusTreeNode* root, void* data, uint32_t key)
{
	/**/
	if (root->CurrentSize < paramRoot->size)
	{
		for (int idx = 0; idx < root->CurrentSize; idx++)
		{
			if (root->Contents[idx]->Key > key)
			{
				/*Mover os no para a frente*/
				for (int idx2 = (root->CurrentSize - 1); idx2 >= idx; idx2--)
				{
					root->Contents[idx2 + 1] = root->Contents[idx2];
				}

				root->Contents[idx] = getNewBPlusTreeSetContent(data, key);

				root->CurrentSize += 1;

				return TRUE;
			}
		}

		/*Se chegamos aqui é porque não foi encontrado nenhuma posição no array ja existente
		* adionamos ao fim
		*/


		/*
		Warning	C6386	Buffer overrun while writing to 'root->Siblings':
		the writable size is 'sizeof(BPlusTreeNode)*((size-1))' bytes, but '16' bytes might be written.
		o "if (root->CurrentSize < size )" já garante que nunca passamos o tamanho do array
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

	//Arvore vazia e não tem parent
	//Porque signifa se tiver parent o root é giual ao parent
	if (paramRoot->root == NULL)
	{

		paramRoot->root = getNewBPlusTreeNode();


		//Alocar o tamanho para os irmãos
		paramRoot->root->Contents = getNewBPlusTreeArray(paramRoot->size - 1);

		if (paramRoot->root->Contents == NULL)
			return FALSE;

		//O primeiro elemento é o root, inicio do array 
		paramRoot->root->Contents[0] = getNewBPlusTreeSetContent(data, key);

		paramRoot->root->Parent = NULL;

		paramRoot->root->CurrentSize = 1;

		return TRUE;
	}


	BPlusTreeNode* aux = getNode(paramRoot->root, key);

	if (aux == NULL)
		return FALSE;

	return  addToNode(paramRoot, aux, data, key);
}