
#include "mylib.h"



struct String* AlocNewString()
{
    struct String* returnValue = malloc(sizeof(struct String*));
    return returnValue;
}

struct String* AlocNewStringSetSize(int len)
{
    struct String* returnValue = AlocNewString();
    returnValue->Length = len;
    returnValue->String = (char*)malloc((len + 1) * sizeof(char)); //Alocar memoria com o tamanho da string e +1 por causa do '\0'
    return returnValue;
}

struct StringArray* AlocNewStringArray()
{
    return (struct StringArray*)malloc(sizeof(struct StringArray*));
}

struct StringArray* AlocNewStringArraySetSize(int arraySize)
{
    struct StringArray* returnValue = malloc(sizeof(struct StringArray*));
    returnValue->Length = arraySize;
    returnValue->Strings = malloc(sizeof(struct String*) * (arraySize + 1));

    return returnValue;
}

struct String* NewString(char* newValue)
{
    int idx = 0;
    struct String* retValue = AlocNewStringSetSize(strlen(newValue));

    strcpy(retValue->String, newValue);

    return retValue;
}

void SetNewString(struct String* oldValue, const char* newValue)
{
    if (oldValue != NULL)
        free(oldValue);

    struct String* retValue = AlocNewStringSetSize(strlen(newValue));

    strcpy(retValue->String, newValue);
}

struct String Concat(const char* PrimeiraParte, const char* SegundaParte)
{
    struct String retValue;

    retValue.Length = strlen(PrimeiraParte) + strlen(SegundaParte) + 1;

    retValue.String = malloc(retValue.Length); /*alocar memoria*/

    strcpy(retValue.String, PrimeiraParte); /* Copiar  PrimeiraParte*/

    strcat(retValue.String, SegundaParte); /* Copiar  SegundaParte*/

    return retValue;
}

struct String* ConcatString(struct String* PrimeiraParte, struct String* SegundaParte)
{
    struct String* retValue = AlocNewString();

    retValue->Length = PrimeiraParte->Length + SegundaParte->Length + 1;

    retValue->String = malloc(retValue->Length); /*alocar memoria*/

    strcpy(retValue->String, PrimeiraParte->String); /* Copiar  PrimeiraParte*/

    strcat(retValue->String, SegundaParte->String); /* Copiar  SegundaParte*/

    return retValue;
}

struct String* SubString(struct String* value, int position, int length)
{
    struct String* retValue = AlocNewString();
    int c;
    retValue->Length = length;

    retValue->String = (char*)malloc((retValue->Length + 1) * sizeof(char)); /*alocar memoria para a string mais o \0*/

    for (c = 0; c < length; c++)
        retValue->String[c] = value->String[c + position];

    retValue->String[c] = '\0';

    return retValue;
}

struct StringArray* SplitString(struct String* value, const char caracter)
{

    int cntCaracter = 0;
    int idx = 0;
    int lastPosition = 0;
    int cntSubstring = 0;
    struct StringArray* retValue = NULL;

    /*Contar quantos caracter existem para saber quanto espaço de memoria tem-se que alocar*/
    for (idx = 0; idx < value->Length; idx++)
        if (value->String[idx] == caracter)
            cntCaracter++;

    retValue = AlocNewStringArraySetSize(cntCaracter);

    for (idx = 0; idx < value->Length; idx++)
        if (value->String[idx] == caracter)
        {
            retValue->Strings[cntSubstring] = SubString(value, lastPosition, (idx - lastPosition));
            lastPosition = idx + 1;
            cntSubstring++;
        }

    if (idx > lastPosition)
        retValue->Strings[cntSubstring] = SubString(value, lastPosition, (idx - lastPosition));

    return retValue;
}

struct StringArray* ToStringArray(const char** values, int len)
{
    struct StringArray* retValue = AlocNewStringArraySetSize(len);

    for (int idx = 0; idx < len; idx++)
        SetNewString(retValue->Strings[idx], values[idx]);

    return retValue;
}

BOOL CopyFile(char fileSource[], char fileDestination[])
{
    FILE* fs = fopen(fileSource, "r");
    FILE* fd = fopen(fileDestination, "w+");

    int content;

    if (fs == NULL || fd == NULL)
    {
        if (fs != NULL)
            fclose(fs);

        if (fd != NULL)
            fclose(fd);

        return FALSE;
    }

    content = fgetc(fs);

    while (content != EOF)
    {
        fputc(content, fd);
        content = fgetc(fs);
    }

    fclose(fs);
    fclose(fd);

    return TRUE;
}

int LasIndexOf(struct String* value, const char caracter)
{
    int len = value->Length;

    for (; len >= 0; len--)
        if (value->String[len] == caracter)
            break;

    return len;
}

BOOL WriteToFile(struct String* fileName, struct StringArray* value)
{

    FILE* fs = fopen(fileName->String, "w+");

    if (fs == NULL)
        return FALSE;

    for (int idx = 0; idx < value->Length; idx++)
        for (int idx2 = 0; idx2 <= value->Strings[idx]->Length; idx2++)
            fputc(value->Strings[idx]->String[idx2 - 1], fs);

    fclose(fs);

    return TRUE;
}

char ToUpper(char letter)
{
    return letter >= 'a' && letter <= 'z' ? letter - ('a' - 'A') : letter;
}

void ToUpperRef(char* letter)
{
    if (*letter >= 'a' && *letter <= 'z')
        *letter -= ('a' - 'A');

    return;
}