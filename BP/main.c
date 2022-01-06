// main.c : Defines the entry point for the application.
//

#include "main.h"
#define MAXCHAR 512
#define NCOL 13

laureate_t* getNewLiveLaureate()
{
	laureate_t* ptr = malloc(sizeof(laureate_t));

	if (ptr == NULL)
		return NULL;
	
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
	
	return ptr;
}

laureate_t* create_element(char row[NCOL][MAXCHAR])
{
	laureate_t* new_elem = getNewLiveLaureate();
	if (new_elem == NULL) {
		return NULL;
	}

	new_elem->id = atoi(row[0]);
/*
Warning	C4996	'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead.
*/
#pragma warning( push )
#pragma warning( disable : 4996 )
	strcpy(new_elem->firstname, row[1]);
	strcpy(new_elem->surname, row[2]);
	strcpy(new_elem->birthdate, row[3]);
	strcpy(new_elem->died,  row[4]);
	strcpy(new_elem->Country,  row[5]);
	strcpy(new_elem->CountryCode,  row[6]);
	strcpy(new_elem->City,  row[7]);
	strcpy(new_elem->gender,  row[8]);
	new_elem->year = atoi(row[9]);
	strcpy(new_elem->category,row[10]);
	new_elem->share = atoi(row[11]);
	strcpy(new_elem->motivation, row[12]);
#pragma warning( pop )
	return new_elem;
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

	int idx = 0;
	/*
	Warning	C4996	'fscanf': This function or variable may be unsafe.Consider using fscanf_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.See online help for details.	
	*/
#pragma warning( push )
#pragma warning( disable : 4996 )
	int lidos = 0;
	int key = 0;
	int minKey = 0;
	while ((lidos =fscanf(ptrFile, " %d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%[^;];%d;%[^\n]",
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
		record->motivation)) != 0)
	{
#pragma warning( pop )
		key = record->id;
		
		if (!addToBPlusTree(root, record, record->id))
		{
			
			printf("Erro ao adicionar o registo com o id %d", record->id);
			fclose(ptrFile);
			return FALSE;
		}
		idx++;
		minKey = getMinKey(root->root);

		record = NULL;
		record = getNewLiveLaureate();

		if (record == NULL)
		{
			fclose(ptrFile);
			return FALSE;
		}
	}


	fclose(ptrFile);
	printf("Linhas lidas %d\n", idx);
	printf("Ultima key lida %d\n", key);

	return TRUE;

}




BOOL ReadFileV2(char path[], BPlusTree* tree)
{
	FILE* ptrFile;
	char line[MAXCHAR];
	char Row[NCOL][MAXCHAR];
	int  i = 0;
	int idx = 0;
	int key = 0;

	fopen_s(&ptrFile, path, "r");

	if (ptrFile == NULL)
	{
		printf("Não foi possivel abrir o ficheiro");
		return FALSE;
	}

	while (fgets(line, sizeof(line), ptrFile)) {
		BPlusTreeNode* root = tree->root;
		char* token;
		token = strtok(line, ";");
		i = 0;
		while (token != NULL && i < NCOL) {
			strcpy(Row[i], token);
			int key = atoi(Row[0]);
			token = strtok(NULL, ";");
			i++;
		}

		laureate_t* record = create_element(Row);

		key = record->id;

		if (!addToBPlusTree(tree, record, record->id))
		{
			printf("Erro ao adicionar o registo com o id %d", record->id);
			fclose(ptrFile);
			return FALSE;
		}	

		idx++;
	}

	fclose(ptrFile);


	printf("Linhas lidas %d\n", idx);
	printf("Ultima key lida %d\n", key);

	return TRUE;

}

int main(int argc, char* argv[])
{

	char* fileName = NULL;
	int imprimidos = 0;

	/*se a quantidade for -1 imprime todos os nós*/
	int quantidade = 24;

	if (argc < 2)
	{
		fileName = malloc(sizeof(char) * MAX_FILE_PATH_LEGHT);

		if (fileName == NULL)
		{
			printf("Ocorreu um erro de memoria");
			return 1;
		}

		printf("Indique o caminho do ficheiro: ");
		gets_s(fileName, MAX_FILE_PATH_LEGHT);
		printf("Quantos elementos pretende ver (-1 para ver todos os nos): ");
		scanf_s("%d", &quantidade);
	}
	else
	{
		fileName = argv[1];

		if (argc > 2)
			quantidade = atoi(argv[2]);
	}

	BPlusTree* root = getNewBPlusTree(5);
	if (ReadFileV2(fileName, root))
	{		
		PrintNodes(root->root, quantidade, &imprimidos);
	}

	return 0;
}

