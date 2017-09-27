/* ch01.programing-exercise-12.c */

/* ===================================80 chars=============================== */

/*
   Write a program to display the following simple arithmetic calculator:
        x:		[ ]	y:		[ ]
        Sum:		[ ]	Difference:	[ ]
        Product:	[ ]	Division:	[ ]
*/

/*
	Compiled & tested with:
	gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
/* Required for: exit() */
#include <stdlib.h>

#define X 10
#define Y 2

int sum( int a, int b ) {
	return a + b;
}

int diff( int a, int b ) {
	if ( a - b > b - a ) {
		return a - b;
	} else if ( b - a > a - b ) {
		return b - a;
	} else {
		return a - b;
	}
}

int prod( int a, int b ) {
	return a * b;
}

double divide( int a, int b ) {
	return ( double )a / ( double )b;
}

int main( void )
{
	int x, y;

	x = X;
	y = Y;

	printf( "\n" );
	printf( "\t\t|=======|\t\t\t\t|=======|\n" );
	printf( "x =\t\t| %d\t|\t\ty =\t\t| %d\t|\n", x
		, y );
	printf( "\t\t|=======|\t\t\t\t|=======|\n" );
	printf( "\t\t|=======|\t\t\t\t|=======|\n" );
	printf( "Sum =\t\t| %d\t|\t\tDifference =\t| %d\t|\n", sum( x
			, y ), diff( x, y ) );
	printf( "\t\t|=======|\t\t\t\t|=======|\n" );
	printf( "\t\t|=======|\t\t\t\t|=======|\n" );
	printf( "Product =\t| %d\t|\t\tDivision =\t| %.2f\t|\n"
		, prod( x, y ), divide( x, y ) );
	printf( "\t\t|=======|\t\t\t\t|=======|\n" );
	printf( "\n" );
	printf( "\n" );

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

