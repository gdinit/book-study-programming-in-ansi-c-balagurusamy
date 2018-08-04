/* 11pe08.c */
/* ===================================80 chars=============================== */

/*
 * Given an array of sorted list of integer numbers, write a function to search
 * for a particular item, using the method of binary search. And also show how
 * this function may be used in a program. Use pointers and pointer arithmetic.
 *
 * (Hint: In binary search, the target value is compared with the array's middle
 * element. Since the table is sorted, if the required value is smaller, we know
 * that all values greater than the middle element can be ignored. That is, in
 * one attempt, we eliminate one half of the list. This search can be applied
 * recursively till the target value is found.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 11pe08.c str5cpy.c -o binary/11pe08
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
#define TITLE "BINARY SEARCH WITH POINTERS AND POINTER ARITHMETIC"
#define CFGDEBUG 1

/* BEGIN: FLUSH */
#ifdef _WIN32
#define FLUSH fflush(stdin);
#elif defined __unix__
#define FLUSH fpurge(stdin);
#elif defined __APPLE__
#define FLUSH fpurge(stdin);
#else
#define FLUSH fflush(stdin);
#endif
/* END: FLUSH */

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void displayArrayInt(int *p, unsigned int els);
int binarySearch(int sorted_list[], int low, int high, int element);

/* PROGRAM ENTRY POINT */
int main(void)
{
	int arr[] = { 1, 3, 7, 19, 23, 44, 57, 66, 69, 71, 89, 91, 98, 99 };
	int elements = (int)(sizeof arr / sizeof(int));
	int key, p;

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("\nThe ORIGINAL Array - ");
	displayArrayInt(arr, sizeof arr / sizeof(int)); /* original */
	printf("\nThere are %d elements in the array.\n", elements);

	printf("Enter the KEY to search for in array: ");
	scanf("%d", &key);
	printf("\nKEY is set to: %d\n", key);

	printf("Searching for KEY %d in array...\n", key);
	p = binarySearch(arr, 0, sizeof arr / sizeof(int), key);
	if(p >= 0) {
		printf("The key %d was found as element #%d.\n",key, p + 1);
	} else {
		printf("The key %d was not found.\n", key);
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
void displayArrayInt(int *p, unsigned int els) /* els = number of elements */
{
	int n;

	printf("Array elements:\n");
	for (n = 0; n < (int)els; n++) {
		printf("\t\t\tElement #%2d:  %2d\n", n + 1, *(p + n));
	}
	printf("\n");
}

/* C binary search using recursion technique
 * source: http://www.zentut.com/c-tutorial/c-binary-search/ */
int binarySearch(int sorted_list[], int low, int high, int element)
{
	int middle;

	if (high < low) {
		return -1;
	}

	middle = low + (high - low) / 2;

	if (element < sorted_list[middle]) {
		return binarySearch(sorted_list, low, middle - 1, element);
	} else if (element >sorted_list[middle]) {
		return binarySearch(sorted_list, middle + 1, high, element);
	} else {
		return middle;
	}
}

/* ===================================80 chars=============================== */
/* EOF */
