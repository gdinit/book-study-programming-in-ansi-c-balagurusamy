/* 08pe15.c */
/* ===================================80 chars=============================== */

/*
Given a string
		char str[] = "123456789";
Write a program that displays the following:
			1
		       232
		      34543
		     4567654
		    567898765
*/

/*
Compiled & tested on:
	Apple LLVM version 9.1.0 (clang-902.0.39.1)
	Target: x86_64-apple-darwin17.5.0
with:
	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
	-Wparentheses -Wformat-zero-length 08pe15.c -o binary/08pe15
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* str5cpy (safe copy) */
#include "str5.h"

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

/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define TITLE "STRING TO PYRAMID"
#define LENGTH 9
#define CFGDEBUG 1

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
void getString(char *s);
void printPyramid(char *s);

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char s[LENGTH + 1] = "";
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	getString(s);
	printf("String is set to: \"%s\"\n", s);

	printPyramid(s);

	displayFooter();
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	/* TODO space works in DOS but is not cross platform. fix or remove */
	printf("\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
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

void getString(char *s)
{
	printf("Please enter a " XSTR(LENGTH) "-character long string: ");
	FLUSH;
	scanf("%" XSTR(LENGTH) "[^\n]", s);
}

void printPyramid(char *s)
{
/*
-------------------------------------
		X	PADDING CHARS
................1	16
...............232	15
..............34543	14
.............4567654	13
............567898765	12
-------------------------------------
*/
/* Center column of pyramid is this many characters from left */
#define CENTER_CHAR_COLUMN 17

	int padding = CENTER_CHAR_COLUMN;
	/* lines */
	int m;
	/* chars */
	int n;
	/* number of extra chars to print */
	int extra = 0;
	/* extra counter */
	int k;

	/* spacer line */
	printf("\n");

	/* print 5 lines */
	for (m = 0; m < 5; m++) {
		/* for this line, reduce padding space by one */
		padding--;

		/* print as many padding whitespace as needed */
		for (n = 0; n < padding; n++) {
			printf(" ");
		}

		/* LEFT EDGE: print this line's char */
		printf("%c", s[m]);

		/* for 1st line, this is all that's needed... */
		if (m == 0) {
			/* end of line */
			printf("\n");
			continue;
		}

		/* for this line, increase extra char printing by one */
		extra++;

		/* print extra chars, till CENTER COLUMN */
		for (k = 0; k < extra; k++) {
			printf("%c", s[m + k + 1]);
		}

		/* print extra chars, after CENTER COLUMN */
		for (k = extra; k > 0; k--) {
			printf("%c", s[m + k - 1]);
		}

		/* end of line */
		printf("\n");
	}
}

/* ===================================80 chars=============================== */
/* EOF */
