// main.h : Include file for standard system include files,
// or project specific include files.
#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct laureate_st {
	uint32_t id;
	char firstname[100];
	char surname[100];
	char birthdate[11];
	char Country[50];
	char CountryCode[3];
	char City[50];
	char died[11];
	char gender[7];
	uint32_t year;
	char category[12];
	uint32_t share;
	char motivation[350];
} laureate_t;

laureate_t *getNewLiveLaureate();

// TODO: Reference additional headers your program requires here.
