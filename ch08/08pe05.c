/* 08pe05.c */
/* ===================================80 chars=============================== */

/*
Write a program which will read a string and rewrite it in the alphabetical
order. For example, the word STRING should be written as GINRST.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c str5cpy.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
/* exit(), EXIT_FAILURE */
#include <stdlib.h>
#include <string.h>
/* tolower() */
#include <ctype.h>
/* str5cpy (safe copy) */
#include "str5.h"

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
#define TITLE "STRING ALPHABETICAL SORTER"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STRMAXLEN 128
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 0

int str5cpy(char *dst, size_t dstsize, const char *src, size_t nb, size_t mode);

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

/* I am being lazy and just uppercase'ing it! */
void getStr(char *p_str)
{
	printf("Please enter the string (will be converted to uppercase): ");
	FLUSH;
	scanf("%" XSTR(STRMAXLEN) "[^\n]", p_str);
}

void copyStr(char *p_str, char *p_newstr)
{
	int ret = 0;
	ret = str5cpy(p_newstr, STRMAXLEN, p_str, STRMAXLEN, NOTRUNC);
	if (ret < 0) {
		/* something went wrong with the str copy! */
		printf("ERROR: str5cpy returned %d!\n", ret);
		exit(EXIT_FAILURE);
	} else if (CFGDEBUG) {
		printf("OK string copied.\n");
	}
}

int charCompare(const void *a, const void *b)
{
	return (*(char *)a - *(char *)b);
}

void upperStr(char *p_str)
{
	int n, len;
	len = strlen(p_str);
	for (n = 0; n < len; n++) {
		p_str[n] = toupper(p_str[n]);
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char str[STRMAXLEN + 1] = "";
	char *p_str = str;
	char newstr[STRMAXLEN + 1] = "";
	char *p_newstr = newstr;
	int len = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	getStr(p_str);
	upperStr(p_str);
	printf("You supplied the following string: %s\n", str);
	copyStr(p_str, p_newstr);
	/* get len - needed by qsort */
	len = strlen(newstr);
	if (CFGDEBUG) {
		printf("LEN calculated as: %d\n", len);
	}
	/* TODO: sort newstr */
	qsort(newstr, len, sizeof(char), charCompare);
	printf("Here is the sorted version: %s\n", newstr);
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
