/* 03pe11.c */

/* ===================================80 chars=============================== */

/*
Write a program to read a four digit integer and print the sum of its digits.
Hint: use / and % operators.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>

/*
Required to prevent -> "scanf: floating point formats not linked																															"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

#define LINESTOCLEARSCREEN 90

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	int	ch = 0;
	int	num = 0;
	/*	e.g. number 1234 <-> d1 = 1, d2 = 2, d3 = 3, d4 = 4 */
	int	d1 = 0, d2 = 0, d3 = 0, d4 = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush( stdin );
	printf(	"|--------------------------------------------------------\n"
		"| 4-DIGIT SUMMER\n|\n|\n" );
	printf( "| Please enter a 4-digit integer: " );
	scanf( "%d", &num );
	printf( "\n\nNumber read: %d\n", num );
	d4 = num / 1 % 10;
	d3 = num / 10 % 10;
	d2 = num / 100 % 10;
	d1 = num / 1000 % 10;
	printf( "| Digits 1 (left) to 4 are:\t%d\t%d\t%d\t%d\n"
		, d1, d2, d3, d4 );
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf( "\n\n\nPress space bar key to quit\n" );
	/* disable input buffer */
	setvbuf( stdin,	0, _IONBF, 0 );
	while ( ( ch = getchar() ) != ' ' && ch != EOF ) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

