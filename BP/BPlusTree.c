#include "BPlusTree.h"


BOOL CompareKeys(const void* node1, const void* node2)
{
	const BPlusTreeNode* temp1Node = node1;
	const BPlusTreeNode* temp2Node = node2;

	return temp1Node->Key < temp2Node->Key;
}

BPlusTreeNode* getNewBPlusTreeNode()
{
	BPlusTreeNode* ptr = malloc(sizeof(BPlusTreeNode));

	if (ptr != NULL)
	{
		ptr->Key = -1;
		ptr->Parent = NULL;
		ptr->Data = NULL;
		ptr->CurrentSize = 0;
		ptr->Child = NULL;
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


BOOL addToBPlusTree(BPlusTreeNode** paramRoot, BPlusTreeNode* node, BPlusTreeNode* parent, int size, int height)
{
	if (node == NULL)
		return FALSE;

	BPlusTreeNode* root = *paramRoot;
	


	//Arvore vazia e não tem parent
	//Porque signifa se tiver parent o root é giual ao parent
	if (root == NULL && parent == NULL)
	{

		root = node;

		*paramRoot = root;

		//Alocar o tamanho para os irmãos
		root->Siblings = malloc(sizeof(BPlusTreeNode) * (size - 1));

		if (root->Siblings == NULL)
			return FALSE;

		//O primeiro elemento é o root, inicio do array 
		root->Siblings[0] = node;

		root->CurrentSize = 1;

		return TRUE;
	}
	else if (parent != NULL)
	{
		//Copiar os valores 
		root = getNewBPlusTreeNode();
		root->Parent = parent;
		root->Siblings = malloc(sizeof(BPlusTreeNode) * (size - 1));
		if (root->Siblings == NULL)
			return FALSE;
		root->Siblings[0] = root;
		root->Key = parent->Key;
		root->Data = parent->Data;
		root->CurrentSize = 1;

		*paramRoot = root;
	}

	if (root->Siblings == NULL)
		return FALSE;

	//A arvore não está vazia mas tambem não está cheia , por isso podemos inserir no sitio actual
	//Procurar o local da arvore
	if (root->CurrentSize < size)
	{
		for (int idx = 0; idx < root->CurrentSize; idx++)
		{

			if (root->Siblings[idx]->Key > node->Key)
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
				node->Parent = parent;

				return TRUE;

			}


		}

		//Se chegamos aqui é porque não foi encontrado nenhuma posição no array ja existente 
		//adionamos ao fim
		node->Parent = parent;
		/*
		Warning	C6386	Buffer overrun while writing to 'root->Siblings': 
		the writable size is 'sizeof(BPlusTreeNode)*((size-1))' bytes, but '16' bytes might be written.
		o "if (root->CurrentSize < size )" já garante que nunca passamos o tamanho do array
		*/
#pragma warning( push )
#pragma warning( disable : 6386 )
		root->Siblings[root->CurrentSize] = node;
#pragma warning( pop )
		root->CurrentSize += 1;
		return TRUE;

	}
	//Temos que procurar os nos abaixo e passar o no que é menor que o valor a ser inserido
	//Só adianta continuarmos a verificar se altura da altura for inferior ao size
	//se for igual temos que fazer split da tree
	else if(height < size)
	{
		for (int idx = 0; idx + 1  < size; idx++)
		{
			if (root->Siblings[idx]->Key < node->Key  && node->Key < root->Siblings[idx+1]->Key )
			{
				return addToBPlusTree(&root->Siblings[idx]->Child, node, root->Siblings[idx], size, height+1);
			}
		}
	}

	return FALSE;
}