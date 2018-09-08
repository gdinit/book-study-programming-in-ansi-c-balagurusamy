/* 12pe03.c */
/* ===================================80 chars=============================== */

/*
 * Write a program that compares two files and returns 0 if they are equal and 1
 * if they are not.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 12pe03.c -o binary/12pe03
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
#define TITLE "PROGRAM TO COMPARE 2 FILES"
#define CFGDEBUG 1
#define FILE_NAME1 "FILE1.txt"
#define FILE_NAME2 "FILE2.txt"

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
int open_compare_files(char *filename_a, char *filename_b);

/* PROGRAM ENTRY POINT */
int main(void)
{
	char file1_filename[] = FILE_NAME1;
	char file2_filename[] = FILE_NAME2;
	int ret;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	ret = open_compare_files(file1_filename, file2_filename);
	printf("\n");

	if (0 == ret) {
		printf("main() reports: '0'. The two files are IDENTICAL!\n");
	} else {
		printf(
		    "main() reports: '1'. The two files are NOT IDENTICAL!\n");
	}

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
int open_compare_files(char *filename_a, char *filename_b)
{
	FILE *fp1, *fp2;
	char ch1, ch2;
	int result;

	printf("Opening file %s read-only for comparison...\n", filename_a);
	if ((fp1 = fopen(filename_a, "r")) == NULL) {
		printf("ERROR: Cannot open file %s for comparison!\n",
		       filename_a);
		return 1;
	} else {
		printf("Successfully opened file %s for comparison\n",
		       filename_a);
	}
	printf("\n");

	printf("Opening file %s read-only for comparison...\n", filename_b);
	if ((fp2 = fopen(filename_b, "r")) == NULL) {
		printf("ERROR: Cannot open file %s for comparison!\n",
		       filename_b);
		return 1;
	} else {
		printf("Successfully opened file %s for comparison\n",
		       filename_b);
	}
	printf("\n");

	do {
		ch1 = getc(fp1);
		ch2 = getc(fp2);
		printf("ch1 is:\t%c\n", ch1);
		printf("ch2 is:\t%c\t", ch2);
		if (ch1 == ch2) {
			result = 0;
			printf(" <-- chars are equal.\n");
		} else {
			result = 1;
			printf(" <-- chars are NOT equal.\n"
			       "open_compare_files() is returning 1\n");
			return 1;
		}
	} while ((ch1 != EOF) && (ch2 != EOF));

	printf("\n");
	fclose(fp1);
	printf("Closed file %s\n", filename_a);
	fclose(fp2);
	printf("Closed file %s\n", filename_b);

	printf("open_compare_files() is returning 0\n");
	return 0;
}

/* ===================================80 chars=============================== */
/* EOF */
