/* 12pe07.c */
/* ===================================80 chars=============================== */

/*
 * Write a program that requests for a file name and an integer, known as offset
 * value. The program then reads the file starting from the location specified
 * by the offset value and prints the contents on the screen.
 *
 * Note: If the offset value is a positive integer, then printing skips that
 * many lines. If it is a negative number, it prints that many lines from the
 * end of the file. An appropriate error message should be printed, if anything
 * goes wrong.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 12pe07.c -o binary/12pe07
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
#define TITLE "PROGRAM TO READ & PRINT A FILE STARTING FROM A LINE OFFSET"
#define CFGDEBUG 1
#define SOURCE_FILENAME "source.txt"
#define BUFFER_SIZE 1024
#define MAX_LINES 4096
#define OFFSET_LINES -4

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
int create_source_file(const char *source_file);
int count_lines_in_file(const char *source_file);
int read_print_file_from_offset(const char *source_file, const int offset,
				const int lines);

/* PROGRAM ENTRY POINT */
int main(void)
{
	char source_file[] = SOURCE_FILENAME;
	int offset = OFFSET_LINES;
	int lines = 0;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	printf("/**************************************/\n");
	create_source_file(source_file);
	printf("/**************************************/\n\n");

	printf("/**************************************/\n");
	lines = count_lines_in_file(source_file);
	printf("Number of lines:\t%d\n", lines);
	printf("/**************************************/\n\n");

	printf("/**************************************/\n");
	printf("Offset has been set to:\t%d\n", offset);
	if (offset >= lines) {
		printf("\nERROR: Unable to display contents of file %s "
		       "beginning with line offset %d because the source file "
		       "has only %d lines!\n",
		       source_file, offset, lines);
		exit(EXIT_FAILURE);
	}
	read_print_file_from_offset(source_file, offset, lines);
	printf("/**************************************/\n\n");

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
int create_source_file(const char *source_file)
{
	FILE *fp;
	const char *content = "'Hope' is the thing with feathers\n"
			      "That perches in the soul\n"
			      "And sings the tune without the words\n"
			      "And never stops-at all\n"
			      "\n"
			      "And sweetest-in the Gale-is heard\n"
			      "And sore must be the storm\n"
			      "That could abash the little Bird\n"
			      "That kept so many warm\n"
			      "\n"
			      "I've heard it in the chillest land\n"
			      "And on the strangest Sea\n"
			      "Yet, never, in Extremity,\n"
			      "It asked a crumb-of Me.\n"
			      "\n"
			      "Emily Dickinson\n";

	printf("Creating/Opening file %s with w (overwrite) access mode...\n",
	       source_file);
	if ((fp = fopen(source_file, "w")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", source_file);
		return 1;
	} else {
		printf("Successfully opened file %s\n", source_file);
	}

	/*printf("Copying default content into the file %s and displaying on "
	       "screen:\n%s\n", source_file, content);*/
	printf("Copying default content into the file %s\n", source_file);
	fputs(content, fp);
	fclose(fp);
	printf("Closed file %s\n", source_file);

	printf("create_source_file() is returning 0\n");
	return 0;
}

int count_lines_in_file(const char *source_file)
{
	FILE *fp;
	int count = 0;
	char buf[BUFFER_SIZE];

	printf("Opening file %s with r (read-only) access mode...\n",
	       source_file);
	if ((fp = fopen(source_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", source_file);
		return 1;
	} else {
		printf("Successfully opened file %s\n", source_file);
	}

	while (fgets(buf, MAX_LINES, fp) != NULL) {
		count++;
	}

	fclose(fp);
	printf("Closed file %s\n", source_file);
	printf("create_source_file() is returning 0\n");
	return count;
}

int read_print_file_from_offset(const char *source_file, const int offset,
				const int lines)
{
	FILE *fp;
	int count = 0;
	int skip = 0;
	char buf[BUFFER_SIZE];

	if (lines > MAX_LINES) {
		printf("\nERROR: lines > MAX_LINES!\n");
		exit(EXIT_FAILURE);
	}

	printf("Opening file %s with r (read-only) access mode...\n",
	       source_file);
	if ((fp = fopen(source_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", source_file);
		exit(EXIT_FAILURE);
	} else {
		printf("Successfully opened file %s\n", source_file);
	}

	if (offset > 0) {
		printf(
		    "Offset is %d lines and there are %d lines in source "
		    "file therefore skipping the first %d lines and "
		    "displaying from line %d, showing a total of %d lines:\n",
		    offset, lines, offset - 1, offset, lines - offset + 1);
		while (fgets(buf, MAX_LINES, fp) != NULL) {
			count++;
			if (count >= offset) {
				puts(buf);
			}
		}
	} else if (offset < 0) {
		/* we need will to fgets-but-not-printf this many times:
		 * lines - abs(offset);
		 */
		skip = lines - abs(offset);
		printf("Offset is %d lines and there are %d lines in source "
		       "file therefore skipping %d lines and displaying last %d"
		       " lines:\n",
		       offset, lines, skip, abs(offset));
		while (count < skip) {
			if (fgets(buf, MAX_LINES, fp) != NULL) {
				count++;
			}
		}
		while (fgets(buf, MAX_LINES, fp) != NULL) {
			count++;
			if (count >= offset) {
				puts(buf);
			}
		}
	}
	fclose(fp);
	printf("Closed file %s\n", source_file);
	return 0;
}

/* ===================================80 chars=============================== */
/* EOF */
