/* 03pe18.c */

/* ===================================80 chars=============================== */

/*
Write a program to compute the values of square-roots and squares of the numbers
from 0 to 100 in steps 10 and print the output in a tabular form as shown below.

Number		Square-root		Square
0		0			0
..		..			..
100		10			10000
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
/* Configuration */
#define NUMBEG 0
#define NUMEND 100
#define NUMINC 10

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void printHeader( void )
{
	printf(
		"-----------------------------------------------------------\n"
		"NUMBER\t\tSQUARE-ROOT\t\tSQUARE\n"
		"-----------------------------------------------------------\n" );
}

void printFooter( void )
{
	printf( "-----------------------------------------------------------\n" );
}

/* print cos(x) and sin(x) for a given x(degrees) */
void printNumSqrtSqre( int x )
{
	double		sqrt_ = 0.0;
	long int	sqre_ = 0;

	sqrt_ = sqrt( x );
	if ( x > 0 ) {
		sqre_ = x * x;
	}
	printf(	"%d\t\t%f\t\t%ld\n", x, sqrt_, sqre_ );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	int	x = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	for ( x = NUMBEG; x <= NUMEND; x += NUMINC ) {
		printNumSqrtSqre( x );
	}
	printFooter();

	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf( "\n\n\nPress space to quit\n" );
	/* disable input buffer */
	setvbuf( stdin,	0, _IONBF, 0 );
	while ( ( ch = getchar() ) != ' ' && ch != EOF ) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

