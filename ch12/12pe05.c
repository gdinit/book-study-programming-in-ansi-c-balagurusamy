/* 12pe05.c */
/* ===================================80 chars=============================== */

/*
 * Write a program that reads a filename containing integers and appends at its
 * end the sum of all the integers.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 12pe05.c -o binary/12pe05
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort(), atoi()) */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "PROGRAM TO READ INTS FROM A FILE AND CALCULATE SUM OF ALL"
#define CFGDEBUG 1
#define FILENAME "integers.txt"

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

#ifdef __APPLE__
#define XPUTW putw
#define XGETW getw
#elif __BORLANDC__
#define XPUTW putw
#define XGETW getw
#else
#define XPUTW _putw
#define XGETW _getw
#endif

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
int create_integers_file(char *filename);
int open_file_read_and_sum_ints(char *filename);

/* PROGRAM ENTRY POINT */
int main(void)
{
	char filename[] = FILENAME;
	int sum = 0;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	create_integers_file(filename);
	sum = open_file_read_and_sum_ints(filename);
	printf("\nsum is:\t%d\n", sum);

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
int create_integers_file(char *filename)
{
	FILE *fp;
	int n = 2;

	printf("Opening file %s with w (overwrite) access mode...\n", filename);
	if ((fp = fopen(filename, "w")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", filename);
		return 1;
	} else {
		printf("Successfully opened file %s\n", filename);
	}

	printf("Writing numbers to the file %s and displaying on screen:\t",
	       filename);
	for (; n < 10; n += 2) {
		XPUTW(n, fp);
		printf(" %d", n);
	}
	fclose(fp);
	printf("\nClosed file %s\n", filename);

	printf("create_integers_file() is returning 0\n");
	return 0;
}

int open_file_read_and_sum_ints(char *filename)
{
	FILE *fp;
	int sum = 0;
	int n = 0;

	printf("\nOpening file %s with r (read) access mode...\n", filename);
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("ERROR: Cannot open file %s for reading!\n", filename);
		return 1;
	} else {
		printf("Successfully opened file %s for reading\n", filename);
	}

	printf("Reading numbers from file %s and displaying on screen:\t",
	       filename);
	while ((n = XGETW(fp)) != EOF) {
		printf(" %d", n);
		sum += n;
	}
	fclose(fp);
	printf("\nClosed file %s\n", filename);

	printf("open_file_read_and_sum_ints() is returning 0\n");
	return sum;
}

/* ===================================80 chars=============================== */
/* EOF */
