/* 09pe16.c */
/* ===================================80 chars=============================== */

/*
 * Write a program that invokes a function called find() to perform the
 * following tasks:
 *
 * (a) Receives a character array and a single character.
 * (b) Returns 1 if the specified character is found in the array, 0 otherwise.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe16.c -o binary/09pe16
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
#define TITLE "FIND() A CHARACTER IN A CHARACTER ARRAY"
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
unsigned int myFind(const char *array, const char c);

/* PROGRAM ENTRY POINT */
int main(void)
{
	int r;
	char s1[STRING_MAX_SIZE] = "This is just a test string...";

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("\nSTRING\n");
	printf("   s1: %s\n\n", s1);

	r = myFind(s1, 'a');
	printf("   `myFind(s1, a)`...\tResult is: %u\n", r);

	r = myFind(s1, 'b');
	printf("   `myFind(s1, b)`...\tResult is: %u\n", r);

	r = myFind(s1, 's');
	printf("   `myFind(s1, s)`...\tResult is: %u\n", r);

	r = myFind(s1, 'x');
	printf("   `myFind(s1, x)`...\tResult is: %u\n", r);

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
unsigned int myFind(const char *array, const char c)
{
	int r = NOTFOUND;
	int n;

	for (n = 0; array[n] != '\0'; n++) {
		if(array[n] == c) {
			r = FOUND;
			break;
		}
	}
	return r;
}

/* ===================================80 chars=============================== */
/* EOF */
