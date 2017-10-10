/* 05pe03.c */

/* ===================================80 chars=============================== */

/*
A set of two linear equations with two unknowns x1 and x2 is given below.

ax1 + bx2 = m
cx1 + dx2 = n

The set has a unique solution:

            md - bn
       x1 = -------
            ad - cb

            na - mc
       x2 = -------
            ad - cb

provided the denominator ad - cb is not equal to zero.

Write a program that will read the values of constants a, b, c, d, m and n and
compute the values of x1 and x2. An appropriate message should be printed if
ad - cb = 0.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

typedef struct Num_t {
	float a, b, c, d, m, n, x1, x2;
} Num;

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void printHeader( void )
{
	printf(	"----------------------------------------\n"
		"LINEAR EQUATION\n" );
}

void printFooter( void )
{
	printf(	"----------------------------------------\n" );
}

void getNum( Num* pnum )
{
	printf( "Please enter a, b, c, d, m and n: " );
	fflush( stdin );
	scanf( "%f%f%f%f%f%f", &pnum->a, &pnum->b, &pnum->c, &pnum->d
		, &pnum->m, &pnum->n );
}

void valNum( Num* pnum )
{
	if ( ( pnum->a * pnum->d ) - ( pnum->c * pnum->b ) == 0 ) {
		printf( "ERROR: ad - cb = 0!\n" );
		exit( EXIT_FAILURE );
	}
	printf( "Please enter a, b, c, d, m and n: " );
	fflush( stdin );
	scanf( "%f%f%f%f%f%f", &pnum->a, &pnum->b, &pnum->c, &pnum->d
		, &pnum->m, &pnum->n );
}

void solEqu( Num* pnum )
{
	pnum->x1 = ( ( pnum->m * pnum->d ) - ( pnum->b * pnum->n ) ) /
		( ( pnum->a * pnum->d ) - ( pnum->c * pnum->b ) );

	pnum->x2 = ( ( pnum->n * pnum->a ) - ( pnum->m * pnum->c ) ) /
		( ( pnum->a * pnum->d ) - ( pnum->c * pnum->b ) );
}

void printNum( Num* pnum )
{
	printf(	"Numbers are:\t a %f\n"
		"\t\t b %f\n"
		"\t\t c %f\n"
		"\t\t d %f\n"
		"\t\t m %f\n"
		"\t\t n %f\n"
		"\t\t x1 %.2f\n"
		"\t\t x2 %.2f\n"
		, pnum->a
		, pnum->b
		, pnum->c
		, pnum->d
		, pnum->m
		, pnum->n
		, pnum->x1
		, pnum->x2 );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	Num	num;
	Num*	pnum = &num;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	num.a = num.b = num.c = num.d = num.m = num.n = num.x1 = num.x2 = 0;
	cls();
	printHeader();
	getNum( pnum );
	valNum( pnum );
	solEqu( pnum );
	printNum( pnum );
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

