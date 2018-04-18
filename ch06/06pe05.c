/* 06pe05.c */

/* ===================================80 chars=============================== */

/*
Rewrite the Chapter06-ProgrammingExercise04 (copied below), using a for loop.

--Chapter06-ProgrammingExercise04-------
The numbers in the sequence 1 1 2 3 5 8 13 21 ... are called Fibonacci numbers.
Write a program using do...while loop to calculate and print the first m
Fibonacci numbers.

( Hint: After the first two numbers in the series, each number is the sum of two
preceding numbers. )
----------------------------------------
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
#endif

/* CONFIGURATION */
#define TITLE "CALCULATE AND PRINT FIRST M FIBONACCI NUMBERS"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define NEED_HEADER 15

typedef struct Data_t {
	long int mm;
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
	printf( "The first m Fibonacci numbers will be calculated. Enter m: " );
	scanf( "%ld", &pdata->mm );
	printf(	"m is read as %ld\n", pdata->mm );
}
void print_header( void )
{
	printf( "SEQUENCE ID\tFABI. NUM\n" );
}

void process( Data* pdata )
{
	long int	mm = pdata->mm;
	long int	it = 1;
	long int	last_sum = 0;
	long int	left = 0;
	long int	right = 0;
	long int	sum = 0;
	int		first_done = 0;

	/* init */
	it = 0;
	left = 0;
	right = 1;
	last_sum = -1;
	print_header();
	printf( "%ld\t\t%ld\n", left+right, it+1 );

	/* loop */
	for ( ; (it + 1) < mm; ) {
		it++;
		sum = left + right;
		if ( last_sum >= sum ) {
			printf("ERROR while attempting to calculate SEQUENCE ID"
			" %ld:\nlast_sum (%ld) >= sum (%ld)!?\n"
			, it+1, last_sum, sum );
			exit(EXIT_FAILURE);
		}
		if ( it % NEED_HEADER == 0 ) {
			print_header();
		}
		printf( "%ld\t\t%ld\n", it+1, sum );
		left = right;
		right = sum;
	}
}

/* zero initialize a Data struct */
void zinit( Data* pdata )
{
	pdata->mm = 0;
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

