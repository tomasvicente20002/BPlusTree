#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define LINE_BREAK '\n'
#define NULL_CHAR  '\0'

struct String
{
    int Length;
    char* String;
};

struct StringArray
{
    int Length;
    struct String** Strings;
};

struct String* AlocNewString();
struct String* AlocNewStringSetSize(int len);
struct StringArray* AlocNewStringArray();
struct StringArray* AlocNewStringArraySetSize(int arraySize);
struct String* NewString(char* newValue);
void SetNewString(struct String* oldValue, const char* newValue);
struct String Concat(const char* PrimeiraParte, const char* SegundaParte);
struct String* ConcatString(struct String* PrimeiraParte, struct String* SegundaParte);
struct String* SubString(struct String* value, int position, int length);
struct StringArray* SplitString(struct String* value, const char caracter);
struct StringArray* ToStringArray(const char** values, int len);
BOOL CopyFile(char fileSource[], char fileDestination[]);
int LasIndexOf(struct String* value, const char caracter);
BOOL WriteToFile(struct String* fileName, struct StringArray* value);
char ToUpper(char letter);
void ToUpperRef(char* letter);