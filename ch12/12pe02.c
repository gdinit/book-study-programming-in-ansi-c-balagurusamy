/* 12pe02.c */
/* ===================================80 chars=============================== */

/*
 * Two files DATA1 and DATA2 contain sorted lists of integers. Write a program
 * to produce a third file DATA which holds a single sorted, merged lists of
 * these two lists. Use command line arguments to specify file names.
 */

/* TODO
   -replace XGETW and XPUTW with something supported by C standard
    perhaps fread/fwrite?
*/

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 12pe02.c -o binary/12pe02
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
#define TITLE "READ 2 SORTED INTEGER ARRAYS FROM FILE AND CREATE A NEW MERGED "\
	      "SORTED FILE"
#define CFGDEBUG 1
#define DATA1_FILENAME "DATA1.bin" /* Write file with odd numbers */
#define DATA2_FILENAME "DATA2.bin" /* Write file with even numbers */
#define DATA3_FILENAME "DATA3.bin" /* Combine files 1 & 2 into this */
#define BUFFER_SIZE 80
#define NUM_ENTRIES 80
#define COLUMNS 10

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
void bubble_sort_asc_int(int list[], int n);
void create_file_data_1(void);
void create_file_data_2(void);
void create_file_data_3(int arr[NUM_ENTRIES]);
void read_display_file_data_1(void);
void read_display_file_data_2(void);
void read_display_file_data_3(void);
int read_file_data1_into_memory(int arr[NUM_ENTRIES]);
void read_file_data2_into_memory(int arr[NUM_ENTRIES], int next_slot);
void init_array(int arr[NUM_ENTRIES]);
void display_array(int arr[NUM_ENTRIES]);

/* PROGRAM ENTRY POINT */
int main(void)
{
	int arr[NUM_ENTRIES];
	int next_slot;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	printf("========================================\n");
	init_array(arr);
	display_array(arr);
	create_file_data_1();
	create_file_data_2();
	printf("========================================\n\n");

	printf("========================================\n");
	next_slot = read_file_data1_into_memory(arr);
	read_file_data2_into_memory(arr, next_slot);
	
	display_array(arr);
	printf("sorting array...\n");
	bubble_sort_asc_int(arr, NUM_ENTRIES);
	display_array(arr);
	printf("========================================\n\n");

	printf("========================================\n");
	create_file_data_3(arr);
	printf("========================================\n");
	printf("\n");

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
void create_file_data_1(void)
{
	FILE *fp1;
	int n;

	fp1 = fopen(DATA1_FILENAME, "wb");
	printf("\nOpened file DATA1 to write\n");
	printf("Writing numbers:\t\t\t\t\t");
	for (n = 1; n < 10; n+=2) {
		XPUTW(n, fp1);
		printf(" %d", n);
	}
	printf("\n");
	fclose(fp1);
	printf("Closed file DATA1\n\n");
}

void create_file_data_2(void)
{
	FILE *fp2;
	int n;

	fp2 = fopen(DATA2_FILENAME, "wb");
	printf("Opened file DATA2 to write\n");
	printf("Writing numbers:\t\t\t\t\t");
	for (n = 2; n <= 10; n+=2) {
		XPUTW(n, fp2);
		printf(" %d", n);
	}
	printf("\n");
	fclose(fp2);
	printf("Closed file DATA2\n");
}

void create_file_data_3(int arr[NUM_ENTRIES])
{
	FILE *fp3;
	int n;

	fp3 = fopen(DATA3_FILENAME, "wb");
	printf("Opened file DATA3 to write\n");
	printf("Writing numbers stored in memory to the file DATA3:\t");
	for (n = 0; n < NUM_ENTRIES; n++) {
		/* simply ignore empty slots (which are set to -1) */
		if(arr[n] != -1) {
			XPUTW(arr[n], fp3);
			printf(" %2d", arr[n]);
		}
	}
	printf("\n");
	fclose(fp3);
	printf("Closed file DATA3\n\n");
}

void read_display_file_data_1(void)
{
	FILE *fp1;
	int n;

	fp1 = fopen(DATA1_FILENAME, "rb");
	printf("Opened file DATA1 to read\n");
	printf("Reading numbers from file DATA1 and displaying on screen:\t");
	while ((n = XGETW(fp1)) != EOF) {
		printf(" %d", n);
	}
	fclose(fp1);
	printf("Closed file DATA1\n\n");
}

void read_display_file_data_2(void)
{
	FILE *fp2;
	int n;

	fp2 = fopen(DATA2_FILENAME, "rb");
	printf("Opened file DATA2\n");
	printf("Reading numbers from file DATA2 and displaying on screen:\t");
	while ((n = XGETW(fp2)) != EOF) {
		printf(" %d", n);
	}
	fclose(fp2);
	printf("Closed file DATA2\n");
}

void read_display_file_data_3(void)
{
	FILE *fp3;
	int n;

	fp3 = fopen(DATA3_FILENAME, "rb");
	printf("Opened file DATA3\n");
	printf("Reading numbers from file DATA3 and displaying on screen:\t");
	while ((n = XGETW(fp3)) != EOF) {
		printf(" %d", n);
	}
	fclose(fp3);
	printf("\n");
	printf("Closed file DATA3\n\n");
}

int read_file_data1_into_memory(int arr[NUM_ENTRIES])
{
	FILE *fp1;
	int n, next_slot, entries;

	fp1 = fopen(DATA1_FILENAME, "rb");
	printf("Opened file DATA1 to read\n");
	printf("Reading numbers from file DATA1 and storing in memory:\t");
	entries = next_slot = 0;
	while ((n = XGETW(fp1)) != EOF) {
		printf(" %d", n);
		arr[next_slot] = n;
		next_slot++;
		entries++;
	}
	printf("\n");
	fclose(fp1);
	printf("Closed file DATA1\n\n");

	return next_slot;
}

void read_file_data2_into_memory(int arr[NUM_ENTRIES], int next_slot)
{
	FILE *fp2;
	int n;

	printf("next_slot has been reported to read_fdata2() as:\t%2d\n\n",
	       next_slot);
	fp2 = fopen(DATA2_FILENAME, "rb");
	printf("Opened file DATA2 to read\n");
	printf("Reading numbers from file DATA2 and storing in memory:\t");
	while ((n = XGETW(fp2)) != EOF) {
		printf(" %d", n);
		arr[next_slot] = n;
		next_slot++;
	}
	printf("\n");
	fclose(fp2);
	printf("Closed file DATA2\n\n");
}

void init_array(int arr[NUM_ENTRIES])
{
	int n;
	for (n = 0; n < NUM_ENTRIES; n++) {
		/* -1 = slot not in use */
		arr[n] = -1;
	}
}

void display_array(int arr[NUM_ENTRIES])
{
	int n;
	printf("Numbers in array in memory:\t\t\t\t");
	n = 1;
	do {
		if (arr[n - 1] >= 0) {
			printf(" %d", arr[n - 1]);
			if (n % COLUMNS == 0) {
				printf("\n");
			} else {
				printf(" ");
			}
		}
		n++;
	} while (n <= NUM_ENTRIES);
	/*printf("\n");*/
}

/* ===================================80 chars=============================== */
/* EOF */
