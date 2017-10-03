/* 03pe10.c */

/* ===================================80 chars=============================== */

/*
For a certain electrical circuit with an inductance L and resistance R, the
damped natural frequency is given by:
                (  1     R * R  )
Frequency =	( --- - -------	)
                (  LC	 4(C*C)	)
It is desired to study the variation of this frequency with C (capacitance).
Write a program to calculate the frequency for different values of C starting
from 0.01 to 0.1, in steps of 0.01
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
	/*
	                                                                                                                                                                                                                                                l (L)	: inductance
	        r	: resistance
	        c	: capacitance
	        f	: frequency
	        d	: discrimant
	*/
	float	l = 0.f, r = 0.f, c = 0.f, f = 0.f, d = 0.f;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush( stdin );
	printf(	"|--------------------------------------------------------\n"
		"| FREQUENCY CALCULATOR\n|\n|\n" );
	printf( "| Please enter INDUCTANCE (L): " );
	scanf( "%f", &l );
	printf( "| Please enter RESISTANCE (R): " );
	scanf( "%f", &r );
	printf(	"|--------------------------------------------------------\n"
		"| FREQUENCY TABLE\n"
		"|\n"
		"| Inductance (L)\t%.6f\n"
		"| Resistance (R)\t%.6f\n"
		"|\n"
		, l, r );
	c = 0.01;
	while ( c <= 0.10 ) {
		d = ( ( 1 / ( l * c ) ) - ( ( r * r ) / ( 4 * c * c ) ) );
		if ( d > 0 ) {
			f = sqrt( d );
		} else {
			printf( "ERROR: discrimant [%f] is non-positive!\n",
				d );
		}
		printf( "| Capacitance = %.2f\tFrequency = %.3f\n", c,
			sqrt( d ) );
		c += 0.01;
	}
	printf(	"|--------------------------------------------------------\n"
		"\n" );
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

