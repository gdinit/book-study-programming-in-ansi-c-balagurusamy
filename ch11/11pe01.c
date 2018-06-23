/* 11pe01.c */
/* ===================================80 chars=============================== */

/*
 * Write a program using pointers to read in an array of integers and print its
 * elements in reverse order.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 11pe01.c -o binary/11pe01
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
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
#define TITLE "READ & SORT INT ARRAY"
#define CFGDEBUG 0
#define DB_SIZE 10

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
void zInitEntry(int db[DB_SIZE], int id);
void zInitAllEntries(int db[DB_SIZE]);
void displayAllEntries(int db[DB_SIZE]);
int cmpIntAscending(const void *v1, const void *v2);
void sortDBAscending(int db[DB_SIZE]);
int randRange(int n);
void fillDBrandomly(int db[DB_SIZE]);
void displayAllEntriesReversed(int db[DB_SIZE]);

/* PROGRAM ENTRY POINT */
int main(void)
{
	int db[DB_SIZE];

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	zInitAllEntries(db);
	printf("Entries after zInit:\t\t\t\t");
	displayAllEntries(db);

	fillDBrandomly(db);
	printf("Entries after fillDBrandomly():\t\t\t");
	displayAllEntries(db);

	sortDBAscending(db);
	printf("Entries after sortDBAscending():\t\t");
	displayAllEntries(db);

	printf("Entries with displayAllEntriesReversed():\t");
	displayAllEntriesReversed(db);

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
void zInitEntry(int db[DB_SIZE], int id)
{
	db[id] = 0;
}

void zInitAllEntries(int db[DB_SIZE])
{
	int n;
	for (n = 0; n < DB_SIZE; n++) {
		zInitEntry(db, n);
	}
}

void displayAllEntries(int db[DB_SIZE])
{
	int n;
	for (n = 0; n < DB_SIZE; n++) {
		printf("%2d ", db[n]);
	}
	printf("\n");
}

int cmpIntAscending(const void *v1, const void *v2)
{
	const int *p1 = (int *)v1;
	const int *p2 = (int *)v2;
	if (*p1 < *p2) {
		return -1;
	} else if (*p1 > *p2) {
		return +1;
	} else {
		return 0;
	}
}

void sortDBAscending(int db[DB_SIZE])
{
	qsort(db, DB_SIZE, sizeof(int), cmpIntAscending);
}

int randRange(int n)
{
	int r;
	int limit;

	limit = RAND_MAX - (RAND_MAX % n);
	while ((r = rand()) >= limit) {
		/* nothing */
	}

	return r % n;
}

/* fill a db with randomly generated numbers */
void fillDBrandomly(int db[DB_SIZE])
{
	int n, r;
	static int rand_seeded = 0;

	if (!rand_seeded) {
		srand(time(0));
		rand_seeded++;
		if (CFGDEBUG) {
			printf("[DEBUG] rand: seeded!\n");
		}
	} else {
		if (CFGDEBUG) {
			printf("[DEBUG] rand: no need to seed\n");
		}
	}
	for (n = 0; n < DB_SIZE; n++) {
		r = randRange(100);
		db[n] = r;
	}
}

void displayAllEntriesReversed(int db[DB_SIZE])
{
	int n;

	for (n = DB_SIZE - 1; n >= 0; n--) {
		printf("%2d ", db[n]);
	}
	printf("\n");
}

/* ===================================80 chars=============================== */
/* EOF */
