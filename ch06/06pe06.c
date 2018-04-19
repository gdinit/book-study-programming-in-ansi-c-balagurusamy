/* 06pe06.c */

/* ===================================80 chars=============================== */

/*
Write a program to evaluate the following investment equation
        V = P(1+r)n
and print the tables which would give the value of V for various combination
of the following values of P, r, and n.
        P: 1000, 2000, 3000, ...., 10000
        r: 0.10, 0.11, 0.12, ..., 0.20
        n: 1, 2, 3, ..., 10

(Hint: P is the principal amount and V is the value of money at the end of n
years. This equation can be recursively written as:
        V = P(1+r)
        P = V
That is, the value of money at the end of first year becomes the principal
amount for the next year and so on)
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
#define TITLE "INVESTMENT CALCULATOR"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66

typedef struct Data_t {
	/* principle (p), rate (r), period (n), value at the end of period (v)*/
	double p;
	double r;
	int n;
	double v;
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

void getValues( Data* pdata )
{
	printf( "\nEnter the principle value: " );
	scanf( "%lf", &pdata->p );
	printf(	"Principle value has been supplied as %lf\n", pdata->p );

	printf( "\nEnter the rate: " );
	scanf( "%lf", &pdata->r );
	printf(	"Rate value has been supplied as %lf\n", pdata->r );

	printf( "\nEnter period value: " );
	scanf( "%d", &pdata->n );
	printf(	"Period value has been supplied as %d\n", pdata->n );
}

void print_header( void )
{
	printf( "SEQUENCE ID\tFABI. NUM\n" );
}

void process( Data* pdata )
{
	double	p = pdata->p;
	double	r = pdata->r;
	int	n = pdata->n;
	double	v = pdata->v;
	int	it = 0;

	printf(	"\nPrinciple value has been supplied as %lf\n", p );
	printf(	"Rate value has been supplied as %lf\n",	r );
	printf(	"Period value has been supplied as %d\n",	n );
	/* ---------------------------------------------------------
	An example so that I understand this better!
	e.g.:	Principal	= 1000
	        r		= 0.12% (percent rate, per period)
	        n		= 5	(unit of time)

	(post-period) Value = 1000 * (1+0.12)
	        Principal (new) = (post-period) Value
	Remember to repeat the calculation for remaining period!
	   --------------------------------------------------------- */
	printf( "PERIOD\tPRINCIPAL\tBALANCE\tRATE\n");
	for ( it = 0; it < n; it++ ) {
		v = p * ( 1 + ( r * 1 / 100 ) );
		printf( "%d\tp=%3.2lf\tv=%3.2lf\tr=%3.2lf%%\n", it + 1, p, v,
			r );
		p = v;
	}
}

/* zero initialize a Data struct */
void zinit( Data* pdata )
{
	pdata->p = 0L;
	pdata->r = 0.f;
	pdata->n = 0L;
	pdata->v = 0L;
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
	getValues( pdata );
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

