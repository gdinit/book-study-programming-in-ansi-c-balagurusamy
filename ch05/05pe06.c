/* 05pe06.c */

/* ===================================80 chars=============================== */

/*
Write a program to print a two-dimensional Square Root Table as show below, to
provide the square root of any number from 0 to 9.9. For example, the value x
will give the square root of 3.2 and y the square root of 3.9.

Square Root Table

Number	0.0	0.1	0.2	...	0.9
0.0	__	__	__	...	__
1.0	__	__	__	...	__
2.0	__	__	__	...	__
3.0	__	__	x	...	y
9.0	__	__	__	...	__

sqrt(3.2) =
sqrt(3.9) = 1.974841
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
#define MAX_SUBJECTS 3
#define	BLANK_MARK -1
#define	COL_SIZE 20

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void printHeader( void )
{
	int tmp = 0;
	for ( tmp = 0; tmp < 66; tmp++ ) {
		printf( "-" );
	}
	printf( "\nTWO DIMENSIONAL SQUARE ROOT TABLE\n" );
}

void printFooter( void )
{
	int tmp = 0;
	for ( tmp = 0; tmp < 66; tmp++ ) {
		printf( "-" );
	}
	printf( "\n" );
}

/*
Number	0.0	0.1	0.2	...	0.9
0.0	__	__	__	...	__
1.0	__	__	__	...	__
2.0	__	__	__	...	__
3.0	__	__	x	...	y
9.0	__	__	__	...	__
*/
void printTable( void )
{
	int	r = 0, tmp = 0;
	float	j = 0.0f, c = 0.0f;

	printf( "\n" );
	for ( r = 0; r <= 9; r++ ) {
		if ( r == 0 ) {
			for ( tmp = 0; tmp < 66; tmp++ ) {
				printf( "-" );
			}
			printf( "\n" );
			printf( "Number\t" );
			for ( j = 0.0f; j < 0.91f; j += 0.1f ) {
				printf( "%.2f  ", j );
			}
			printf( "\n" );
			for ( tmp = 0; tmp < 66; tmp++ ) {
				printf( "-" );
			}
			printf( "\n" );
		}
		printf( "%1d.0\t", r );
		for ( j = 0.0f; j < 0.91f; j += 0.1f ) {
			printf( "%.2f  ", sqrt( ( float )r + j ) );
		}
		printf( "\n" );
	}
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	int	marks [ MAX_SUBJECTS ] = { -1 };
	int*	pmarks = &marks [ 0 ];
	int	readCount = 0;
	int*	preadCount = &readCount;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	printTable();
	printFooter();

	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf( "\nPress space to quit\n" );
	/* disable input buffer */
	setvbuf( stdin,	0, _IONBF, 0 );
	while ( ( ch = getchar() ) != ' ' && ch != EOF ) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

