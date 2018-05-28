/* 09pe03.c */
/* ===================================80 chars=============================== */

/*
Write a function that will round a floating-point number to an indicated decimal
place. For example the number 17.457 would yield the value 17.46 when it is
rounded off to two decimal places.
*/

/*
Compiled & tested on:
	Apple LLVM version 9.1.0 (clang-902.0.39.1)
	Target: x86_64-apple-darwin17.5.0
with:
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
	-Wparentheses -Wformat-zero-length 09pe03.c -o binary/09pe03
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* On Borland C++ v.3.1 we use round() from custom implementation */
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
#include "round.h"
#endif

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

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
/* ********************************** */
#define TITLE "FUNCTION: FLOATING POINT ROUNDER"
#define CFGDEBUG 1

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
double round1(double x, unsigned int digits);
void processSet(double d, unsigned int digits);

/* GLOBALS */

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	unsigned int digits = 2;
	double d1 = 17.457f;
	unsigned int n;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	/* example number from the book */
	processSet(d1, digits);

	printf("\n");

	/* a more exhaustive example */
	for (n = 0; n < 9; n++) {
		processSet(3.123456789, n);
	}
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

/* Rounding Method #1:	using recursion (slow?) */
double round1(double x, unsigned int digits)
{
	if (digits > 0) {
		return round1(x * 10.0, digits - 1) / 10.0;
	} else {
		return round(x);
	}
}

void processSet(double d, unsigned int digits)
{
	printf("digits=%u\tPRE=%f\t", digits, d);
	d = round1(d, digits);
	printf("POST=%f\n", d);
}
/* ===================================80 chars=============================== */
/* EOF */
