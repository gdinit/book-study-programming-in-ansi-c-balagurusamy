/* 03pe15.c */

/* ===================================80 chars=============================== */

/*
Write a program to read three values using scanf statement and print the
following results:
 (a) Sum of the values
 (b) Average of the three
 (c) Largest of the three
 (d) Smallest of the three
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

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
	double d1 = 0.0, d2 = 0.0, d3 = 0.0;
	double sum = 0.0, avg = 0.0, max = 0.0, min = 0.0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush(stdin);

	printf("Please enter three numbers separated with space: ");
	scanf("%lf %lf %lf", &d1, &d2, &d3);
	printf("Numbers READ:\t%lf\t%lf\t%lf\n\n", d1, d2, d3);

	sum = d1 + d2 + d3;
	printf("SUM\t\t\t%lf\n", sum);

	avg = (d1 + d2 + d3) / 3;
	printf("AVG\t\t\t%lf\n", avg);

	max = d1 > d2 ? (d1 > d3 ? d1 : d3) : (d2 > d3 ? d2 : d3);
	printf("LARGEST\t\t\t%.1lf\n", max);

	/* TODO: SMALLEST */
	min = d1 < d2 ? (d1 < d3 ? d1 : d3) : (d2 < d3 ? d2 : d3);
	printf("SMALLEST\t\t%.1lf\n", min);

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
