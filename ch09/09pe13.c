/* 09pe13.c */
/* ===================================80 chars=============================== */

/*
 * Design and code an interactive modular program that will use functions to a
 * matrix of m by n size, compute column averages and row averages, and then
 * print the entire matrix with averages shown in respective rows and columns.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe13.c -o binary/09pe13
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
/**************************************/
#define TITLE "MATRIX ROW COLUMN AVERAGES"
#define CFGDEBUG 0
#define ROWCOL_MIN 2    /* Matrix row/col size - minimum value */
#define ROWCOL_MAX 5    /* Matrix row/col size - minimum value */
#define MATRIX_EL_MIN 1 /* Matrix element - minimum value */
#define MATRIX_EL_MAX 9 /* Matrix element - maximum value */

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

struct matrix_size_t {
	unsigned long int rows1;
	unsigned long int cols1;
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
unsigned long int generateNumberMax(unsigned long int max);
unsigned long int generateNumberRange(unsigned long int min,
				      unsigned long int max);
unsigned long int generateNumberRangeExclude(unsigned long int min,
					     unsigned long int max,
					     unsigned long int *excludes,
					     unsigned long int excludesCount);
struct matrix_size_t pick2DMatrixSize(unsigned long int min,
				      unsigned long int max);
void zeroFillUL2DMatrix(unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			const unsigned long int rows,
			const unsigned long int cols);
void displayUL2DMatrix(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
		       const unsigned long int rows,
		       const unsigned long int cols);
/* Fill an unsigned long int 2D matrix with randomly generated numbers. */
void fillUL2DMatrixRandomly(unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			    unsigned long int rows, unsigned long int cols,
			    long int minVal, long int maxVal);
void calculateDisplayUL2DMatrixAverages(
    const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
    const unsigned long int rows, const unsigned long int cols);
void calcDisplayColumnAvg(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			  const unsigned long int rows,
			  const unsigned long int cols,
			  const unsigned long int col);
void calcDisplayRowAvg(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
		       const unsigned long int cols,
		       const unsigned long int row);

/* GLOBALS */

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct matrix_size_t matrix_size;
	unsigned long int m1[ROWCOL_MAX][ROWCOL_MAX];

	cls();
	displayHeaderLine();
	displayHeaderText();

	srand((unsigned int)time(0));
	matrix_size = pick2DMatrixSize(ROWCOL_MIN, ROWCOL_MAX);
	printf("\nmatrix size has been randomly chosen: rows=%lu cols=%lu.\n",
	       matrix_size.rows1, matrix_size.cols1);

	zeroFillUL2DMatrix(m1, matrix_size.rows1, matrix_size.cols1);
	fillUL2DMatrixRandomly(m1, matrix_size.rows1, matrix_size.cols1,
			       MATRIX_EL_MIN, MATRIX_EL_MAX);
	printf("matrix have been filled with random numbers between " XSTR(
	    MATRIX_EL_MIN) " and " XSTR(MATRIX_EL_MAX) ".\n\n");
	printf("MATRIX\n");
	displayUL2DMatrix(m1, matrix_size.rows1, matrix_size.cols1);
	printf("\n");

	printf("ROW & COLUMN AVERAGES\n");
	calculateDisplayUL2DMatrixAverages(m1, matrix_size.rows1,
					   matrix_size.cols1);

	displayFooter();

	return EXIT_SUCCESS;
}

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

/* Return a random int r:	0 >= r <= max */
unsigned long int generateNumberMax(unsigned long int max)
{
	int r, limit;

	if (max == 0) {
		printf("ERROR: generateNumberMax() received 0!\n");
		exit(EXIT_FAILURE);
	} else {
		max++;
	}

	limit = RAND_MAX - (RAND_MAX % max);
	while ((r = rand()) >= limit) {
		/* nothing */
	}

	return r % max;
}

/* Return a random int r:	min >= r <= max */
unsigned long int generateNumberRange(unsigned long int min,
				      unsigned long int max)
{
	unsigned long int r;
	unsigned long int trying = 1;

	if (min > max) {
		printf("ERROR: generateNumberRange() min > max!\n");
		exit(EXIT_FAILURE);
	}
	while (trying) {
		r = generateNumberMax(max);
		if (r >= min) {
			trying = 0;
		}
	}

	return r;
}

