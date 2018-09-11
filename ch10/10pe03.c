/* 10pe03.c */
/* ===================================80 chars=============================== */

/*
 * Design a function update that would accept the data structure designed in
 * Exercise 10.1 and increments time by one second and returns the new time. (If
 * the increment results in 60 seconds, then the second member is set to zero
 * and the minute member is incremented by one. Then, if the result is 60
 * minutes, the minute member is set to zero and the hour member is incremented
 * by one. Finally when the hour becomes 24, it is set to zero.)
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe03.c -o binary/10pe03
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
#define TITLE "TIME STRUCT WITH INPUT AND UPDATE()"
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
void addSecond(struct time_struct_t *t);
void shiftTimeIfNecessary(struct time_struct_t *t);
void update(struct time_struct_t *t);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct time_struct_t t;
	t.h = t.m = t.s = 0;

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("Days are not implemented; 25th hour will show as 01 hour!\n");
	requestTimeOfDayInput(&t);
	displayTime24hFormat(&t);

	update(&t);
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

void addSecond(struct time_struct_t *t)
{
	t->s++;
}

void shiftTimeIfNecessary(struct time_struct_t *t)
{
	/* seconds */
	for ( ; t->s > 60; t->s -= 60) { /* shave seconds */
		t->m++;
	}
	if (t->s == 60) { /* cleanup seconds */
		t->m++;
		t->s = 0;
	}

	/* minutes */
	for ( ; t->m > 60; t->m -= 60) { /* shave minutes */
		t->h++;
	}
	if (t->m == 60) { /* cleanup minutes */
		t->h++;
		t->m = 0;
	}

	/* hours */
	for ( ; t->h > 24; t->h -= 24) { /* shave hours */
		/* TODO add day increment here... */
	}
	if (t->h == 24) { /* cleanup hours */
		/* TODO add day increment here... */
		t->h = 0;
	}
}

void update(struct time_struct_t *t)
{
	addSecond(t);
	shiftTimeIfNecessary(t);
}

/* ===================================80 chars=============================== */
/* EOF */
