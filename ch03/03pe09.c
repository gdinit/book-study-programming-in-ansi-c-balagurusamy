/* 03pe09.c */

/* ===================================80 chars=============================== */

/*

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
	/*
	        s: total displacement (distance) (meters)
	        u: initial velocity (meters per second)
	        t: time taken (total time) (seconds)
	        a: acceleration (meters per second) constant throughout
	*/

	float	s = 0, u = 0, t = 0, a = 0;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printf(
		"|---------------------------------------|\n"
		"| DISPLACEMENT CALCULATOR\t|\n"
		"|\t\t\t\t\t|\n"
		"| Please enter the values for computation\n"
		"|\t\t\t\t\t|\n"
		"|---------------------------------------|\n\n" );
	printf(	"Enter initial velocity (meters/sec): " );
	fflush( stdin );
	scanf( "%f", &u );
	printf(	"Enter acceleration (meters/sec): " );
	fflush( stdin );
	scanf( "%f", &a );
	printf(	"Enter time taken (total time seconds): " );
	fflush( stdin );
	scanf( "%f", &t );
	printf( "\n\n"
		"|---------------------------------------\n"
		"|  DATA READ\n"
		"|\n"
		"|  Initial Velocity\t%.2f\n"
		"|  Acceleration\t%.2f\n"
		"|  Time Taken\t%.2f\n"
		"|---------------------------------------\n\n"
		, u, a, t );
	s = ( u * t ) + ( ( a * t * t ) / 2 );
	printf(	"|---------------------------------------\n"
		"|  CALCULATION RESULT\n"
		"|\n"
		"|  Distance Travelled\t%.2f meters\n"
		"|---------------------------------------\n"
		, s );
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

