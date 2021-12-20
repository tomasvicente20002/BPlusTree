#include "linkedList.h"


LinkedListNode* GetNewNode()
{
	LinkedListNode* node;
	node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	
	if (node != NULL)
	{
		node->Next = NULL;
		node->Previous = NULL;		
	}

	return node;
}

LinkedList* GetNewLinkedList()
{
	LinkedList* list;
	list = (LinkedList*)malloc(sizeof(LinkedList));

	if (list != NULL)
	{
		list->Head = NULL;
		list->Tail = NULL;
		list->Count = -1;
	}

	return list;
}

LinkedListNode* AddToLinkedList(LinkedList* list, void* value)
{
	//Obter um novo n�
	LinkedListNode* node = GetNewNode();
	node->Value = value;
	node->Previous = NULL;

	//Cen�rio 1 lista est� vazia
	if (list->Head == NULL && list->Tail == NULL)
	{
		//Cabe�a e igual ao n�
		list->Head = node;
	}
	//Cen�rio 2 lista j� tem elementos
	else
	{
		//O cauda ir� passar a ser o penultimo n� , logo o nex passa apontar para o novo n� que ir� ser a nova cauda
		list->Tail->Next = node;
		//O n� antererior a novo n� (nova cauda) � a cauda atual
		node->Previous = list->Tail;
	}

	//A cauda � igual o nova a inserir
	list->Tail = node;

	list->Count += 1;

	return node;
}

void Pop(LinkedList* list)
{
	//Validar se existem n� na lista
	if (list->Head == NULL)
		return;

	//s� existem um elemtno na lista
	if (list->Head == list->Tail)
	{
		//Apontam todas para null
		list->Head = NULL;
		free(list->Tail);
		list->Tail = NULL;
	}
	else
	{
		//A cauda passa a ser o penultimo elemento
		list->Tail = list->Tail->Previous;
		free(list->Tail->Next);
		list->Tail->Next = NULL;
	}

	list->Count -= 1;

}

BOOL RemoveLinkedListNode(LinkedList* list, void* elem, BOOL compareFnc(const void*, const void*))
{
	if (remove_node(&list->Head, elem, compareFnc))
	{
		list->Count += 1;
		return TRUE;
	}
	else
		return FALSE


}

BOOL remove_node(LinkedListNode** list_head, void* elem, BOOL compareFnc(const void*, const void*)) 
{
	if (*list_head == NULL) {
		return FALSE;
	}
	LinkedListNode* it = *list_head;
	// Stop at the end of the list
	while (it != NULL) {
		// "If the pointer value if "it" is the same as"elem", we have found it

		//TODO: Corrigir
		//if (strcmp(&((OcorrenciaLetras_t*)it->Value)->letra, &elem)) 
		if(TRUE)		
		{
			if ((it->Previous == NULL) && (it->Next == NULL)) {	// Only 1 element
				free(it);	// Free the container, not the data
				it = NULL;
				*list_head = NULL;
			
				return TRUE;
			}
			if (it->Next == NULL) {	// Last element
				it->Previous->Next = NULL;
				free(it);
				it = NULL;			
				

				return TRUE;
			}
			if (it->Previous == NULL) {
				it->Next->Previous = NULL;
				*list_head = it->Next;
				free(it);
				it = NULL;
				return TRUE;
			}
			// Nothing special
			it->Previous->Next = it->Next;
			it->Next->Previous = it->Previous;
			free(it);
			it = NULL;
			return TRUE;
		}
		it = it->Next;
	}
	// Elem is not in list
	return FALSE;
}
