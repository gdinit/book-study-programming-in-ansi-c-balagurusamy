/* 13wop02.c */
/* ===================================80 chars=============================== */

/*
 * Worked Out Problem 13.2
 *
 * Write a program to store a character string in a block of memory space
 * created by malloc and then modify the same to store a larger string.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 13wop02.c -o binary/13wop02
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort(), atoi()) */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "REALLOC DEMO"
#define CFGDEBUG 1
#ifndef NULL
#define NULL 0
#endif

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/

/* PROGRAM ENTRY POINT */
int main(void)
{
	char *buffer;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	if ((buffer = (char *)malloc(10)) == NULL) {
		printf("malloc failed!\n");
		exit(EXIT_FAILURE);
	}

	printf("Buffer of size %d created\n", _msize(buffer));
	strcpy(buffer, "HYDERABAD");
	printf("\nBuffer contains: %s\n", buffer);

	if((buffer = (char *)realloc(buffer, 15)) == NULL) {
		printf("realloc failed.\n");
		exit(EXIT_FAILURE);
	}
	printf("\nBuffer size modified.\n");
	printf("\nBuffer stil contains: %s\n", buffer);
	strcpy(buffer, "SECUNDERABAD");
	printf("\nBuffer now contains: %s\n", buffer);

	free(buffer);

	displayFooter();

	return EXIT_SUCCESS;
}
/**************************************/
void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeaderLine(void)
{
	int n;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}

void displayHeaderText(void)
{
	char s[] = TITLE;
	printf("%s\n", s);
}

void displayFooter(void)
{
	int n = 0;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}
/**************************************/

/* ===================================80 chars=============================== */
/* EOF */
