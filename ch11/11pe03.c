/* 11pe03.c */
/* ===================================80 chars=============================== */

/*
 * Write a function that receives a sorted array of integers and an integer
 * value, and inserts the value in its correct place.
 */

/*
 * IMPLEMENTATION NOTES
 *
 * If array is already 'full', inserting an element will cause overflow
 * therefore when adding n extra elements, n elements from right side of array
 * will be lost.
 */
	
/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 11pe03.c -o binary/11pe03
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
#define TITLE "FUNCTION TO INSERT AN INT VALUE INTO A GIVEN SORTED INT ARRAY"
#define DB_SIZE 10
#define CFGDEBUG 0

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
void zInitEntry(int *db, int id);
void zInitAllEntries(int *db, int size);
void displayAllEntries(int *db, int size);
int cmpIntAscending(const void *v1, const void *v2);
void sortDBAscending(int db[DB_SIZE]);
int randRange(int n);
void fillDBrandomly(int db[DB_SIZE]);

/*
 * take a sorted int array *db1 & an int value; and a *db2 which must be 1 
 * element larger than *db1
 *
 * copy *db1 as *db2 but also insert value into the correct place in this array
 */
void insertSortedNewArray(int *db1, int size, int value, int *db2)
{
	int n, spot = 0;

	/* determine insertion spot */
	for (n = 0; n < size; n++) {
		if (value > *(db1 + n)) {
			spot++;
		}
	}
	if(CFGDEBUG) {
		printf("[DEBUG] Spot is: %d\n", spot);
	}

	/* copy anything up to 'spot' to db2 */
	for (n = 0; n < spot; n++) {
		db2[n] = *(db1 + n);
	}

	/* copy in the new value */
	db2[spot] = value;

	/* copy anything after 'spot' to db2 */
	for (n = spot; n < size; n++) {
		db2[n + 1] = *(db1 + n);
	}

	if (CFGDEBUG) {
		printf("[DEBUG] DB2 final:\t\t\t\t");
		for (n = 0; n < size + 1; n++) {
			printf("%2d ", db2[n]);
		}
		printf("\n");
	}
}

/* PROGRAM ENTRY POINT */
int main(void)
{
	int db1[DB_SIZE];
	int db2[DB_SIZE + 1];
	int size, value, n;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	size = sizeof(db1) / sizeof(int);
	printf("DB1 Size is: %d\n", size);

	zInitAllEntries(db1, size);
	zInitAllEntries(db2, size + 1);
	printf("DB1 Entries After Zero-initialization:\t\t");
	displayAllEntries(db1, size);

	fillDBrandomly(db1);
	printf("DB1 Entries After fillDBrandomly():\t\t");
	displayAllEntries(db1, size);

	sortDBAscending(db1);
	printf("DB1 Entries After sortDBAscending():\t\t");
	displayAllEntries(db1, size);

	srand(time(0));
	for ( n = 0; n < size * size * size * size; n++) {
		value = randRange(100);
	}	
	printf("Randomly Selected Value to Insert is:\t\t%2d\n", value);

	insertSortedNewArray(&db1[0], size, value, &db2[0]);

	printf("DB2 After insertSortedArrayInt() Execution:\t");
	displayAllEntries(db2, size + 1);

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
void zInitEntry(int *db, int id)
{
	db[id] = 0;
}

void zInitAllEntries(int *db, int size)
{
	int n;
	for (n = 0; n < size; n++) {
		zInitEntry(db, n);
	}
}

void displayAllEntries(int *db, int size)
{
	int n;
	for (n = 0; n < size; n++) {
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

/* ===================================80 chars=============================== */
/* EOF */
