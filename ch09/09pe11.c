/* 09pe11.c */
/* ===================================80 chars=============================== */

/*
 * Write a function that can be called to find the largest element of an m by n
 * matrix.
 */

/* Here we have PRNG based random numbers in a matrix.
 * findLargestElement() will identify the largest element and list details */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe11.c -o binary/09pe11.exe
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h> /* ceil() */
#include <stdio.h>
#include <stdlib.h> /* EXIT_SUCCESS */
#include <string.h> /* for title */
#include <time.h>   /* srand(time()) */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/* ********************************** */
#define TITLE "MATRIX LARGEST ELEMENT FINDER"
#define CFGDEBUG 0
#define ROW 5
#define COLUMN 5
#define MAXVAL 99
#define ITERATIONS 256

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
	long int top; /* known largest element's position */
	long int top_i;
	long int top_j;
};

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
/* ********************************** */
void init(struct dataCard_t *p_myData);
void mainLoop(struct dataCard_t *p_myData);
int getChoice(void);
void printMainMenu(void);
void actionChoice(int choice, struct dataCard_t *p_myData);
void getNumber(long int *num);
void showMatrix(struct dataCard_t *p_myData);
void fillMatrixRandomly(struct dataCard_t *p_myData);
int randRange(int n);
void findLargestElement(void *firstElement, const int m, const int n);

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

/* initialize a dataCard for the purposes of application */
void init(struct dataCard_t *p_myData) { fillMatrixRandomly(p_myData); }

void mainLoop(struct dataCard_t *p_myData)
{
	int choice;

	while (1) {
		choice = getChoice();
		actionChoice(choice, p_myData);
	}
}

int getChoice(void)
{
#define ENTRY_LOWEST 1
#define ENTRY_HIGHEST 3

	int num;

	do {
		printMainMenu();
		FLUSH
		scanf("%d", &num);
		if (num < ENTRY_LOWEST || num > ENTRY_HIGHEST) {
			printf("\n\nERROR: Invalid input!\n");
		}
	} while (num < ENTRY_LOWEST || num > ENTRY_HIGHEST);
	printf("Valid choice selected: %d\n", num);

	return num;
}

void printMainMenu(void)
{
	/* without this ugly hack double quotes do get printed :( */
	char title[] = XSTR(TITLE);
	unsigned int len = strlen(title);
	title[0] = ' ';       /* first double quote */
	title[len - 1] = ' '; /* second double quote */

	printf("\n\n\n");
	displayHeaderLine();
	/*displayHeaderText();*/
	printf("***%s- MAIN MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: SHOW matrix\n"
	       "\t2: ASSIGN RANDOM integers into matrix\n"
	       "\t3: EXIT program\n"
	       "Enter your choice: ",
	       title);
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

	if (p_myData->m[0][0] == 999) {
		/* dummy. just to keep -Wunused-parameter happy */
	}
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

	findLargestElement((void *)&(p_myData->m), ROW, COLUMN);
}

/* fill a dataCard_t->m matrix with randomly generated numbers */
void fillMatrixRandomly(struct dataCard_t *p_myData)
{

	int i, j, r;
	static int rand_seeded = 0;

	if (!rand_seeded) {
		srand(time(0));
		rand_seeded++;
		if (CFGDEBUG) {
			printf("[DEBUG] rand: seeded!\n");
		}
	} else {
		if (CFGDEBUG) {
			printf("[DEBUG] rand: no need to seed\n");
		}
	}
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COLUMN; j++) {
			r = randRange(100);
			p_myData->m[i][j] = r;
		}
	}
}

int randRange(int n)
{
	int r;
	int limit;

	limit = RAND_MAX - (RAND_MAX % n);
	while ((r = rand()) >= limit) {
		/* nothing */
	}

	return r % n;
}

void findLargestElement(void *firstElement, const int m, const int n)
{
	/* top = greatest number in array */
	long int top = 0, top_m = 0, top_n = 0;
	long int *p_data = (long int *)firstElement;
	long int row = 0, col = 0;

	printf("\n");
	for (row = 0; row < m; ++row) {		/* Loop of row */
		for (col = 0; col < n; ++col) { /* Loop for column */
			/* Read element of 2D array */
			if (CFGDEBUG) {
				printf("aiData[%02ld][%02ld] = %02ld", row, col,
				       *(p_data + (row * n) + col));
			}
			/* larger than known largest? */
			if (*(p_data + (row * n) + col) > top) {
				top = *(p_data + (row * n) + col);
				top_m = row;
				top_n = col;
				if (CFGDEBUG) {
					printf(" <--- New top element value is "
					       "%ld!\n",
					       top);
				}
			} else {
				if (CFGDEBUG) {
					printf("\n");
				}
			}
		}
	}
	printf("Largest element: %02ld, located at m[%ld][%ld]\n", top, top_m,
	       top_n);
}

/* ===================================80 chars=============================== */
/* EOF */
