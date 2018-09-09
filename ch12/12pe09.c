/* 12pe09.c */
/* ===================================80 chars=============================== */

/*
 * Write a program to read the file created in Exercise 12.8 and compute and
 * print the total value of all the five products.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 12pe09.c -o binary/12pe09
 */

/**
 * KNOWN ISSUES & IMPROVEMENT IDEAS: see main program 12pe08
 **/

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
#define TITLE "STORE PRODUCT MANAGEMENT"
#define CFGDEBUG 0
#define MAIN_DATABASE_FILENAME "db_main.bin"
#define PRODUCT_LINE_MAX_SIZE 1024
#define FIELD_SIZE 32
#define MAX_LINES 4096
#define MENU_ENTRY_LOWEST 1
#define MENU_ENTRY_HIGHEST 5
#define CLS_MINI_SIZE 5 /* used in display_main_menu() to push up text  */

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
int count_lines_in_file(const char *db_main_file);
int test_main_db(const char *db_main_file);
double grand_total(const char *db_main_file);

/* PROGRAM ENTRY POINT */
int main(void)
{
	const char db_main_file[] = MAIN_DATABASE_FILENAME;
	int ret = -1;

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("\n");
	ret = test_main_db(db_main_file);
	if (0 == ret) {
		/* main DB exists & can be opened for read-write access*/
		printf("MainDB exists & can be accessed in read-write mode. Not"
		       " creating the default database\n");
	} else {
		printf("ERROR: Cannot open db file %s!\n", db_main_file);
		exit(EXIT_FAILURE);
	}
	printf("\nTotal Value of all %d products in the database is:  %.2f\n", 
	       count_lines_in_file(db_main_file),
	       grand_total(db_main_file));

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
int count_lines_in_file(const char *db_main_file)
{
	FILE *fp_maindb;
	int count = 0;
	char buf[PRODUCT_LINE_MAX_SIZE];

	if (CFGDEBUG) {
		printf("Opening file %s with r (read-only) access mode...\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		return 1;
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
	}

	while (fgets(buf, MAX_LINES, fp_maindb) != NULL) {
		count++;
	}
	fclose(fp_maindb);
	printf("Found %d products in the database...\n", count);
	if (CFGDEBUG) {
		printf("Closed file %s\n", db_main_file);
	}
	return count;
}

/**
 * RETURN CODES
 *
 *  0 = main DB exists & can be opened for read-write access
 * -1 = main DB either does not exist or read-write access cannot be obtained
 **/
int test_main_db(const char *db_main_file)
{
	FILE *fp_maindb;

	/* attempt opening file for read-write access */
	if (CFGDEBUG) {
		printf("Opening file %s with r+ (read-write) access mode..."
		       "\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r+")) == NULL) {
		if (CFGDEBUG) {
			printf("ERROR: Cannot open file %s!\n", db_main_file);
		}
		return -1;
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
		fclose(fp_maindb);
		if (CFGDEBUG) {
			printf("Closed file %s\n\n", db_main_file);
		}
		return 0;
	}
}

double grand_total(const char *db_main_file)
{
	FILE *fp_maindb;
	char buf[PRODUCT_LINE_MAX_SIZE];
	int id = -1;
	char product_code[FIELD_SIZE] = "";
	char product_desc[FIELD_SIZE] = "";
	double price = 0.f;
	char *p_product_code = &product_code[0];
	char *p_product_desc = &product_desc[0];
	double *p_price = &price;
	double sum = 0.f;

	/* open file for read-only access */
	if (CFGDEBUG) {
		printf("Opening file %s with r (read-only) access mode...\n",
		       db_main_file);
	}
	if ((fp_maindb = fopen(db_main_file, "r")) == NULL) {
		printf("ERROR: Cannot open file %s!\n", db_main_file);
		printf("This program requires a valid database from 12pe08 "
		       "program.");
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("Successfully opened file %s\n", db_main_file);
		}
	}

	/* loop: read a line, add its price to grand_total */
	while (fgets(buf, sizeof(buf), fp_maindb) != NULL) {
		/* read a line into buffer & break apart to tokens */
		/*
		1	|WG01	|Water Glass	|499	<-- a DB line
		%[^|]	|%[^|]	|%[^|]		|%[^|]	<-- sscanf format
		%[^|]|%[^|]|%[^|]|%[^|]			<-- sscanf merged
		*/
		sscanf(buf, "%d|%31[^|]|%31[^|]|%31lf", &id, p_product_code,
		       p_product_desc, p_price);
		if (CFGDEBUG) {
			printf("-----------------------------------------------"
			       "---------------------------------\n");
			printf("%d\n", id);
			printf("%s\n", product_code);
			printf("%s\n", product_desc);
			printf("%f\n", price);
		}
		sum += price;
		if (CFGDEBUG) {
			printf("Price to add is:\t%f\nGrand Total is:\t\t%f\n",
			       price, sum);
		}
	}
	fclose(fp_maindb);
	return sum;
}

/* ===================================80 chars=============================== */
/* EOF */
