// main.c : Defines the entry point for the application.
//

#include "main.h"


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


BOOL ReadFile(char path[], LinkedList* list)
{
	FILE* ptrFile = fopen(path, "r");

	if (ptrFile == NULL)
		return FALSE;

	laureate_t* record = getNewLiveLaureate();

	if (record == NULL)
	{
		fclose(ptrFile);
		return FALSE;
	}

	while(fscanf(ptrFile, " %d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%d;%[^\n]",
		&record->id,
		record->firstname,
		record->surname,
		record->birthdate,
		record->died,
		record->Country,
		record->CountryCode,
		record->City,
		record->gender,
		&record->year,
		record->category,
		&record->share, 
		record->motivation) != 0)
	{
		AddToLinkedList(list, record);
		record = NULL;
		record = getNewLiveLaureate();

		if (record == NULL)
		{
			fclose(ptrFile);
			return FALSE;
		}
	}

}

int main(int argc,char *argv[])
{
	LinkedList* list = GetNewLinkedList();

	char* fileName = "C:\\Users\\tomas\\Downloads\\new_nobel_prizes.csv";

	ReadFile(fileName, list);
			
	return 0;
}


