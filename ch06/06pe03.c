/* 06pe03.c */

/* ===================================80 chars=============================== */

/*
Write a program to compute the sum of the digits of a given integer number.
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
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
#endif

/* CONFIGURATION */
#define TITLE "COMPUTE SUM OF DIGITS OF A GIVEN INTEGER"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define ARR_SIZE 32
#define CFGDEBUG 1

typedef struct Data_t {
	long int nn;
	char arr [ ARR_SIZE ];
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

void getNum( Data* pdata )
{
	printf( "Enter an integer number to be digit-sum'd: " );
	scanf( "%ld", &pdata->nn );
	printf(	"n is read as %ld\n", pdata->nn );
}

void process( Data* pdata )
{
	long int	nn = pdata->nn;
	long int	k = 0;
	int		len = 0;
	int		sum = 0;
	int		digits = 0;

	/* count digit length */
	for ( len = 0; nn != 0; len++ ) {
		nn /= 10;
	}
	printf( "\nlen is counted as: %d\n", len );

	nn = pdata->nn;

	/* compute the digit sum */
	for ( ( digits = len, k = 1, sum = 0 ); digits > 0;
	      ( digits--, k *= 10 ) ) {
		sum += nn / k % 10 * 1;
		if ( CFGDEBUG && k <= 1000 ) {
			printf( "nn mod: %ld\tk: %ld\t\tdigits: %d\tsum: "
				"%d\n", nn / k % 10, k, digits, sum );
		} else if ( CFGDEBUG && k > 1000 ) {
			printf( "nn mod: %ld\tk: %ld\tdigits: %d\tsum: "
				"%d\n", nn / k % 10, k, digits, sum );
		}
	}
	printf( "\nSUM is: %d\n", sum );
}

/* zero initialize a Data struct */
void zinit( Data* pdata )
{
	int j;
	for ( j = 0; j < ARR_SIZE; j++ ) {
		pdata->arr [ j ] = '\0';
	}
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	Data	data;
	Data*	pdata = &data;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	zinit( pdata );
	getNum( pdata );
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

