/* 08pe11.c */
/* ===================================80 chars=============================== */

/*
Write a program to read two strings and compare them using the function
strncmp() and print a message that the first string is equal, less, or greater
than the second one.
*/

/*
Compiled & tested with:
	gcc -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment
	-Wparentheses -Wformat-zero-length 08pe11.c -o binary/08pe11
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
/* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <stdlib.h>
#include <string.h>
/* tolower() */
#include <ctype.h>

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
#define TITLE "STRING COMPARATOR"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STRMAXLEN 20
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 1

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
void getString(char *s);
void compareAndPrint(char *s1, char *s2);

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char str1[STRMAXLEN + 1] = "";
	char str2[STRMAXLEN + 1] = "";
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	getString(str1);
	printf("String #1 is: \"%s\"\n", str1);
	getString(str2);
	printf("String #2 is: \"%s\"\n", str2);

	compareAndPrint(str1, str2);

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
	printf("Please enter a string (" XSTR(STRMAXLEN) " chars max): ");
	FLUSH;
	scanf("%" XSTR(STRMAXLEN) "[^\n]", s);
}

void compareAndPrint(char *s1, char *s2)
{
	int result = strncmp(s1, s2, STRMAXLEN);

	printf("\nCOMPARISON RESULT:\t");
	if (result < 0) {
		printf("String1 is LESS THAN String2.\n");
	} else if (result == 0) {
		printf("String1 is EQUAL TO String2.\n");
	} else if (result > 0) {
		printf("String1 is GREATER THAN String2.\n");
	}
}

/* ===================================80 chars=============================== */
/* EOF */
