/* 05pe14.c */

/* ===================================80 chars=============================== */

/*
(a) Write an interactive program that could read a positive integer number and
decide whether the number is a prime number and display the output accordingly.

(b) Modify the program to count all the prime numbers that lie between 100 &
200.

NOTE: A prime number is a positive integer that is divisible only by 1 or by
itself.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
Required to prevent -> "scanf: floating point formats not linked"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
#endif

/* CONFIGURATION */
#define TITLE "PRIME NUMBERS"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66

void cls( void )
{
	int n;
	for ( n = 0; n < LINES_TO_CLEAR_SCREEN; n++ ) {
		printf( "\n" );
	}
}

void displayHeader( void )
{
	char	s [] = TITLE;
	int	tmp = 0;
	for ( tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++ ) {
		printf( "-" );
	}
	printf( "\n%s\n\n", s );
}

void displayFooter( void )
{
	int tmp = 0;
	for ( tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++ ) {
		printf( "-" );
	}
	printf( "\n" );
}

void process( int n )
{
	int i = 0, c = 0;
	/* Determine whether n is prime number & print on screen */
	for ( i = 1; i <= n; i++ ) {
		if ( n % i == 0 ) {
			c++;
		}
	}
	if ( c == 2 ) {
		printf( "Supplied number (%d) is a prime number.\n", n );
	} else {
		printf( "Supplied number (%d) is not a prime number.\n", n );
	}
}

void checkPrimeDisplay( int n )
{
	int i = 0, c = 0;
	/* Determine whether n is prime number; print n on screen if it is */
	for ( i = 1; i <= n; i++ ) {
		if ( n % i == 0 ) {
			c++;
		}
	}
	if ( c == 2 ) {
		printf( "%d\n", n );
	} else {
	}
}

void prime100200( void )
{
	int n = 0;
	for ( n = 100; n < 200; n++ ) {
		checkPrimeDisplay( n );
	}
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	int	n = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	printf(	"\nPROGRAM SECTION #1: Prime Checker\n"
		"Enter a positive number (greater than 2): " );
	scanf( "%d", &n );
	if ( n <= 2 ) {
		printf( "ERROR: Supplied number (%d) is not greater than 2!\n"
			, n );
	} else {
		process( n );
	}
	printf(	"\nPROGRAM SECTION #2: Prime Numbers between 100 & 200\n" );
	prime100200();
	displayFooter();
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

