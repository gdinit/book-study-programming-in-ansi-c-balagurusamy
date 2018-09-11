/* 08pe13.c */
/* ===================================80 chars=============================== */

/*
Write a program that will copy m consecutive characters from a string s1
beginning at position n into another string s2.
*/

/*
Compiled & tested with:
	gcc -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment
	-Wparentheses -Wformat-zero-length 08pe13.c str5cpy.c -o binary/08pe13
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

/* CONFIGURATION */
#define TITLE "STRING PARTIAL COPY"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STRMAXLEN 64
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 0

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
void getM(int *m, char *s1, char *s2);
void getN(int *m, int *n, char *s1, char *s2);
void getString(char *s);
int strPartialCopy(char *from, char *to, int *pos, int *num_chars);
void reportParams(int *m, int *n, char *s1, char *s2);
/*
void getWord(char *w);
void searchCountPrint(char *word, char *text);
*/

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char s1[STRMAXLEN + 1] = "";
	char s2[STRMAXLEN + 1] = "";
	int m, n;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	printf("Enter STRING1 (" XSTR(STRMAXLEN) " chars max): ");
	getString(s1);
	printf("String1 is set to: \"%s\"\n", s1);

	printf("Enter STRING2 (" XSTR(STRMAXLEN) " chars max): ");
	getString(s2);
	printf("String2 is set to: \"%s\"\n", s2);

	getM(&m, s1, s2);
	printf("m is set to: %d\n", m);

	getN(&m, &n, s1, s2);
	printf("n is set to: %d\n", n);

	reportParams(&m, &n, s1, s2);

	{
		/* strPartialCopy(from, to, copyCharOnward, copyChars); */
		int ret = strPartialCopy(s1, s2, &n, &m);
		if (ret == -1) {
			printf("string partial copy returned an error code!\n");
			exit(EXIT_FAILURE);
		} else if (ret == 0) {
			if (CFGDEBUG) {
				printf("SUCCESS: string partial copy OK!\n\n");
			}
			printf("Here is the result\n"
			       "string 1: %s\n"
			       "string 2: %s\n",
			       s1, s2);
		}
	}

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
	FLUSH;
	scanf("%" XSTR(STRMAXLEN) "[^\n]", s);
}

void getM(int *m, char *s1, char *s2)
{
	/* m cannot be greater than length of s1
	   or length of s2, whichever comes first */
	/* m cannot be greater than length of s2 */
	int s1_len = strlen(s1);
	int s2_len = strlen(s2);
	int em = 0, lim = 0;

	lim = s1_len < s2_len ? s1_len : s2_len;
	if (CFGDEBUG) {
		printf("getM lim is set to: %d\n", lim);
	}

	do {
		printf("Enter number of characters to be copied (%d chars "
		       "max) or 999 to exit: ",
		       lim);
		FLUSH;
		scanf("%d", &em);
		if (em == 999) {
			printf("Terminating as requested.\n");
			exit(EXIT_FAILURE);
		} else if (em < 0) {
			printf("m cannot be a negative number!\n");
		} else if (em > lim) {
			printf("m cannot be greater than %d chars!\n", lim);
		} else if (em > s2_len) {
			printf("m cannot be greater than length of string2 "
			       "(%d chars)!\n",
			       s2_len);
		}
	} while (em < 0 || em > lim);
	*m = em;
}

void getN(int *m, int *n, char *s1, char *s2)
{
	/* 1. n cannot be greater than length of s1 */
	/* 2. at position n, there must be m chars left in s1 */
	/* 3. n cannot be further ahead than: (s1_len - m) */
	int s1_len = strlen(s1);
	int lim;
	int en;

	/* tmp */
	char *z = s2;
	if (*z == 'x')
		;

	lim = s1_len - *m;
	if (CFGDEBUG) {
		printf("(getN) lim is set to: %d\n", lim);
	}

	do {
		printf("Enter copy begin position n (%d max) or 999 to "
		       "exit: ",
		       lim);
		FLUSH;
		scanf("%d", &en);
		if (en == 999) {
			printf("Terminating as requested.\n");
			exit(EXIT_FAILURE);
		} else if (en < 0) {
			printf("n cannot be a negative number!\n");
		} else if (en > lim) {
			printf("n cannot be greater than %d chars!\n", lim);
		}
	} while (en < 0 || en > lim);
	*n = en;
	if (CFGDEBUG) {
		printf("n is set to: %d\n", *n);
	}
}

int strPartialCopy(char *from, char *to, int *pos, int *num_chars)
{
	int r;

	if ((r = strtcpy(to, *num_chars, &from[*pos])) < 0) {
		/* error */
		printf("strtcpy error: %d", r);
		return -1;
	} else {
		if (CFGDEBUG) {
			printf("strtcpy OK\n");
		}
		return 0;
	}
}

void reportParams(int *m, int *n, char *s1, char *s2)
{
	char section[STRMAXLEN] = {0};
	int copy_len = strlen(s1) - *n;
	int r;

	/* prep 'section to be copied' string */
	if ((r = strtcpy(section, copy_len + 1, &s1[*n])) < 0) {
		/* error */
		printf("strtcpy error: %d", r);
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("strtcpy OK\n");
		}
	}
	if (CFGDEBUG) {
		printf("\nThese are the copy operation parameters:\n");
		printf("String 1: \"%s\"\n", s1);
		printf("String 2: \"%s\"\n", s2);
		printf("Number of characters to copy (m): %d\n", *m);
		printf("Begin copy operation from char (n) ID: %d\n", *n);
		printf("Section to be copied: \"%s\"\n", section);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
