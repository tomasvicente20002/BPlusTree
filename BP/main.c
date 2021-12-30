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





BOOL ReadFile(char path[], BPlusTree* root)
{
	FILE* ptrFile;
	fopen_s(&ptrFile, path, "r");

	if (ptrFile == NULL)
		return FALSE;

	laureate_t* record = getNewLiveLaureate();

	if (record == NULL)
	{
		fclose(ptrFile);
		return FALSE;
	}


	/*
	Warning	C4996	'fscanf': This function or variable may be unsafe.Consider using fscanf_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.See online help for details.	
	*/
#pragma warning( push )
#pragma warning( disable : 4996 )
	while (fscanf(ptrFile, " %d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%d;%[^\n]",
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
#pragma warning( pop )

		addToBPlusTree(root, record,record->id);

		record = NULL;
		record = getNewLiveLaureate();

		if (record == NULL)
		{
			fclose(ptrFile);
			return FALSE;
		}
	}

	return TRUE;

}

int main(int argc, char* argv[])
{
	BPlusTree* root = getNewBPlusTree(5);

	char* fileName = "C:\\Users\\tomas\\Downloads\\new_nobel_prizes.csv";

	ReadFile(fileName, root);	

	return 0;
}


