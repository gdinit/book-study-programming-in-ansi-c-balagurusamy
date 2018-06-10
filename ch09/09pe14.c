/* 09pe14.c */
/* ===================================80 chars=============================== */

/*
 * Develop a top-down modular program that will perform the following tasks:
 *
 * (a) Read two integer arrays with unsorted elements
 * (b) Sort them in ascending order
 * (c) Merge the sorted arrays
 * (d) Print the sorted list
 *
 * Use functions for carrying out each of the above tasks. The main function
 * should have only function calls.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe14.c -o binary/09pe14
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <math.h> /* ceil() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */
#include <time.h>   /* srand(time()) */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "ACCEPT, SORT, MERGE, DISPLAY INT ARRAYS"
#define CFGDEBUG 0
#define ARR_ELEMENT_COUNT 3 /* number of integers in each array */

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
void takeInputIntArray(int *arr, const int elements);
int cmpfunc(const void *a, const void *b);
void sortAscending(int *arr, const int elements);
void copyMergeArrays(int *arr1, int *arr2, int *arr3, int arr1Size,
		     int arr2Size, int arr3Size);
void displayArray(int *arr, int elements);

/* GLOBALS */

/* PROGRAM ENTRY POINT */
int main(void)
{
	int arr1[ARR_ELEMENT_COUNT] = {0};
	int arr2[ARR_ELEMENT_COUNT] = {0};
	int arr3[ARR_ELEMENT_COUNT * 2] = {0};

	cls();
	displayHeaderLine();
	displayHeaderText();

	/* take input array 1 & array 2 */
	takeInputIntArray(arr1, ARR_ELEMENT_COUNT);
	takeInputIntArray(arr2, ARR_ELEMENT_COUNT);

	/* merge two arrays into one */
	copyMergeArrays(arr1, arr2, arr3, ARR_ELEMENT_COUNT, ARR_ELEMENT_COUNT,
			ARR_ELEMENT_COUNT * 2);

	/* sort the merged big array */
	sortAscending(arr3, ARR_ELEMENT_COUNT * 2);

	/* display the merged big array */
	printf("\nMerged and sorted array: ");
	displayArray(arr3, ARR_ELEMENT_COUNT * 2);

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
void takeInputIntArray(int *arr, const int elements)
{
	int n;

	printf("Please enter up to " XSTR(
	    elements) " integers separated with space character or -999 to end "
		      "data entry\nINPUT: ");
	for (n = 0; n < elements; n++) {
		int x;
		scanf("%d", &x);
		if (x == -999) {
			break;
		} else {
			arr[n] = x;
		}
	}
}

int cmpfunc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

void sortAscending(int *arr, const int elements)
{
	/*int n;*/
	qsort(arr, elements, sizeof(int), cmpfunc);
}

/* Copy arr1 and arr2 into arr3 */
void copyMergeArrays(int *arr1, int *arr2, int *arr3, int arr1Size,
		     int arr2Size, int arr3Size)
{
	int n;
	int n3 = 0;

	assert(arr1Size + arr2Size >= arr3Size);
	for (n = 0; n < arr1Size; n++) {
		arr3[n3] = arr1[n];
		n3++;
	}
	for (n = 0; n < arr2Size; n++) {
		arr3[n3] = arr2[n];
		n3++;
	}
}

void displayArray(int *arr, int elements)
{
	int n;
	for (n = 0; n < elements; n++) {
		printf("%d ", arr[n]);
	}
	printf("\n");
}

/* ===================================80 chars=============================== */
/* EOF */
