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
		list->Count = 0;
	}

	return list;
}

LinkedListNode* AddToTheBeginingLinkedList(LinkedList* list, void* value)
{
	LinkedListNode* node = GetNewNode();
	node->Value = value;
	node->Previous = NULL;

	//Cen�rio 1 lista est� vazia
	if (list->Head == NULL && list->Tail == NULL)
	{
		//Cabe�a e igual ao n�
		list->Head = node;
		list->Tail = node;
	}
	else
	{
		list->Head->Previous = node;
		node->Next = list->Head;
		list->Head = node;
	}

	return node;
}

LinkedListNode* AddOrderlyToLinkedList(LinkedList* list, void* value, BOOL compareFnc(const void*, const void*))
{


	//Cen�rio 1 lista est� vazia
	if (list->Head == NULL && list->Tail == NULL)
	{	//Obter um novo n�
		return AddToLinkedList(list, value);
	}
	//Temos que ir procurar o sitio certo a inserir
	else
	{
		LinkedListNode* tempNode = list->Head;


		while (tempNode != NULL)
		{
			if (compareFnc(tempNode->Value, value))
			{
				//Adicao normal no fim da lista
				if (tempNode == list->Tail)
					return AddToLinkedList(list, value);
				else
				{
					//Temos que inserir a meio dos nos
					return NULL;

				}
			}

			tempNode = tempNode->Next;
		}

		//Chegamos ao fim e n�o encontramos um sitio onde inserir por isso fica no fim
		return AddToLinkedList(list, value);
	}
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
		return FALSE;


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
