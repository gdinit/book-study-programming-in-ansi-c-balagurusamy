/* 08pe01.c */
/* ===================================80 chars=============================== */

/*
Write a program, which reads your name from the keyboard and outputs a list of
ASCII codes, which represent your name.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
/* exit(), EXIT_FAILURE */
#include <math.h>
#include <stdlib.h>

/*
Required to prevent -> "scanf: floating point formats not linked"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
extern _floatconvert;
#pragma extref _floatconvert
#endif

/* CONFIGURATION */
#define TITLE "NAME TO ASCII CODE CONVERTER"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
/* use fpurge(stdin) for linux? */
#define FLUSH fflush(stdin);
#define STR(x) #x
#define XSTR(x) STR(x)
#define NAMEMAXLEN 32

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

/* get name from the user and save it in an array */
void getName(char *pname)
{
	printf("Enter name (32 chars max): ");
	FLUSH;
	scanf("%" XSTR(NAMEMAXLEN) "[^\n]", pname);
}

void printAscii(char *pname)
{
	int n;
	printf("\nHere is the ASCII character codes for supplied name, %s.\n",
	       pname);
	printf("LETTER\t\tASCII CODE\n");
	for (n = 0; (n <= NAMEMAXLEN && pname[n] != '\0'); n++) {
		printf("%c\t=\t%4d\n", pname[n], pname[n]);
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char name[NAMEMAXLEN] = {'\0'};
	char *pname = &name[0];
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	getName(pname);
	printAscii(pname);
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
