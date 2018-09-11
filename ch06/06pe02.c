/* 06pe02.c */

/* ===================================80 chars=============================== */

/*
The factorial of an integer m is the product of consecutive integers from 1 to
m. That is,
	factorial m = m! = m x (m-1) x ... x 1
Write a program that computes and prints a table of factorials for any given m.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*
#include <string.h>
*/

/*
Required to prevent -> "scanf: floating point formats not linked"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
#endif

/* CONFIGURATION */
#define TITLE "FACTORIAL CALCULATION"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66

typedef struct Data_t {
	long int m;
	unsigned long int f;
} Data;

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

void getN(Data *pdata)
{
	printf("Enter an integer (m) to calculate its factorial: ");
	scanf("%ld", &pdata->m);
	printf("m is supplied as: %ld\n", pdata->m);
}

void process(Data *pdata)
{
	long int m = pdata->m;
	long int i = 0;
	unsigned long int f = 0;

	if (m < 0) {
		printf("ERROR: m is negative! Factorial of a negative number "
		       "doesn't exist!\n");
		exit(1);
	} else {
		for ((f = 1, i = 1); i <= m; i++) {
			f *= i;
		}
		printf("Factorial of %ld is %lu\n", m, f);
		pdata->f = f;
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	Data data;
	Data *pdata = &data;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	getN(pdata);
	process(pdata);
	displayFooter();
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf("\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
