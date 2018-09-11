/* 09pe17.c */
/* ===================================80 chars=============================== */

/*
 * Design a function locate() that takes two character arrays s1 and s2 and one
 * integer value m as parameters and inserts the string s2 into s1 immediately
 * after the index m.
 * 
 * Write a program to test the function using a real-life situation. (Hint: s2
 * may be a missing word in s1 that represents a line of text).
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe17.c -o binary/09pe17
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <math.h> /* ceil() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */
#include <time.h>   /* srand(time()) */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "A FUNCTION CALLED LOCATE BUT ACTUALLY SHOULD BE CALLED INSERT AT\
 POSITION"
#define CFGDEBUG 0
#define STRING_MAX_SIZE 128
#define NOTFOUND 0
#define FOUND 1

/* BEGIN: FLUSH rev.03 */
#ifdef _WIN32
#define FLUSH fflush(stdin);
/*#elif defined __unix__
#define FLUSH fpurge(stdin);*/
#elif defined __APPLE__
#define FLUSH fpurge(stdin);
#elif defined __gnu_linux__
#include <stdio_ext.h>
#define FLUSH __fpurge(stdin);
#else
#define FLUSH fflush(stdin);
#endif
/* END: FLUSH rev.03 */

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void locate(char *target, const char *source, const unsigned int m);

/* PROGRAM ENTRY POINT */
int main(void)
{
	char s1[STRING_MAX_SIZE] = "To be, that is the question.";
	const char s2[STRING_MAX_SIZE] = "or not to be, ";
	const m = 7;

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("\nINITIAL STRINGS and m\n");
	printf("   s1: %s\n"
	       "   s2: %s\n"
	       "    m: %d\n"
	       , s1, s2, m);

	locate(s1, s2, m);

	printf("\nFINAL STRING\n");
	printf("   s1: %s\n", s1);

	displayFooter();

	return EXIT_SUCCESS;
}
/**************************************/
void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeaderLine(void)
{
	int n;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}

void displayHeaderText(void)
{
	char s[] = TITLE;
	printf("%s\n", s);
}

void displayFooter(void)
{
	int n = 0;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}
/**************************************/
void locate(char *target, const char *source, const unsigned int m)
{
	char tmp[STRING_MAX_SIZE] = "";
	int si = 0; /* source index */
	int ti = m; /* target index */
	int n;
	unsigned int slen = strlen(source);

	/* first back up any chars after position m */
	for (n = 0; target[m + n] != '\0'; n++) {
		tmp[n] = target[m + n];
	}

	/* insert and overwrite anything after m */
	for ( ; source[si] != '\0'; si++) {
		target[ti] = source[si];
		ti++;
	}

	/* copy back anything after m */
	for (n = 0; tmp[n] != '\0'; n++) {
		target[m + slen + n] = tmp[n];
	}
}

/* ===================================80 chars=============================== */
/* EOF */
