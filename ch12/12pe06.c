/* 12pe06.c */
/* ===================================80 chars=============================== */

/*
 * Write a program that prompts the user for two files, one containing a line of
 * text known as source file and other, an empty file knows as target file and
 * then copies the contents of source file into target file.
 *
 * Modify the program so that a specified character is deleted from the source
 * file as it is copied to the target file.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 12pe06.c -o binary/12pe06
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
#define SOURCE_FILENAME "source.txt"
#define TARGET_FILENAME1 "target1.txt"
#define TARGET_FILENAME2 "target2.txt"

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
int create_source_file(char *source_file);
int copy_identical(char *source_file, char *target_file1);
int copy_i_removed(char *source_file, char *target_file1);

/* PROGRAM ENTRY POINT */
int main(void)
{
	char source_file[] = SOURCE_FILENAME;
	char target_file1[] = TARGET_FILENAME1;
	char target_file2[] = TARGET_FILENAME2;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	printf("/**************************************/\n");
	create_source_file(source_file);
	printf("/**************************************/\n\n");

	printf("/**************************************/\n");
	copy_identical(source_file, target_file1);
	printf("/**************************************/\n\n");

	printf("/**************************************/\n");
	copy_i_removed(source_file, target_file2);
	printf("/**************************************/\n");

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
int create_source_file(char *source_file)
{
	FILE *fp;
	const char *content = "This is the content of source file 123.";

	printf("Creating/Opening file %s with w (overwrite) access mode...\n",
	       source_file);
	if ((fp = fopen(source_file, "w")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", source_file);
		return 1;
	} else {
		printf("Successfully opened file %s\n", source_file);
	}

	printf("Copying default content into the file %s and displaying on "
	       "screen:\t%s\n",
	       source_file, content);
	fputs(content, fp);
	fclose(fp);
	printf("Closed file %s\n", source_file);

	printf("create_source_file() is returning 0\n");
	return 0;
}

int copy_identical(char *source_file, char *target_file1)
{
	FILE *fps, *fpt;
	char ch;
	int r = 0; /* read char count */
	int w = 0; /* written char count */

	printf("Opening file %s with r (read) access mode...\n", source_file);
	if ((fps = fopen(source_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s for reading!\n",
		       source_file);
		return 1;
	} else {
		printf("Successfully opened file %s for reading\n",
		       source_file);
	}
	printf("Reading numbers from file %s and displaying on screen:\t",
	       source_file);

	printf("\nOpening file %s with w (overwrite) access mode...\n",
	       target_file1);
	if ((fpt = fopen(target_file1, "w")) == NULL) {
		printf("ERROR: Cannot open file %s for reading!\n",
		       target_file1);
		return 1;
	} else {
		printf("Successfully opened file %s for writing\n",
		       target_file1);
	}

	printf("Reading characters from file %s, displaying on screen and "
	       "writing to file %s:\n",
	       source_file, target_file1);
	do {
		ch = getc(fps);
		r++;
		printf("ch is:\t%c\n", ch);
		putc(ch, fpt);
		w++;
	} while (ch != EOF);

	printf("Read char count:\t%d\tWritten char count:\t%d\n", r, w);

	fclose(fps);
	printf("\nClosed file %s\n", source_file);

	fclose(fpt);
	printf("Closed file %s\n", target_file1);

	printf("copy_identical() is returning 0\n");
	return 0;
}

/*
 * copy source_file to target_file1
 * but for inexplicable reasons, do NOT copy any instance of character 'i'!
 */
int copy_i_removed(char *source_file, char *target_file1)
{
	FILE *fps, *fpt;
	char ch;
	int r = 0; /* read char count */
	int w = 0; /* written char count */

	printf("Opening file %s with r (read) access mode...\n", source_file);
	if ((fps = fopen(source_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s for reading!\n",
		       source_file);
		return 1;
	} else {
		printf("Successfully opened file %s for reading\n",
		       source_file);
	}
	printf("Reading numbers from file %s and displaying on screen:\t",
	       source_file);

	printf("\nOpening file %s with w (overwrite) access mode...\n",
	       target_file1);
	if ((fpt = fopen(target_file1, "w")) == NULL) {
		printf("ERROR: Cannot open file %s for reading!\n",
		       target_file1);
		return 1;
	} else {
		printf("Successfully opened file %s for writing\n",
		       target_file1);
	}

	printf("Reading characters from file %s, displaying on screen and "
	       "writing to file %s:\n",
	       source_file, target_file1);
	do {
		ch = getc(fps);
		r++;
		printf("ch is:\t%c\n", ch);
		if (ch != 'i') {
			putc(ch, fpt);
			w++;
		}
	} while (ch != EOF);

	printf("Read char count:\t%d\tWritten char count:\t%d\n", r, w);

	fclose(fps);
	printf("\nClosed file %s\n", source_file);

	fclose(fpt);
	printf("Closed file %s\n", target_file1);

	printf("copy_identical() is returning 0\n");
	return 0;
}

/* ===================================80 chars=============================== */
/* EOF */
