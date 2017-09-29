/* 02pe01.c */

/* ===================================80 chars=============================== */

/*
        Write a program to determine and print the sum of the following harmonic
        series for a given value of n:
                1 + 1/2 + 1/3 + ... + 1/n
*/

/*
        Compiled & tested with:
        gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

/* Required to prevent -> "scanf: floating point formats not linked" */
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

#include <stdio.h>
/*
   Required for: exit()
   #include <stdlib.h>
   Required for: sqrt()
   #include <math.h>
   Required for: assertions
   #include <assert.h>
   #include "round.h"
 */

/* #define GIVENVAL 5 */

int main( void )
{
	int	limit;
	int	n;
	float	sum;

	printf( "Enter the Harmonic Series limit: " );
	scanf( "%d", &limit );
	printf( "Limit input read as %d\n", limit );
	sum = 1.0;
	n = 0;
	while ( n < limit ) {
		n++;
		/* for accurate tab alignment */
		if ( n < 10 ) {
			printf( "[Addition #%d]\t\tnew sum = %f\n", n, sum );
		} else if ( n > 9 && n < 100 ) {
			printf( "[Addition #%d]\tnew sum = %f\n", n, sum );
		} else if ( n > 100 ) {
			printf( "[Addition #%d]\tnew sum = %f\n", n, sum );
		}
		sum = sum + ( float )1 / ( float )n;
	}
	printf( "Total number of additions completed: %d\n",	limit );
	printf( "FINAL VALUE: %f\n",				sum );

	/*
	printf( "\n\n" );
	printf( "--------------------------------------------\n" );
	printf( "INPUT\n\n" );
	printf( "Points\t\t\t: p1=%d,%d   p2=%d,%d\n", p1.x, p1.y, p2.x, p2.y );
	printf( "--------------------------------------------\n" );
	printf( "\n\n" );
	printf( "--------------------------------------------\n" );
	printf( "CALCULATION RESULTS\n\n" );
	printf( "*** FLOAT **********************************\n" );
	printf( "pointDistanceFloat (p2->p1 distance)\t: %f\n",	pointDistanceFloat( p2, p1 ) );
	printf( "radiusFloat\t\t\t\t: %f\n",	radiusFloat );
	printf( "diameterFloat\t\t\t\t: %f\n",			diameterFloat );
	printf( "circumferenceFloat\t\t\t: %f\n"
	        , circumferenceFloat );
	printf( "areaFloat\t\t\t\t: %f\n",			areaFloat );
	printf( "--------------------------------------------\n" );
	printf( "\n" );
	*/
	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

