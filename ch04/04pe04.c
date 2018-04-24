/* 04pe04.c */

/* ===================================80 chars=============================== */

/*
Write a program that reads 4 floating point values in the range 0.0 to 20.0 and
prints a horizontal bar chart to represent these values using the character * as
the fill character. For the purpose of the chart, the values may be rounded off
to the nearest integer. For example the value 4.36 should be represented as
follows:

*	*	*	*	4.36

Note that he actual values are shown at the end of each bar.
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
/* Configuration */
#define NUMMIN 0
#define NUMMAX 20

typedef struct fourNumber_t {
	double n1;
	double n2;
	double n3;
	double n4;
} fourNumber;

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printHeader(void)
{
	printf("-------------------- NUM2BAR --------------------\n");
}

void printFooter(void)
{
	printf("-------------------------------------------------\n");
}

void getNumbers(fourNumber *pfn)
{
	printf("Please enter four numbers (min: 0, max: 20): ");
	scanf("%lf %lf %lf %lf", &(pfn->n1), &(pfn->n2), &(pfn->n3),
	      &(pfn->n4));
	if (pfn->n1 < 0 || pfn->n1 > 20) {
		pfn->n1 = 0;
	}
	if (pfn->n2 < 0 || pfn->n2 > 20) {
		pfn->n2 = 0;
	}
	if (pfn->n3 < 0 || pfn->n3 > 20) {
		pfn->n3 = 0;
	}
	if (pfn->n4 < 0 || pfn->n4 > 20) {
		pfn->n4 = 0;
	}
}

void printSingleBar(double n)
{
	int i = 0;
	while (floor(n) > i) {
		i++;
		printf("* ");
	}
	printf(" %.2lf\n", n);
}

void printAllBars(fourNumber *pfn)
{
	printf("\n");
	printSingleBar(pfn->n1);
	printSingleBar(pfn->n2);
	printSingleBar(pfn->n3);
	printSingleBar(pfn->n4);
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	fourNumber fn;
	fourNumber *pfn = &fn;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	getNumbers(pfn);
	printAllBars(pfn);
	printFooter();

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
