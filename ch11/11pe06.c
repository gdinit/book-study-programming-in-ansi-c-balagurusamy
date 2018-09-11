/* 11pe06.c */
/* ===================================80 chars=============================== */

/*
 * Write a function day_name that receives a number n and returns a pointer to a
 * character string containing the name of the corresponding day. The day names
 * should be kept in a static table of a character strings local to the
 * function.
 */
	
/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 11pe06.c str5cpy.c -o binary/11pe06
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "FUNCTION THAT RETURS POINTER TO DAY_NAME"
#define CFGDEBUG 0

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
const char * printDayName(int day_id);

/* PROGRAM ENTRY POINT */
int main(void)
{
	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	printf("Input = 0.\tOutput = %s\n", printDayName(0));
	printf("Input = 1.\tOutput = %s\n", printDayName(1));
	printf("Input = 2.\tOutput = %s\n", printDayName(2));
	printf("Input = 3.\tOutput = %s\n", printDayName(3));
	printf("Input = 4.\tOutput = %s\n", printDayName(4));
	printf("Input = 5.\tOutput = %s\n", printDayName(5));
	printf("Input = 6.\tOutput = %s\n", printDayName(6));
	printf("Input = 7.\tOutput = %s\n", printDayName(7));
	printf("Input = 17.\tOutput = %s\n", printDayName(17));
	printf("Input = 75.\tOutput = %s\n", printDayName(75));

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
const char * printDayName(int day_id)
{
	const char *days[] = { "Monday", "Tuesday", "Wednesday", "Thursday",
			       "Friday", "Saturday", "Sunday",
			       "ERROR: printDayName has received invalid "
			       "parameter" };

	if (day_id >= 0 && day_id <= 6) {
		return days[day_id];
	} else {
		if (CFGDEBUG) {
			printf("invalid parameter is: %d!\n", day_id);
		}
		return  days[7];
	}
}

/* ===================================80 chars=============================== */
/* EOF */
