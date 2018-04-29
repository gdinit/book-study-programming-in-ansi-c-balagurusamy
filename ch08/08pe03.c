/* 08pe03.c */
/* ===================================80 chars=============================== */

/*
Write a program to extract a portion of a character string and print the
extracted string. Assume that m characters are extracted, starting with the nth
character.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
/* exit(), EXIT_FAILURE */
#include <math.h>
#include <stdlib.h>
#include <string.h>
/* tolower() */
#include <ctype.h>

/*
Required to prevent -> "scanf: floating point formats not linked" in Borland 3
*/
/*
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
extern		_floatconvert;
#pragma extref _floatconvert
#endif
*/

/* BEGIN: FLUSH */
/*
#ifdef _WIN32
#define FLUSH fflush(stdin);
#elif defined __unix__
#define FLUSH fpurge(stdin);
#elif defined __APPLE__
#define FLUSH fpurge(stdin);
#else
#define FLUSH fflush(stdin);
#endif
*/
/* END: FLUSH */

/* CONFIGURATION */
#define TITLE "EXTRACT PORTION OF STRING"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 0

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

void extractPrint(char *pmyString, int n, int m)
{
	int j;
	printf("\nHere is the extracted substring: \"");
	for (j = n - 1; m > 0; (m--, j++)) {
		printf("%c", pmyString[j]);
	}
	printf("\"\nGoodbye!\n");
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	/* hardcoded values */
	/* start extracting from this character */
	int n = 3;
	/* characters to extract */
	int m = 6;
	char myString[] = "C is fun!";
	char *pmyString = &myString[0];
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	printf("\nSETTINGS\nString: \"%s\"\n", myString);
	printf("Extraction begins with character number %d\n", n);
	printf("Extracting %d characters\n", m);
	extractPrint(pmyString, n, m);
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
