/* 12pe04.c */
/* ===================================80 chars=============================== */

/*
 * Write a program that appends one file at the end of another.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 12pe04.c -o binary/12pe04
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
#define TITLE "PROGRAM TO APPEND A FILE AT THE END OF ANOTHER"
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
int open_files_append_to_first(char *filename_a, char *filename_b);

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

	ret = open_files_append_to_first(file1_filename, file2_filename);
	printf("\n");

	if (0 == ret) {
		printf("main() reports: '0'. Append operation SUCCESSFULL!\n");
	} else {
		printf("main() reports: '1'. Append operation FAILED!\n");
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
int open_files_append_to_first(char *filename_a, char *filename_b)
{
	FILE *fp1, *fp2;
	char ch2;

	printf("Opening file %s with r (read) access mode\n", filename_b);
	if ((fp2 = fopen(filename_b, "r")) == NULL) {
		printf("ERROR: Cannot open file %s for reading!\n", filename_b);
		return 1;
	} else {
		printf("Successfully opened file %s for reading\n", filename_b);
	}
	printf("\n");

	printf("Opening file %s with a (append) access mode...\n", filename_a);
	if ((fp1 = fopen(filename_a, "a")) == NULL) {
		printf("ERROR: Cannot open file %s for append operation!\n",
		       filename_a);
		return 1;
	} else {
		printf("Successfully opened file %s for append operation\n",
		       filename_a);
	}
	printf("\n");

	do {
		ch2 = getc(fp2);
		printf("ch2 is:\t%c\n", ch2);
		putc(ch2, fp1);
	} while (ch2 != EOF);

	printf("\n");
	fclose(fp1);
	printf("Closed file %s\n", filename_a);
	fclose(fp2);
	printf("Closed file %s\n", filename_b);

	printf("open_files_append_to_first() is returning 0\n");
	return 0;
}

/* ===================================80 chars=============================== */
/* EOF */
