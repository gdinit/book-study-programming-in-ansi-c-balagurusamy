/* 09pe20.c */
/* ===================================80 chars=============================== */

/*
 * Write a function that receives a floating point value x and returns it as a
 * value rounded to two nearest decimal places. For example, the value 123.4567
 * will be rounded to 123.46 (Hint: Seek help of one of the math functions
 * available in math library).
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe20.c -o binary/09pe20
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
#define TITLE "ROUND FLOAT TO TWO NEAREST DECIMAL PLACES"
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
void getInput(double *input);
void printRoundedToTwoDecimalPoints(double *f);
void processInput(double *f);
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
	printf("\nEnter a floating point number to get it rounded to two "
	       "nearest decimal places or 0 to quit: ");
}

void getInput(double *input)
{
	scanf("%lf", input);
}

/* 
 * This (using printf trick) is a bit of cheating but it works even in ANSI C
 * and even in Borland C 3
 */
void printRoundedToTwoDecimalPoints(double *f)
{
	printf("%.2f\n", *f);
}

void processInput(double *f)
{
	if (*f == 0.f) {
		printf("EXIT.\n\nGOODBYE!\n");
		exit(EXIT_SUCCESS);
	} else {
		printf("Entered value: %f\n", *f);
		printf("Rounded value: ");
		printRoundedToTwoDecimalPoints(f);
		printf("\n");
	}
}

void mainLoop(void)
{
	double f;

	while(1) {
		f = 0.f;
		displayMessageRequestInput();
		FLUSH
		getInput(&f);
		processInput(&f);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
