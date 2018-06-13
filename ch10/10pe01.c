/* 10pe01.c */
/* ===================================80 chars=============================== */

/*
 * Define a structure data type called time_struct containing three members
 * integer hour, integer minute and integer second. Develop a program that would
 * assign values to the individual members and display time in the following
 * form:
 *
 *	16:40:51
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe01.c -o binary/10pe01
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "TIME STRUCT DEMO"
#define CFGDEBUG 0
#define UNKNOWN_YEAR -1
#define COMMON_YEAR 0
#define LEAP_YEAR 1

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

struct time_struct_t {
	int h;
	int m;
	int s;
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void displayTime24hFormat(struct time_struct_t *t);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct time_struct_t t;

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("\nA couple of time-of-day entries, stored in a struct, printed "
	       "via displayTime24hFormat():\n");

	t.h = 14;
	t.m = 28;
	t.s = 49;
	displayTime24hFormat(&t);

	t.h = 21;
	t.m = 38;
	t.s = 2;
	displayTime24hFormat(&t);

	t.h = 03;
	t.m = 00;
	t.s = 20;
	displayTime24hFormat(&t);

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
void displayTime24hFormat(struct time_struct_t *t)
{
	printf("Time is %02d:%02d:%02d\n", t->h, t->m, t->s);
}

/* ===================================80 chars=============================== */
/* EOF */
