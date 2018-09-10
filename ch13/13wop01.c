/* 13wop01.c */
/* ===================================80 chars=============================== */

/*
 * Worked Out Problem 13.1
 *
 * Write a program that uses a table of integers whose size will be specified
 * interactively at run time.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 13wop01.c -o binary/13wop01
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
#define TITLE "INTERACTIVELY SIZED TABLE OF INTEGERS"
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
	int *p, *table;
	int size;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	printf("\nWhat is the size of table?");
	scanf("%d", &size);
	printf("\n");
	/*----------Memory Allocation----------*/
	if((table = (int*)malloc(size * sizeof(int))) == NULL) {
		printf("No space available\n");
		exit(EXIT_FAILURE);
	}

	printf("\nAddress of the first byte is %ld\n", (long int)table);

	/*----------Reading table values----------*/
	printf("\nInput table values\n");

	for(p = table; p < table + size; p++) {
		scanf("%d", p);
	}
	/*----------Printing table values in reverse order----------*/
	for (p = table + size - 1; p >= table; p--) {
		printf("%d is stored at address %ld\n", *p, (long int)p);
	}

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
