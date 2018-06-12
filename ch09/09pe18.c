/* 09pe18.c */
/* ===================================80 chars=============================== */

/*
 * Write a function that takes an integer parameter m representing the month
 * number of the year and returns the corresponding name of the month.
 * For instance, if m = 3, the month is March.
 * Test your program.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe18.c -o binary/09pe18
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
#define TITLE "A FUNCTION THAT TAKES AN INT & DISPLAYS A MONTH"
#define CFGDEBUG 0
#define STRING_MAX_SIZE 128
#define NOTFOUND 0
#define FOUND 1

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

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void displayMessageRequestInput(void);
void getInput(int *choice);
void processInput(int *m);
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
	printf("\nEnter number (1-12) to get corresponding month or 0 to quit: ");
}

void getInput(int *choice)
{
	scanf("%d", choice);
}

void processInput(int *m)
{
	printf("You have chosen: ");
	switch(*m)
	{
		case 0:
			printf("EXIT.\n\nGOODBYE!\n");
			exit(EXIT_SUCCESS);
		case 1:
			printf("January.\n");
			break;
		case 2:
			printf("February.\n");
			break;
		case 3:
			printf("March.\n");
			break;
		case 4:
			printf("April.\n");
			break;
		case 5:
			printf("May.\n");
			break;
		case 6:
			printf("June.\n");
			break;
		case 7:
			printf("July.\n");
			break;
		case 8:
			printf("August.\n");
			break;
		case 9:
			printf("September.\n");
			break;
		case 10:
			printf("October.\n");
			break;
		case 11:
			printf("November.\n");
			break;
		case 12:
			printf("December.\n");
			break;
		default:
			printf("INVALID MONTH ENTRY\n");
	}

}

void mainLoop(void)
{
	int m;

	while(1) {
		m = 0;
		displayMessageRequestInput();
		FLUSH
		getInput(&m);
		processInput(&m);
	}
}


/* ===================================80 chars=============================== */
/* EOF */
