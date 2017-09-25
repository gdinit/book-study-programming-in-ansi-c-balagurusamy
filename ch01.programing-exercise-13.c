/* ch01.programing-exercise-13.c */

/* ===================================80 chars=============================== */

/*
   Distance between two points (x₁, y₁) and (x₂, y₂) is governed by the formula:
        D² = (x₂ - x₁)² + (y₂ - y₁)²

   Write a program to computer D given the coordinates of the points.
*/
#include <stdio.h>
/* Required for: exit() */
#include <stdlib.h>
/* Required for: sqrt() */
#include <math.h>

#define X1 3
#define Y1 2

#define X2 9
#define Y2 7

int main( void )
{
	int	x1, x2;
	int	y1, y2;
	double	distSquared, dist;

	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;

	distSquared = ( ( x2 - x1 ) * ( x2 - x1 ) ) +
		( ( y2 - y1 ) * ( y2 - y1 ) );
	dist = sqrt( distSquared );

	printf( "\n\n" );
	printf( "--------------------------------------------\n" );
	printf( "INPUT\n\n" );
	printf( "Point1: %d,%d\n",	x1,	y1 );
	printf( "Point2: %d,%d\n",	x2,	y2 );
	printf( "--------------------------------------------\n" );
	printf( "\n\n" );
	printf( "--------------------------------------------\n" );
	printf( "CALCULATION RESULTS\n\n" );
	printf( "distSquared=%f\n",	distSquared );
	printf( "dist=%f\n",		dist );
	printf( "--------------------------------------------\n" );
	printf( "\n" );
}

/* ===================================80 chars=============================== */

/* EOF */

