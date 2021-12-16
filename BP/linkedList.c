#include "linkedList.h"
#include "types.h"

LinkedListNode* GetNewNode()
{
	LinkedListNode* node;
	node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	node->Next = NULL;
	node->Previous = NULL;
}

LinkedList* GetNewLinkedList()
{
	LinkedList* list;
	list = (LinkedList*)malloc(sizeof(LinkedList));
	list->Head = NULL;
	list->Tail = NULL;
	return list;
}

LinkedListNode* AddToLinkedList(LinkedList* list, void* value)
{
	//Obter um novo nó
	LinkedListNode* node = GetNewNode();
	node->Value = value;
	node->Previous = NULL;

	//Cenário 1 lista está vazia
	if (list->Head == NULL && list->Tail == NULL)
	{
		//Cabeça e igual ao nó
		list->Head = node;
	}
	//Cenário 2 lista já tem elementos
	else
	{
		//O cauda irá passar a ser o penultimo nó , logo o nex passa apontar para o novo nó que irá ser a nova cauda
		list->Tail->Next = node;
		//O nó antererior a novo nó (nova cauda) é a cauda atual
		node->Previous = list->Tail;
	}

	//A cauda é igual o nova a inserir
	list->Tail = node;

	return node;
}

void Pop(LinkedList* list)
{
	//Validar se existem nó na lista
	if (list->Head == NULL)
		return;

	//só existem um elemtno na lista
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

}

BOOL remove_node(LinkedListNode** list_head, char* elem) {
	if (*list_head == NULL) {
		printf("Cannot remove element, list is empty\n");
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