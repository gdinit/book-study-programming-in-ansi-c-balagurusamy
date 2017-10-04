/* 03pe17.c */

/* ===================================80 chars=============================== */

/*
Write a program to print a table of sin and cos functions for the interval from
0 to 180 degrees in increments of 15 as shown below.

x (degrees)	sin (x)		cos (x)
0		..		..
15		..		..
..		..		..
180		..		..
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
#define PI 3.14159265
#define ANGLE_START 0
#define ANGLE_INCREMENT 0

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
		"x degrees\t\tsin(x)\t\t\tcos(x)\n"
		"-----------------------------------------------------------\n" );
}

void printFooter( void )
{
	printf( "-----------------------------------------------------------\n" );
}

/* print cos(x) and sin(x) for a given x(degrees) */
void printSinCos( double x )
{
	double	val = 0.0;
	double	rsin = 0.0;
	double	rcos = 0.0;

	val = PI / 180;
	rsin = sin( x * val );
	rcos = cos( x * val );
	printf(	"%f\t\t%f\t\t%f\n", x, rsin, rcos );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	double	x = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush( stdin );
	printHeader();
	for ( x = 0; x <= 180; x += 15 ) {
		printSinCos( x );
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

