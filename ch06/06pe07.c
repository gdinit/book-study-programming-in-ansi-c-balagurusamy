/* 06pe07.c */

/* ===================================80 chars=============================== */

/*
Write programs to print the following outputs using for loops.
	(a)	1		(b)	* * * * *
		2 2			  * * * *
		3 3 3			    * * *
		4 4 4 4			      * *
		5 5 5 5 5		        *
NOTE: In the printed book (7th ed.), 1st line of B section has 6 (instead of 5)
      asterisks. I believe this is a typo. I have therefore removed the 6th *.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
/* exit(), EXIT_FAILURE */
#include <stdlib.h>
#include <math.h>

/*
Required to prevent -> "scanf: floating point formats not linked"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
extern		_floatconvert;
#pragma extref _floatconvert
#endif

/* CONFIGURATION */
#define TITLE "PRINT CHARS USING 'FOR' LOOPS"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define LEN 5

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

void displayArt1()
{
	int n, stamped;

	for ( ( n = 1, stamped = 0 ); n <= LEN; ( n++, stamped = 0 ) ) {
		do {
			printf( "%d ", n );
			stamped++;
		} while ( stamped < n );
		printf( "\n" );
	}
	printf( "\n" );
}

void displayArt2()
{
	int n, stamped, prepad;

	for ( ( n = LEN, stamped = 0 ); n > 0;
	      ( n--, stamped = 0, prepad = 0 ) ) {
		do {
			/* print padding chars */
			while ( prepad < LEN - n ) {
				printf( "  " );
				prepad++;
			}
			/* print content */
			printf( "* " );
			stamped++;
		} while ( stamped < n );
		printf( "\n" );
	}
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	displayArt1();
	displayArt2();
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

