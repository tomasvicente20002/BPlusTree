#pragma once
#include <stdlib.h>
#include "mylib.h"

typedef struct LinkedListNode_st
{
	/// <summary>
	/// Valor a apontar
	/// </summary>
	void* Value;
	/// <summary>
	/// No aseguir
	/// </summary>
	struct LinkedListNode_st* Next;
	/// <summary>
	/// No anterior
	/// </summary>
	struct LinkedListNode_st* Previous;

} LinkedListNode;
typedef struct LinkedList_st
{
	/// <summary>
	/// Cabeça (primeiro elemento)
	/// </summary>
	LinkedListNode* Head;
	/// <summary>
	/// Cauda (ultimo elemento)
	/// </summary>
	LinkedListNode* Tail;
	/// <summary>
	/// Quantidade de elementos
	/// </summary>
	int Count;
} LinkedList;
LinkedListNode* GetNewNode();
LinkedList* GetNewLinkedList();
LinkedListNode* AddToTheBeginingLinkedList(LinkedList* list, void* value);
LinkedListNode* AddOrderlyToLinkedList(LinkedList* list, void* value, BOOL compareFnc(const void*, const void*));
LinkedListNode* AddToLinkedList(LinkedList* list, void* value);
BOOL remove_node(LinkedListNode** list_head, void* elem, BOOL compareFnc(const void*, const void*));
BOOL RemoveLinkedListNode(LinkedList* list, void* elem, BOOL compareFnc(const void*, const void*));
void Pop(LinkedList* list);

