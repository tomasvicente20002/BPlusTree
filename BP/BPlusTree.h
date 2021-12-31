#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mylib.h"

/// <summary>
/// Conteudo do node
/// </summary>
typedef struct BPlusTreeNodeContent_st {
	/// <summary>
	/// Key no node
	/// </summary>
	uint32_t Key;
	/// <summary>
	/// Conteudo do node
	/// </summary>
	void* Data;
	/// <summary>
	/// Filho do node
	/// </summary>
	struct BPlusTreeNode_st* Child;/* type of BPlusTreeNode, but wast */

}BPlusTreeNodeContent;

/// <summary>
/// Nó de um B++ Tree
/// </summary>
typedef struct BPlusTreeNode_st {
	/// <summary>
	/// Varios node do no
	/// </summary>
	BPlusTreeNodeContent** Contents;
	/// <summary>
	/// Quantide de contents no nó
	/// </summary>
	int CurrentSize;
	/// <summary>
	/// Pai do nó
	/// </summary>
	struct BPlusTreeNode_st* Parent; 
}BPlusTreeNode;


/// <summary>
/// B++ Tree
/// </summary>
typedef struct BPlusTree_st {
	/// <summary>
	/// Primeiro elemento da arvore
	/// </summary>
	BPlusTreeNode *root;
	/// <summary>
	/// Quantidade de elementos que a arvore pode ter por node
	/// </summary>
	int size;
}BPlusTree;

/// <summary>
/// Cria e inicializa uma struct do tipo BPlusTreeNodeContent
/// </summary>
/// <returns>Sruct</returns>
BPlusTreeNodeContent* getNewBPlusTreeNodeContent();


/// <summary>
/// Criar um array do tipo BPlusTreeNodeContent
/// </summary>
/// <param name="size"></param>
/// <returns>Sruct</returns>
BPlusTreeNodeContent** getNewBPlusTreeArray(int size);


/// <summary>
/// Criar , incializa e define os campos data e key de uma BPlusTreeNodeContent
/// </summary>
/// <param name="data"></param>
/// <param name="key"></param>
/// <returns>Sruct</returns>
BPlusTreeNodeContent* getNewBPlusTreeSetContent(void* data, uint32_t key);

/// <summary>
/// Cria e incializa uma struct BPlusTreeNode
/// </summary>
/// <returns>Sruct</returns>
BPlusTreeNode* getNewBPlusTreeNode();

/// <summary>
/// Cria e incializa uma struct do tipo BPlusTree
/// </summary>
/// <param name="size"></param>
/// <returns>Sruct</returns>
BPlusTree* getNewBPlusTree(int size);


/// <summary>
/// Verifica se é um leaf node, no no ultimo nivel
/// </summary>
/// <param name="root"></param>
/// <returns>TRUE se o no é leaf, caso contrário FALSE</returns>
BOOL isleafNode(const BPlusTreeNode* root);



/// <summary>
/// ontem a chave menor da arvore
/// </summary>
/// <param name="root">no</param>
/// <returns>Chave menor da arvore</returns>
int getMinKey(const BPlusTreeNode* root);


/// <summary>
/// Imprimes os nos da arvore
/// </summary>
/// <param name="root">no atual</param>
/// <param name="n">quantidade de nos a ser imprimidos, se for menor que 0 imprime todos</param>
/// <param name="imprimidos">quantidade de nos imprimidos</param>
/// <returns>TRUE se já imprimiu todos os nós até n</returns>
BOOL PrintNodes(const BPlusTreeNode* root, int n, int* imprimidos);


/// <summary>
/// Obtem o leaf node onde devera se inserido o registo
/// </summary>
/// <param name="root">no</param>
/// <param name="key">chave a inserir</param>
/// <param name="parent">pai do root</param>
/// <returns>Nó a inserir o registo</returns>
BPlusTreeNode* getNode(BPlusTreeNode* root, uint32_t key, BPlusTreeNode* parent);


/// <summary>
/// Verifica se uma key já existe na arvore
/// </summary>
/// <param name="root">no</param>
/// <param name="key">key a verificar</param>
/// <returns>TRUE se a key já existe no registo , caso contrário FALSE</returns>
BOOL KeyExist(BPlusTreeNode* root, uint32_t key);

/// <summary>
/// Actualiza o primeiro elemento de todos parent nodes
/// </summary>
/// <param name="root">no a actulizar</param>
/// <param name="key">nova chave</param>
void UpdateRootKey(BPlusTreeNode* root, int key);


/// <summary>
/// Adiciona um novo filho a arvore
/// </summary>
/// <param name="paramRoot">arvore</param>
/// <param name="root">no a inserir o registo</param>
/// <param name="node">no a inserir</param>
/// <returns></returns>
BOOL addNewChild(BPlusTree* paramRoot, BPlusTreeNode* root, BPlusTreeNode* node);


/// <summary>
/// Divide um no em dois
/// </summary>
/// <param name="paramRoot">tree</param>
/// <param name="root">no a ser dividido</param>
/// <returns></returns>
BPlusTreeNode* Split(BPlusTree* paramRoot, BPlusTreeNode* root);

/// <summary>
/// Traca o conteudo de dois BPlusTreeNodeContent
/// </summary>
/// <param name="node1"></param>
/// <param name="node2"></param>
void SwapContent(BPlusTreeNodeContent* node1, BPlusTreeNodeContent* node2);

/// <summary>
/// Adiciona um novo registo a arvore
/// </summary>
/// <param name="paramRoot">tree inde se vai inserir o registo</param>
/// <param name="root">no a inserir o registo</param>
/// <param name="data">conteudo do registo</param>
/// <param name="key">key do registo</param>
/// <returns></returns>
BOOL addToNode(BPlusTree* paramRoot, BPlusTreeNode* root, void* data, uint32_t key);

/// <summary>
/// Adicona um novo registo a tree
/// </summary>
/// <param name="paramRoot">tree a inserir o registo</param>
/// <param name="data">conteudo do registo</param>
/// <param name="key">key do registo</param>
/// <returns>TRUE se o registo foi inserido com sucesso, FALSO se não foi inserido e WARNING se foi ignorado</returns>
BOOL addToBPlusTree(BPlusTree* paramRoot, void* data, uint32_t key);