/* Return a random int r:	min >= r <= max
 * r cannot be one of the numbers in 'int array excludes' */
unsigned long int generateNumberRangeExclude(unsigned long int min,
					     unsigned long int max,
					     unsigned long int *excludes,
					     unsigned long int excludesCount)
{
	unsigned long int r;
	unsigned long int it;
	unsigned long int searching = 1;

	if (min > max) {
		printf("ERROR: generateNumberRangeExclude() min > max!\n");
		exit(EXIT_FAILURE);
	}
	while (searching) {
		r = generateNumberMax(max);
		searching = 0;
		for (it = 0; it < excludesCount; it++) {
			if (r == excludes[it] || r < min) {
				searching = 1;
			}
		}
	}
	return r;
}

/* picks a random matrix_size row/col size based on min/max parameters.
 * ensures row and col is not the same number. */
struct matrix_size_t pick2DMatrixSize(unsigned long int min,
				      unsigned long int max)
{
	unsigned long int row, col;
	struct matrix_size_t ret;
	/* begin: without this code block, 'random' value of row always is 4? */
	unsigned long int i = generateNumberMax(256);
	unsigned long int j = generateNumberMax(1024);
	unsigned long int k = generateNumberMax(4096);
	unsigned long int excludes[2] = {0};
	unsigned long int excludesCount = 0;
	i = i + (j << k);
	k = ((i + j + k) % ROWCOL_MAX) + 1;
	/* end: anti-4 */
	row = generateNumberRange(min, max);
	excludes[0] = row;
	excludesCount++;
	col = generateNumberRangeExclude(min, max, excludes, excludesCount);
	ret.rows1 = row;
	ret.cols1 = col;
	return ret;
}

/* Zero fill an unsigned long int 2D matrix */
void zeroFillUL2DMatrix(unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			const unsigned long int rows,
			const unsigned long int cols)
{
	unsigned long int r, c, i = 0;

	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			el1[r][c] = 0;
			i++;
		}
	}
}

/* Display an unsigned long int 2D matrix */
void displayUL2DMatrix(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
		       const unsigned long int rows,
		       const unsigned long int cols)
{
	unsigned long int r, c;

	for (r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			printf("%lu ", el1[r][c]);
		}
		printf("\n");
	}
}

/* Fill an unsigned long int 2D matrix with randomly generated numbers. */
void fillUL2DMatrixRandomly(unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			    unsigned long int rows1, unsigned long int cols1,
			    long int minVal, long int maxVal)
{
	unsigned long int r, c;

	for (r = 0; r < rows1; r++) {
		for (c = 0; c < cols1; c++) {
			el1[r][c] = generateNumberRange(minVal, maxVal);
		}
	}
}

void calculateDisplayUL2DMatrixAverages(
    const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
    const unsigned long int rows, const unsigned long int cols)
{
	unsigned long int r, c;

	for (r = 0; r < rows + 1; r++) {
		if (r == rows) {
			printf("Avg:\t");
		} else {
			printf("\t");
		}
		for (c = 0; c < cols + 1; c++) {
			printf("\t");
			if (r == rows && c == cols) {
				printf("  ");
			} else if (r == rows && c == 0) {
				calcDisplayColumnAvg(el1, rows, cols, c);
			} else if (r == rows && c != 0) {
				calcDisplayColumnAvg(el1, rows, cols, c);
			} else if (c == cols) {
				calcDisplayRowAvg(el1, cols, r);
			} else {
				printf("%lu ", el1[r][c]);
			}
		}
		printf("\n");
	}
}

void calcDisplayColumnAvg(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			  const unsigned long int rows,
			  const unsigned long int cols,
			  const unsigned long int col)
{
	unsigned long int i, j, sum;

	sum = 0;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (j == col) {
				sum = sum + el1[i][j];
			}
		}
	}
	printf("%.2f", (float)sum / (float)i);
}

void calcDisplayRowAvg(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
		       const unsigned long int cols,
		       const unsigned long int row)
{
	unsigned long int r, i, sum;

	r = row;
	sum = 0;
	for (i = 0; i < cols; i++) {
		sum = sum + el1[r][i];
	}
	printf("\tAvg: %.2f", (float)sum / (float)i);
}

/* ===================================80 chars=============================== */
/* EOF */
