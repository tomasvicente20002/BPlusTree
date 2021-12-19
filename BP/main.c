// main.c : Defines the entry point for the application.
//

#include "main.h"
#include "linkedList.h"

laureate_t* getNewLiveLaureate()
{
	laureate_t* ptr = malloc(sizeof(laureate_t));
	if (ptr != NULL)
	{
		ptr->id = 0;
		ptr->firstname[0] = '\n';
		ptr->surname[0] = '\n';
		ptr->birthdate[0] = '\n';
		ptr->Country[0] = '\n';
		ptr->CountryCode[0] = '\n';
		ptr->City[0] = '\n';
		ptr->died[0] = '\n';
		ptr->gender[0] = '\n';
		ptr->year = 0;
		ptr->category[0] = '\n';
		ptr->share = 0;
		ptr->motivation[0] = '\n';
	}
	return ptr;
}



int main()
{
	LinkedList* list = GetNewLinkedList();
	int a = 8;

	AddToLinkedList(list, &a);
			
	return 0;
}


