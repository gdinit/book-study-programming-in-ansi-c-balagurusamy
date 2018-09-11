/* 09pe12.c */
/* ===================================80 chars=============================== */

/*
 * Write a function that can be called to compute the product of two matrices of
 * size m  by n and n by m. The main function provides the values for m and n
 * and two matrices.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe12.c -o binary/09pe12
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
#define TITLE "COMPUTE PRODUCT OF MATRICES"
#define CFGDEBUG 0
#define ROWCOL_MIN 2    /* Matrix row/col size - minimum value */
#define ROWCOL_MAX 5    /* Matrix row/col size - minimum value */
#define MATRIX_EL_MIN 2 /* Matrix element - minimum value */
#define MATRIX_EL_MAX 9 /* Matrix element - maximum value */

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

struct matrix_size_t {
	unsigned long int rows1;
	unsigned long int cols1;
	unsigned long int rows2;
	unsigned long int cols2;
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
void displayUL2DMatrix2(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			const unsigned long int rows1,
			const unsigned long int cols1,
			const unsigned long int el2[ROWCOL_MAX][ROWCOL_MAX],
			const unsigned long int rows2,
			const unsigned long int cols2);
/* Fill an unsigned long int 2D matrix with randomly generated numbers. */
void fillUL2DMatrixRandomly(unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			    unsigned long int rows, unsigned long int cols,
			    long int minVal, long int maxVal);
void productOfMatrices(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
		       const unsigned long int rows1,
		       const unsigned long int el2[ROWCOL_MAX][ROWCOL_MAX],
		       const unsigned long int rows2,
		       const unsigned long int cols2,
		       unsigned long int pr[ROWCOL_MAX][ROWCOL_MAX]);

/* GLOBALS */

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct matrix_size_t matrix_size;
	unsigned long int m1[ROWCOL_MAX][ROWCOL_MAX];
	unsigned long int m2[ROWCOL_MAX][ROWCOL_MAX];
	unsigned long int pr[ROWCOL_MAX][ROWCOL_MAX];

	cls();
	displayHeaderLine();
	displayHeaderText();

	srand((unsigned int)time(0));
	matrix_size = pick2DMatrixSize(ROWCOL_MIN, ROWCOL_MAX);
	printf("\nmatrix size has been randomly chosen: rows=%lu cols=%lu.\n",
	       matrix_size.rows1, matrix_size.cols1);

	matrix_size.rows2 = matrix_size.cols1;
	matrix_size.cols2 = matrix_size.rows1;

	zeroFillUL2DMatrix(m1, matrix_size.rows1, matrix_size.cols1);
	fillUL2DMatrixRandomly(m1, matrix_size.rows1, matrix_size.cols1,
			       MATRIX_EL_MIN, MATRIX_EL_MAX);
	zeroFillUL2DMatrix(m2, matrix_size.rows2, matrix_size.cols2);
	fillUL2DMatrixRandomly(m2, matrix_size.rows2, matrix_size.cols2,
			       MATRIX_EL_MIN, MATRIX_EL_MAX);
	printf("matrices have been filled with random numbers between " XSTR(
	    MATRIX_EL_MIN) " and " XSTR(MATRIX_EL_MAX) ".\n\n");
	displayUL2DMatrix2(m1, matrix_size.rows1, matrix_size.cols1, m2,
			   matrix_size.rows2, matrix_size.cols2);

	productOfMatrices(m1, matrix_size.rows1, m2, matrix_size.rows2,
			  matrix_size.cols2, pr);

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

/* Display two unsigned long int 2D matrices side by side */
void displayUL2DMatrix2(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
			const unsigned long int rows1,
			const unsigned long int cols1,
			const unsigned long int el2[ROWCOL_MAX][ROWCOL_MAX],
			const unsigned long int rows2,
			const unsigned long int cols2)
{
	unsigned long int r, c;
	unsigned long int c2;
	unsigned long int rows;
	unsigned long int m1nIndex = 0;
	unsigned long int m2nIndex = 0;
	unsigned long int m1total = rows1 * cols1;
	unsigned long int m2total = rows2 * cols2;

	rows = rows1 > rows2 ? rows1 : rows2;

	printf("Displaying two unsigned long int 2D matrices side by side "
	       "(%lu, %lu),(%lu, %lu):"
	       "\n",
	       rows1, cols1, rows2, cols2);

	for (r = 0; r < rows; r++) {
		c2 = 0;
		for (c = 0; c < cols1 + 1 + cols2; c++) {
			if (c < cols1) {
				if (m1nIndex < m1total) {
					printf("%lu ", el1[r][c]);
					m1nIndex++;
				} else {
					printf("  ");
				}
			} else if (c == cols1 && r == 0) {
				printf("  x   ");
			} else if (c == cols1 && r != 0) {
				printf("      ");
			} else if (c > cols1) {
				if (m2nIndex < m2total) {
					printf("%lu ", el2[r][c2]);
					m2nIndex++;
					c2++;
				}
			}
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

void productOfMatrices(const unsigned long int el1[ROWCOL_MAX][ROWCOL_MAX],
		       const unsigned long int rows1,
		       const unsigned long int el2[ROWCOL_MAX][ROWCOL_MAX],
		       const unsigned long int rows2,
		       const unsigned long int cols2,
		       unsigned long int pr[ROWCOL_MAX][ROWCOL_MAX])
{
	unsigned long int i, j, k, sum;

	for (i = 0; i < rows1; i++) {
		for (j = 0; j < cols2; j++) {
			sum = 0;
			for (k = 0; k < rows2; k++) {
				sum = sum + el1[i][k] * el2[k][j];
			}
			pr[i][j] = sum;
		}
	}

	printf("\nProduct of entered matrices:\n");
	for (i = 0; i < rows1; i++) {
		for (j = 0; j < cols2; j++) {
			printf("%lu\t", pr[i][j]);
		}
		printf("\n");
	}
	printf("\nYou can verify the result on this website:\n"
	       "https://matrixcalc.org/en\n");
}

/* ===================================80 chars=============================== */
/* EOF */
