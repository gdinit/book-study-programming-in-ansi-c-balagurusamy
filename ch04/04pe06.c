/* 04pe06.c */

/* ===================================80 chars=============================== */

/*
Write a program to read three integers from the keyboard using one scanf
statement and output them on one line using:
(a) three printf statements,
(b) only one printf with conversion specifiers, and
(c) only one printf without conversion specifiers.
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

typedef struct threeInt_t {
	int n1;
	int n2;
	int n3;
} threeInt;

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printHeader(void)
{
	printf("-------------- TWO INT MULTIPLICATION --------------\n");
}

void printFooter(void)
{
	printf("----------------------------------------------------\n");
}

void getNumbers(threeInt *pti)
{
	printf("Please enter three integers: ");
	scanf("%d %d %d", &(pti->n1), &(pti->n2), &(pti->n3));
}

void printSolution(threeInt *pti)
{
	printf("\n");
	printf("Number 1 is:\t%d\n", pti->n1);
	printf("Number 2 is:\t%d\n", pti->n2);
	printf("Number 3 is:\t%d\n", pti->n3);
	printf(
	    "Number 1, 2, 3 with HEX conversion specifier is:\t%#x %#x %#x\n",
	    pti->n1, pti->n2, pti->n3);
	printf(
	    "Number 1, 2, 3 without any conversion specifiers is:\t%d %d %d\n",
	    pti->n1, pti->n2, pti->n3);
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	threeInt ti;
	threeInt *pti = &ti;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	getNumbers(pti);
	printSolution(pti);
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
