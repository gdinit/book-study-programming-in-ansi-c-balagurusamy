/* 09pe19.c */
/* ===================================80 chars=============================== */

/*
 * In preparing the calendar for a year we need to know whether that particular
 * year is leap year or not. Design a leap() that receives the year as a 
 * parameter and returns an appropriate message.
 *
 * What modifications are required if we want to use the function in preparing
 * the actual calendar?
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe19.c -o binary/09pe19
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
#define TITLE "LEAP YEAR vs COMMON YEAR DETECTOR"
#define CFGDEBUG 0
#define UNKNOWN_YEAR -1
#define COMMON_YEAR 0
#define LEAP_YEAR 1

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
void displayMessageRequestInput(void);
void getInput(int *choice);
int leap(int year);
void processInput(int *y);
void mainLoop(void);

/* PROGRAM ENTRY POINT */
int main(void)
{
	cls();
	displayHeaderLine();
	displayHeaderText();
	mainLoop();
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
void displayMessageRequestInput(void)
{
	printf("\nEnter a year between 1760 - 2276 to find out whether that was"
	       " a leap year or 0 to quit: ");
}

void getInput(int *choice)
{
	scanf("%d", choice);
}

int leap(int year)
{
	int r = UNKNOWN_YEAR;

	if (year % 4 != 0) {
		printf("%d is a COMMON YEAR\n", year);
		r = COMMON_YEAR;
	} else if (year % 100 != 0) {
		printf("%d is a LEAP YEAR\n", year);
		r = LEAP_YEAR;
	} else if (year % 400 != 0) {
		printf("%d is a COMMON YEAR\n", year);
		r = COMMON_YEAR;
	} else {
		printf("%d is a LEAP YEAR\n", year);
		r = LEAP_YEAR;
	}

	return r;
}

void processInput(int *y)
{
	if (*y == 0) {
		printf("EXITING ON REQUEST.\nGOODBYE!\n");
		exit(EXIT_SUCCESS);
	} else if (*y < 1760 || *y > 2276) {
		printf("Year cannot be less than 1760 or greater than 2276! "
		       "(year chosen=%d)\n", *y);
		return;
	} else {
		leap(*y);
	}
}

void mainLoop(void)
{
	int y;

	while(1) {
		y = 0;
		displayMessageRequestInput();
		FLUSH
		getInput(&y);
		processInput(&y);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
