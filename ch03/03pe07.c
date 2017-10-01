/* 03pe07.c */

/* ===================================80 chars=============================== */

/*
Write a program that will read a real number from the keyboard and print the
following output in one line:

        Smallest integer	The given number	Largest integer
        not less than                                   not greater than
        the number					the number
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>

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

void cls( void )
{
	int n;

	for ( n = 0; n < LINESTOCLEARSCREEN; n++ )
		printf( "\n" );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	gotChar = '\0';
	double	num = 0.f, numFloor = 0, numCeil = 0, frac = 0, intg = 0;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printf(
		"|---------------------------------------|\n"
		"| NUMBER NEIGHBOR CALCULATOR\t|\n"
		"|\t\t\t\t\t|\n"
		"| Please enter a real number: " );
	scanf( "%lf", &num );
	numFloor = floor( num );
	frac = modf( num, &intg );
	/* Needed to prevent, e.g.: '4' returning 4/4/4 */
	if ( frac < 0.00001 ) {
		num += 0.00001;
		printf( "bumped the number by 0.0001!\n" );
	}
	numCeil = ceil( num );
	printf(	"\n\n"
		"%.0lf\t%lf\t%.0lf\n"
		, numFloor, num, numCeil );
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */

	/* disable input & output buffers */
	setvbuf(	stdout, 0,	_IONBF, 0 );
	setvbuf(	stdin,	0,	_IONBF, 0 );
	printf( "\n\n" );
	printf( "\n\nPress any key to quit \n" );
	gotChar = getchar();
	/* required to suppress "Error: var not used!" */
	gotChar += 1;
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

