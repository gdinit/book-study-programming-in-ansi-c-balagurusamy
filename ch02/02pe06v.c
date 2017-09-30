/* 02pe06v.c  */

/* Veltas's improved version */

/*
Write a program to count and print the number of negative and positive
numbers lastInput a given set of numbers. Test your program with a suitable set
of numbers. Use scanf to read the numbers. Reading should be terminated
when the value 0 is encountered.
*/

#include <stdio.h>

static int
promptForNumber( const char* const which )
{
	int num = 0;

	printf( "\n\nEnter %s number & press ENTER (0 to exit): ", which );
	scanf( "%d", &num );

	return num;
}

static void
printNumInfo( const int num )
{
	printf(
		"\n\nYou have entered a %s number (%d).\n\n"
		, num < 0 ? "negative" : "positive"
		, num
		);
}

static void
printTotals( const int nNeg, const int nPos )
{
	printf(
		"Negatives: %d\tPositives: %d\tTotal: %d\n"
		"-----------------------------------------\n"
		, nNeg, nPos, nNeg + nPos
		);
}

int
main( void )
{
	const char*	whichStr = "the first";
	int		num, nNeg = 0, nPos = 0;

	setvbuf(	stdout, 0,	_IONBF, 0 );
	setvbuf(	stdin,	0,	_IONBF, 0 );

	for ( ; ( num = promptForNumber( whichStr ) ); whichStr = "another" ) {
		if ( num < 0 ) {
			++nNeg;
		} else if ( num > 0 ) {
			++nPos;
		}
		printNumInfo( num );
		printf( "--- CURRENT STATS -----------------------\n" );
		printTotals( nNeg, nPos );
	}
	printf(	"TERMINATION REQUESTED\n\n"
		"--- FINAL STATS -----------------------\n" );
	printTotals( nNeg, nPos );

	printf( "\n\nPress any key to quit \n" );
	getchar();
	getchar();

	return 0;
}

/* ===================================80 chars=================================|
   */
/* EOF */

