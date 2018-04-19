/* 06pe01.c */

/* ===================================80 chars=============================== */

/*
Given a number, write a program using while loop to reverse the digits of the
number. For example, the number:
        12345
should be written as:
        54321

Hint: Use modulus operator to extract the last digit and the integer division by
10 to get the n-1 digit number from the n gidit number.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>
/*
#include <stdlib.h>
#include <string.h>
*/

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
#define TITLE "DISPLAY A GIVEN NUMBER'S DIGITS IN REVERSE"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66

/*
 * Even though assignment does NOT require it, just for exercise
 * purposes we also store the reversed digits in the struct.
 */
typedef struct Data_t {
	long int n;
	int r [ 16 ];
} Data;

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

void getN( Data* pdata )
{
	printf( "Enter an integer number to be reversed: " );
	scanf( "%ld", &pdata->n );
	printf( "N is supplied as: %ld\n", pdata->n );
}

void process( Data* pdata )
{
	long int	n = pdata->n;
	int		len = -1, k = -1, it = -1, j = -1;
	for ( len = 0; n != 0; len++ ) {
		n /= 10;
	}
	printf( "Reversed number is: " );
	n = pdata->n;
	for ( ( it = len, k = 1, j = 0 ); it > 0; ( it--, k *= 10, j++ ) ) {
		printf( "%ld", n / k % 10 );
		pdata->r [ j ] = n / k % 10;
	}
	printf( "\n" );
}

/* zero initialize a Data struct */
void zinit( Data* pdata )
{
	int n = 0;
	pdata->n = 0;
	for ( n = 0; n < 16; n++ ) {
		pdata->r [ n ] = -1;
	}
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	Data	data;
	Data*	pdata = &data;
	data.r [ 0 ] = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	zinit( pdata );
	getN( pdata );
	process( pdata );
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

