/* 03pe05.c */

/* ===================================80 chars=============================== */

/*
Given an integer number, write a program that display the number as follows:
	First line	:	all digits
	Second line	:	all except first digit
	Third line	:	all except first two digits
	...
	Last line	:	the last digit

	For example, the number 5678 will be displayed as:
	5 6 7 8
	6 7 8
	7 8
	8
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <math.h>
#include <stdio.h>

/*
Required to prevent -> "scanf: floating point formats not linked"
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

	for (n = 0; n < LINESTOCLEARSCREEN; n++)
		printf("\n");
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char gotChar = '\0';
	unsigned long long int number = 0;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printf("Please enter a number: ");
	scanf("%lld", &number);
	printf("|---------------------------------------|\n"
	       "|\t      INITIAL VALUE\t\t|\n"
	       "|\t\t\t\t\t|\n"
	       "|\tnumber\t%lld\t\t|\n"
	       "|---------------------------------------|\n",
	       number);
	while (number > 0) {
		printf("%lld\n", number);
		number /= 10;
	}
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */

	/* disable input & output buffers */
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
	printf("\n\n");
	printf("\n\nPress any key to quit \n");
	gotChar = getchar();
	/* required to suppress "Error: var not used!" */
	gotChar += 1;
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
