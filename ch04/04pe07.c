/* 04pe07.c */

/* ===================================80 chars=============================== */

/*
Write a program that prints the value 10.45678 in exponential format with the
following specifications:
(a) correct to two decimal places
(b) correct to four decimal places, and
(c) correct to eight decimal places.
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

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printHeader(void)
{
	printf("-------------- EXPONENTIAL FORMAT DEMO --------------\n");
}

void printFooter(void)
{
	printf("-----------------------------------------------------\n");
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	double n = 10.45678;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	printf("%.2e\n", n);
	printf("%.4e\n", n);
	printf("%.8e\n", n);
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
