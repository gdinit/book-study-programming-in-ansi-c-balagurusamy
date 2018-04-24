/* 05pe07.c */

/* ===================================80 chars=============================== */

/*
Show below is a Floyd's triangle.

 1
 2  3
 4  5  6
 7  8  9 10
11 .. .. .. 15
.
.
79 .................91

(a) Write a program to print this triangle.
(b) Modify the program to produce the following form of Floyd's triangle:

1
0 1
1 0 1
0 1 0 1
1 0 1 0 1
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
Required to prevent -> "scanf: floating point formats not linked
"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

/* CONFIGURATION */
#define TITLE "FLOYD'S TRIANGLE"
#define LINESTOCLEARSCREEN 90
#define MAX_LINES 14

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printHeader(void)
{
	char s[] = TITLE;
	int tmp = 0;
	for (tmp = 0; tmp < 66; tmp++) {
		printf("-");
	}
	printf("\n%s\n", s);
}

void printFooter(void)
{
	int tmp = 0;
	for (tmp = 0; tmp < 66; tmp++) {
		printf("-");
	}
	printf("\n");
}

void printTable(void)
{
	int line = 0, colw = 0, j = 1, n = 1;

	for (line = 0; line < MAX_LINES; (++line, ++colw)) {
		for (j = 0; j < colw; (j++, n++)) {
			printf("%d ", n);
		}
		printf("\n");
	}
}

void printTable2(void)
{
	/* last "first character of line" */
	int line = 1, colw = 1, j = 0, n = 0, lfc = 0;

	printf("\n");
	for (line = 1; line < MAX_LINES; (line++, colw++)) {
		n = lfc = !lfc;
		for (j = 0; j < colw; j++) {
			printf("%1d ", n);
			n = !n;
		}
		printf("\n");
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	printTable();
	printTable2();
	printFooter();

	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf("\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
