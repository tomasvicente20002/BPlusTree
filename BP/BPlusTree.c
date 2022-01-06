#include "BPlusTree.h"

/// <summary>
/// Cria e inicializa uma struct do tipo BPlusTreeNodeContent
/// </summary>
/// <returns>Sruct</returns>
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

/// <summary>
/// Criar um array do tipo BPlusTreeNodeContent
/// </summary>
/// <param name="size"></param>
/// <returns>Sruct</returns>
BPlusTreeNodeContent** getNewBPlusTreeArray(int size)
{
	return  malloc(sizeof(BPlusTreeNodeContent) * size);
}

/// <summary>
/// Criar , incializa e define os campos data e key de uma BPlusTreeNodeContent
/// </summary>
/// <param name="data"></param>
/// <param name="key"></param>
/// <returns>Sruct</returns>
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

/// <summary>
/// Cria e incializa uma struct BPlusTreeNode
/// </summary>
/// <returns>Sruct</returns>
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

/// <summary>
/// Cria e incializa uma struct do tipo BPlusTree
/// </summary>
/// <param name="size"></param>
/// <returns>Sruct</returns>
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

/// <summary>
/// Verifica se é um leaf node, no no ultimo nivel
/// </summary>
/// <param name="root"></param>
/// <returns>TRUE se o no é leaf, caso contrário FALSE</returns>
BOOL isleafNode(const BPlusTreeNode *root)
{
	for (int idx = 0; idx < root->CurrentSize; idx++)
		if (root->Contents[idx]->Child != NULL)
			return FALSE;

	return TRUE;
}

/// <summary>
/// ontem a chave menor da arvore
/// </summary>
/// <param name="root">no</param>
/// <returns>Chave menor da arvore</returns>
int getMinKey(const BPlusTreeNode* root)
{
	if (isleafNode(root))
		return root->Contents[0]->Key;

	return getMinKey(root->Contents[0]->Child);
}

/// <summary>
/// Imprimes os nos da arvore
/// </summary>
/// <param name="root">no atual</param>
/// <param name="n">quantidade de nos a ser imprimidos, se for menor que 0 imprime todos</param>
/// <param name="imprimidos">quantidade de nos imprimidos</param>
/// <returns>TRUE se já imprimiu todos os nós até n</returns>
BOOL PrintNodes(const BPlusTreeNode *root, int n, int *imprimidos)
{	
	/*Imprimir apenas o nos do ultimo nivel*/
	if (isleafNode(root))
	{
		for (int idx = 0; idx < root->CurrentSize; idx++)
		{
			(*imprimidos)++;
			int key = root->Contents[idx]->Key;

			printf("%5d|	",key);

			if (n > 0 && *imprimidos == n)
				return TRUE;
		}

		printf("\b\b\n");

		return FALSE;
	}


	for (int idx = 0; idx < root->CurrentSize; idx++)
		if (PrintNodes(root->Contents[idx]->Child, n, imprimidos))
			return TRUE;

	return FALSE;
}

/// <summary>
/// Obtem o leaf node onde devera se inserido o registo
/// </summary>
/// <param name="root">no</param>
/// <param name="key">chave a inserir</param>
/// <param name="parent">pai do root</param>
/// <returns>Nó a inserir o registo</returns>
BPlusTreeNode* getNode(BPlusTreeNode* root, uint32_t key, BPlusTreeNode* parent)
{
	root->Parent = parent;
	/*Se não tiver filho significa que chegamos ao ultimos no onde adicionmos os nos*/
	if (isleafNode(root))
		return root;

	//Procurar o no 
	for (int idx = 0; idx < root->CurrentSize; idx++)
	{
		if (root->Contents[idx]->Key > key)
		{
			if (idx == 0)
				return getNode(root->Contents[0]->Child, key,root);
			else
			{
				return getNode(root->Contents[idx - 1]->Child, key, root);
			}
		}
	}

	//Se não encontramos significa que o key é maior que ultimo no, por isso mandamos o ultimo nó
	return getNode(root->Contents[root->CurrentSize - 1]->Child, key, root);
}

/// <summary>
/// Verifica se uma key já existe na arvore
/// </summary>
/// <param name="root">no</param>
/// <param name="key">key a verificar</param>
/// <returns>TRUE se a key já existe no registo , caso contrário FALSE</returns>
BOOL KeyExist(BPlusTreeNode* root, uint32_t key)
{

	if (isleafNode(root))
	{
		for (int i = 0; i < root->CurrentSize; i++)
		{
			if (root->Contents[i]->Key == key)
				return TRUE;
		}
		/*Chegamos ao ultimos nivel e não encotramos nada*/
		return FALSE;
	}


	for (int idx = 0; idx < root->CurrentSize; idx++)
	{
		if (root->Contents[idx]->Key == key)
			return TRUE;

		if (root->Contents[idx]->Key > key)
		{
			if (idx == 0)
				return KeyExist(root->Contents[0]->Child, key);
			else
			{
				return KeyExist(root->Contents[idx - 1]->Child, key);
			}
		}
	}

	//Se não encontramos significa que o key é maior que ultimo no, por isso mandamos o ultimo nó
	return KeyExist(root->Contents[root->CurrentSize - 1]->Child, key);
}

