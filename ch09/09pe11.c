/* 09pe11.c */
/* ===================================80 chars=============================== */

/*
 * Write a function that can be called to find the largest element of an m by n
 * matrix.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe11.c mt.c -o binary/09pe11
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mt.h"

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
/* ********************************** */
#define TITLE "MATRIX LARGEST ELEMENT FINDER"
#define CFGDEBUG 1
#define ROW 10
#define COLUMN 10
#define MAXVAL 99

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

struct dataCard_t {
	long int m[ROW][COLUMN];
	/* currently known largest element in array, it's i and j subscripts */
	long int top;
	long int top_i;
	long int top_j;

	long int dummy;
};

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
/* ********************************** */
void init(struct dataCard_t *p_myData);
void mainLoop(struct dataCard_t *p_myData);
int getChoice(struct dataCard_t *p_myData);
void printMainMenu(struct dataCard_t *p_myData);
void actionChoice(int choice, struct dataCard_t *p_myData);
void getNumber(long int *num);
void showMatrix(struct dataCard_t *p_myData);
void fillMatrixRandomly(struct dataCard_t *p_myData);

/* GLOBALS */

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	struct dataCard_t myData;
	struct dataCard_t *p_myData = &myData;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	init(p_myData);
	mainLoop(p_myData);
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	displayFooter();
	/* END: Standard Footer Section ************************************* */

	return EXIT_SUCCESS;
}

/* FUNCTIONS */
void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeader(void)
{
	char s[] = TITLE;
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n%s\n\n", s);
}

void displayFooter(void)
{
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n");
}

/* initialize a dataCard for the purposes of application */
void init(struct dataCard_t *p_myData) { fillMatrixRandomly(p_myData); }

void mainLoop(struct dataCard_t *p_myData)
{
	int choice;

	while (1) {
		choice = getChoice(p_myData);
		actionChoice(choice, p_myData);
	}
}

int getChoice(struct dataCard_t *p_myData)
{
#define ENTRY_LOWEST 1
#define ENTRY_HIGHEST 3

	int num;

	do {
		printMainMenu(p_myData);
		FLUSH
		scanf("%d", &num);
		if (num < ENTRY_LOWEST || num > ENTRY_HIGHEST) {
			printf("\n\nERROR: Invalid input!\n");
		}
	} while (num < ENTRY_LOWEST || num > ENTRY_HIGHEST);
	printf("Valid choice selected: %d\n", num);

	return num;
}

void printMainMenu(struct dataCard_t *p_myData)
{
	printf("\n\n\n*** TITLE MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: SHOW matrix\n"
	       "\t2: ASSIGN RANDOM integers into matrix\n"
	       "\t3: EXIT program\n"
	       "Enter your choice: ");

	/* dummy, just to keep -Wunused-parameter happy */
	p_myData->dummy = 0;
}

/*
 * find the greatest long int element in a dataCard_t->m matrix
 */
void findLargestElement(struct dataCard_t *p_myData)
{
	/* top = greatest number in array */
	int i, j;
	int top = 0;
	int top_i, top_j;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COLUMN; j++) {
			if (p_myData->m[i][j] > top) {
				top = p_myData->m[i][j];
				top_i = i;
				top_j = j;
			}
		}
	}

	p_myData->top = top;
	p_myData->top_i = top_i;
	p_myData->top_j = top_j;
}

void actionChoice(int choice, struct dataCard_t *p_myData)
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: SHOW MATRIX\n");
		showMatrix(p_myData);
		break;
	case 2:
		printf("\nACTIONING: ASSIGN RANDOM integers into matrix\n");
		fillMatrixRandomly(p_myData);
		showMatrix(p_myData);
		break;
	case 3:
		printf("\nACTIONING: EXIT program\nGoodbye!\n");
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}

	/* dummy, just to keep -Wunused-parameter happy */
	p_myData->dummy = 0;
}

void showMatrix(struct dataCard_t *p_myData)
{
	int i, j;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COLUMN; j++) {
			printf("%02ld ", p_myData->m[i][j]);
		}
		printf("\n");
	}

	findLargestElement(p_myData);
	printf("\nLargest element: %ld, located at m[%ld][%ld]\n",
	       p_myData->top, p_myData->top_i, p_myData->top_j);
}

/*
 * fill a dataCard_t->m matrix with randomly generated numbers
 */
void fillMatrixRandomly(struct dataCard_t *p_myData)
{

	int i, j, r;
	static int mt_seeded = 0;

	if (mt_seeded == 0) {
		init_genrand(time(NULL));
		mt_seeded++;
	}

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COLUMN; j++) {
			r = genrand_int32() % MAXVAL;
			p_myData->m[i][j] = r;
		}
	}
}

/* ===================================80 chars=============================== */
/* EOF */
