#pragma once
#include <stdlib.h>
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
} LinkedList;

LinkedListNode* GetNewNode();
LinkedList* GetNewLinkedList();
LinkedListNode* AddToLinkedList(LinkedList* list, void* value);
void Pop(LinkedList* list);
BOOL remove_node(LinkedListNode** list_head, char* elem);