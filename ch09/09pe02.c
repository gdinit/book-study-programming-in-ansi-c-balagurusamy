/* 09pe02.c */
/* ===================================80 chars=============================== */

/*
Write a function space(x) that can be used to provide a space of x positions
between two output numbers. Demonstrate its application.
*/

/*
Compiled & tested on:
	Apple LLVM version 9.1.0 (clang-902.0.39.1)
	Target: x86_64-apple-darwin17.5.0
with:
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
	-Wparentheses -Wformat-zero-length 09pe02.c -o binary/09pe02
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
/* ********************************** */
#define TITLE "FUNCTION: SPACE(X)"
#define CFGDEBUG 1

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
void space(int);

/* GLOBALS */

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	int n1 = 128;
	int n2 = 89;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	printf("Two numbers with space(5):\t%d", n1);
	space(5);
	printf("%d\n", n2);

	printf("Two numbers with space(0):\t%d", n1);
	space(0);
	printf("%d\n", n2);

	printf("Two numbers with space(1):\t%d", n1);
	space(1);
	printf("%d\n", n2);

	printf("Two numbers with space(23):\t%d", n1);
	space(23);
	printf("%d\n", n2);

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

void space(int x)
{
	int n;

	for (n = 0; n < x; n++) {
		printf(" ");
	}
}

/* ===================================80 chars=============================== */
/* EOF */
