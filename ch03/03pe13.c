/* 03pe13.c */

/* ===================================80 chars=============================== */

/*
Write a program to read three values and print ouf the largest of them without
using if statement.
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
	double d1 = 0.0, d2 = 0.0, d3 = 0.0, max = 0.0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush(stdin);
	printf("Please enter three numbers separated with space: ");
	scanf("%lf %lf %lf", &d1, &d2, &d3);
	printf("Numbers READ:\t%lf\t%lf\t%lf\n", d1, d2, d3);
	max = d1 > d2 ? (d1 > d3 ? d1 : d3) : (d2 > d3 ? d2 : d3);
	printf("LARGEST NUMBER is: %.1lf\n", max);
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
