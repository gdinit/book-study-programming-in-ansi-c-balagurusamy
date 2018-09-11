/* 11pe09.c */
/* ===================================80 chars=============================== */

/*
 * Write a function (using a pointer parameter) that reverses the elements of a
 * given array.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 11pe09.c str5cpy.c -o binary/11pe09
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "FUNCTION THAT REVERSES THE ELEMENTS OF A GIVEN ARRAY"
#define CFGDEBUG 1

/* BEGIN: FLUSH rev.03 */
#ifdef _WIN32
#define FLUSH fflush(stdin);
/*#elif defined __unix__
#define FLUSH fpurge(stdin);*/
#elif defined __APPLE__
#define FLUSH fpurge(stdin);
#elif defined __gnu_linux__
#include <stdio_ext.h>
#define FLUSH __fpurge(stdin);
#else
#define FLUSH fflush(stdin);
#endif
/* END: FLUSH rev.03 */

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void reversePArrayInt(int *parr, int size);
void reverseArrayInt(int ar[], int size);
void displayArrayInt(int *p, unsigned int els); /* els = number of elements */

/* PROGRAM ENTRY POINT */
int main(void)
{
	int arr[] = {3, 5, 7, 9, 11, 27, 99};
	int *parr = &arr[0];

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("\n");

	printf("ORIGINAL array:\n");
	displayArrayInt(arr, sizeof arr / sizeof(int)); /* original */

	printf("Reversing using a pointer...\n");
	reversePArrayInt(parr, sizeof arr / sizeof(int)); /* reverse w/pointer */
	printf("REVERSED array:\n");
	displayArrayInt(arr, sizeof arr / sizeof(int)); /* reversed */

	printf("Reversing back without a pointer...\n");
	reverseArrayInt(arr, sizeof arr / sizeof(int)); /* reverse nonpointer */
	printf("REVERSED again, back to ORIGINAL array:\n");
	displayArrayInt(arr, sizeof arr / sizeof(int)); /* reversed again */

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
void reversePArrayInt(int *parr, int size)
{
	int i, temp;

	printf("reversePArrayInt executing...\n");
	for (i = 0; i < size / 2; ++i) {
		temp = *(parr + i);
		*(parr + i) = *(parr + (size - 1 - i));
		*(parr + (size - 1 - i)) = temp;
	}
}

void reverseArrayInt(int ar[], int size)
{
	int i, temp;

	printf("reverseArrayInt executing...\n");
	for (i = 0; i < size / 2; ++i) {
		temp = ar[i];
		ar[i] = ar[size - 1 - i];
		ar[size - 1 - i] = temp;
	}
}

void displayArrayInt(int *p, unsigned int els) /* els = number of elements */
{
	int n;

	printf("Here are the elements:\n");
	for (n = 0; n < (int)els; n++) {
		printf("\t\t\tElement #%2d:  %2d\n", n + 1, *(p + n));
	}
	printf("\n");
}

/* ===================================80 chars=============================== */
/* EOF */
