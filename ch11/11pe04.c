/* 11pe04.c */
/* ===================================80 chars=============================== */

/*
 * Write a function using pointers to add two matrices and return the resultant
 * matrix to the calling function.
 */

/*
 * Implementation Notes
 * 
 * To keep it super simple, limited the RNG to 1-6
 * To keep it super simple, fixed the row/col size to 2,3
 */
	
/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 11pe04.c -o binary/11pe04
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
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
#define TITLE "FUNCTION TO ADD TWO MATRICES TOGETHER"
#define DB_SIZE 10
#define CFGDEBUG 0
#define ROWS 2
#define COLS 3
#define RNG_MAX 6
#define RNG_MAX_MINUS_ONE RNG_MAX - 1

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
int randRange(int n);
void zFillMatrix(int *elementFirst, int rows, int cols);
void rFillMatrix(int *elementFirst, int rows, int cols);
void displayMatrix(int *elementFirst, int rows, int cols);
void addMatrix(const int rows, const int cols, const int *e1, const int *e2,
	       int *e3);

/* PROGRAM ENTRY POINT */
int main(void)
{
	int m1[ROWS][COLS];
	int m2[ROWS][COLS];
	int m3[ROWS][COLS];

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	zFillMatrix(&m1[0][0], ROWS, COLS);
	zFillMatrix(&m2[0][0], ROWS, COLS);
	zFillMatrix(&m3[0][0], ROWS, COLS);

	rFillMatrix(&m1[0][0], ROWS, COLS);
	rFillMatrix(&m2[0][0], ROWS, COLS);

	printf("matrix1:\n");
	displayMatrix(&m1[0][0], ROWS, COLS);
	printf("\n");


	printf("matrix2:\n");
	displayMatrix(&m2[0][0], ROWS, COLS);
	printf("\n");

	printf("Adding two matrices together...\n");
	printf("\n");
	addMatrix(ROWS, COLS, &m1[0][0], &m2[0][0], &m3[0][0]);

	printf("matrix3:\n");
	displayMatrix(&m3[0][0], ROWS, COLS);
	printf("\n");

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

void zFillMatrix(int *elementFirst, int rows, int cols)
{
	int r, c;

	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			*(elementFirst + (r * cols) + c) = 0;
		}
	}
}

/* fill a matrix with random numbers within limit of 1 - RNG_MAX (both incl.) */
void rFillMatrix(int *elementFirst, int rows, int cols)
{
	int r, c, n;
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

	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			n = randRange(RNG_MAX_MINUS_ONE);
			n = randRange(RNG_MAX_MINUS_ONE);
			n = randRange(RNG_MAX_MINUS_ONE);
			n++;
			*(elementFirst + (r * cols) + c) = n;
		}
	}
}

void displayMatrix(int *elementFirst, int rows, int cols)
{
	int r, c;

	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			printf("%2d ", *(elementFirst + (r * cols) + c));
		}
		printf("\n");
	}
}

void addMatrix(const int rows, const int cols, const int *e1, const int *e2,
	       int *e3)
{

	int r, c;

	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			*(e3 + (r * cols) + c) = 
			*((e1 + (r * cols) + c)) + *((e2 + (r * cols) + c));
		}
	}

}

/* ===================================80 chars=============================== */
/* EOF */