/// <summary>
/// Actualiza o primeiro elemento de todos parent nodes
/// </summary>
/// <param name="root">no a actulizar</param>
/// <param name="key">nova chave</param>
void UpdateRootKey(BPlusTreeNode* root, int key)
{
	if (root == NULL)
		return; 

	root->Contents[0]->Key = key;

	UpdateRootKey(root->Parent,key);
}

/// <summary>
/// Adiciona um novo filho a arvore
/// </summary>
/// <param name="paramRoot">arvore</param>
/// <param name="root">no a inserir o registo</param>
/// <param name="node">no a inserir</param>
/// <returns></returns>
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
					if (idx2 + 1 == root->CurrentSize)
					{
						root->Contents[idx2 + 1] = NULL;
						root->Contents[idx2 + 1] = getNewBPlusTreeNodeContent();
					}
					SwapContent(root->Contents[idx2 + 1], root->Contents[idx2]);
				}

				node->Parent = root;
				root->Contents[idx] = getNewBPlusTreeSetContent(NULL, node->Contents[0]->Key);	
				root->Contents[idx]->Child = node;
				root->CurrentSize += 1;
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
		node->Parent = root;
		root->Contents[root->CurrentSize] = getNewBPlusTreeSetContent(NULL, node->Contents[0]->Key);
		root->Contents[root->CurrentSize]->Child = node;
#pragma warning( pop )
		root->CurrentSize += 1;
		return TRUE;

	}
	else
	{
		//TODO: rever
		if (Split(paramRoot, root) != NULL)
		{
			if(root->Contents[root->CurrentSize-1]->Key > node->Contents[0]->Key)
				addNewChild(paramRoot, root, node);
			else
				addNewChild(paramRoot, root->Parent->Contents[1]->Child, node);
			return TRUE;
		}
	}

	return FALSE;
}

/// <summary>
/// Divide um no em dois
/// </summary>
/// <param name="paramRoot">tree</param>
/// <param name="root">no a ser dividido</param>
/// <returns></returns>
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
	for (int idx = 0; idx + index < root->CurrentSize; idx++)
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

/// <summary>
/// Traca o conteudo de dois BPlusTreeNodeContent
/// </summary>
/// <param name="node1"></param>
/// <param name="node2"></param>
void SwapContent(BPlusTreeNodeContent *node1, BPlusTreeNodeContent *node2)
{
	BPlusTreeNodeContent aux = *node1;

	node1->Child = node2->Child;
	node1->Data = node2->Data;
	node1->Key = node2->Key;


	node2->Child = aux.Child;
	node2->Data = aux.Data;
	node2->Key = aux.Key;
}

/// <summary>
/// Adiciona um novo registo a arvore
/// </summary>
/// <param name="paramRoot">tree inde se vai inserir o registo</param>
/// <param name="root">no a inserir o registo</param>
/// <param name="data">conteudo do registo</param>
/// <param name="key">key do registo</param>
/// <returns></returns>
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
					if (idx2 + 1 == root->CurrentSize)
					{
						root->Contents[idx2 + 1] = NULL;
						root->Contents[idx2 + 1] = getNewBPlusTreeNodeContent();
					}
					/*Trocar apenas o conteudo, porque temos pointer a apontar para o primeiro elemento*/
					SwapContent(root->Contents[idx2 + 1], root->Contents[idx2]);
				}

				root->Contents[idx] = getNewBPlusTreeSetContent(data, key);

				root->CurrentSize += 1;

				//Quando mudamos o indice 0 temo que actualizar as parent key da arvore toda para fica coerente
				if (idx == 0)
					UpdateRootKey(root->Parent, key);

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
		//Quando mudamos o indice 0 temo que actualizar as parent key da arvore toda para fica coerente
		if (root->CurrentSize == 0)
			UpdateRootKey(root->Parent, key);

		root->CurrentSize += 1;
		return TRUE;

	}
	else
	{
		/*Divir o no ,e depois procurar novament a posição e inserir*/
		if (Split(paramRoot, root) != NULL)
		{
			BPlusTreeNode* aux = getNode(paramRoot->root, key, NULL);

			return addToNode(paramRoot, aux, data, key);
		}
	}

	return FALSE;
}

/// <summary>
/// Adicona um novo registo a tree
/// </summary>
/// <param name="paramRoot">tree a inserir o registo</param>
/// <param name="data">conteudo do registo</param>
/// <param name="key">key do registo</param>
/// <returns>TRUE se o registo foi inserido com sucesso, FALSO se não foi inserido e WARNING se foi ignorado</returns>
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

	/*Verificar se a key existe, se não ignoramos*/
	if (!KeyExist(paramRoot->root, key))
	{

		BPlusTreeNode* aux = getNode(paramRoot->root, key, NULL);

		if (aux == NULL)
			return FALSE;

		return  addToNode(paramRoot, aux, data, key);
	}
	else
	{
		printf("Registo com a key %5d ja existe, registo ignorado\n", (int)key);
		return  WARNING;
	}
	
	return FALSE;
}