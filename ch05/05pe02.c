/* 05pe02.c */

/* ===================================80 chars=============================== */

/*
Write a program to find the number of and sum of all integers greater than 100
and less than 200 that are divisible by 7.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>

/*
Required to prevent -> "scanf: floating point formats not linked
"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

#define LINESTOCLEARSCREEN 90
/* Configuration */
#define NUMBEG 100
#define NUMEND 200
#define NUMDIV 7

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printHeader(void)
{
	printf("----------------------------------------\n"
	       "EVEN/ODD DETECTOR\n");
}

void printFooter(void) { printf("----------------------------------------\n"); }

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	int n = 0, count = 0, sum = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();

	for (n = NUMBEG + 1; n < NUMEND; n++) {
		if (n % 7 == 0) {
			count++;
			sum += n;
		}
	}
	printf("\nThere are %d numbers that are\n"
	       "greater than %d and less than %d\n"
	       "and divisible by %d.\n\n"
	       "Sum of these numbers is %d.\n"
	       "List of these numbers:\n",
	       count, NUMBEG, NUMEND, NUMDIV, sum);
	for (n = NUMBEG + 1; n < NUMEND; n++) {
		if (n % 7 == 0) {
			printf("%d ", n);
		}
	}
	printf("\n");
	printFooter();

	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf("\n\n\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
