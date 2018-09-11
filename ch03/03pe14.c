/* 03pe14.c */

/* ===================================80 chars=============================== */

/*
Write a program to read two integer values m and n.
Decide and print whether m is a multiple of n.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>

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

#define LINESTOCLEARSCREEN 90

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	int m = 0, n = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush(stdin);
	printf("Please enter two integer numbers separated with space: ");
	scanf("%d %d", &m, &n);
	printf("Numbers READ:\t%d\t%d\n", m, n);
	if (m % n == 0) {
		printf("m (%d) IS a multiple of n (%d)\n", m, n);
	} else {
		printf("m (%d) IS NOT a multiple of n (%d)\n", m, n);
	}
	/* END: Program Main Code ******************************************* */
	/* BEGIN: Standard Footer Section *********************************** */
	printf("\n\n\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
