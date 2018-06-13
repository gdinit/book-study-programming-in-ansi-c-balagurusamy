/* 10pe02.c */
/* ===================================80 chars=============================== */

/*
 * Modify the above program such that a function is used to input values to the
 * members and another function to display the time.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe02.c -o binary/10pe02
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
#define TITLE "TIME STRUCT WITH INPUT"
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
void displayMessageRequestInputHour(void);
void displayMessageRequestInputMinute(void);
void displayMessageRequestInputSecond(void);
void getInputHour(int *h);
void getInputMinute(int *m);
void getInputSecond(int *s);
void requestTimeOfDayInput(struct time_struct_t *t);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct time_struct_t t;
	t.h = t.m = t.s = 0;

	cls();
	displayHeaderLine();
	displayHeaderText();

	requestTimeOfDayInput(&t);
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
	printf("Entered Time is %02d:%02d:%02d\n", t->h, t->m, t->s);
}

void displayMessageRequestInputHour(void)
{
	printf("Enter the hour: ");
}

void displayMessageRequestInputMinute(void)
{
	printf("Enter the minute: ");
}

void displayMessageRequestInputSecond(void)
{
	printf("Enter the second: ");
}

void getInputHour(int *h)
{
	scanf("%d", h);
}

void getInputMinute(int *m)
{
	scanf("%d", m);
}

void getInputSecond(int *s)
{
	scanf("%d", s);
}

void requestTimeOfDayInput(struct time_struct_t *t)
{
	displayMessageRequestInputHour();
	getInputHour(&t->h);

	displayMessageRequestInputMinute();
	getInputMinute(&t->m);

	displayMessageRequestInputSecond();
	getInputSecond(&t->s);
}

/* ===================================80 chars=============================== */
/* EOF */
