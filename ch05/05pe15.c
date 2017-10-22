/* 05pe15.c */

/* ===================================80 chars=============================== */

/*
Write a program to read a double-type value x that represents angle in radians
and a character type variable T that represents the type of trigonometric
function and display the value of:

(a) sin(x), if s or S is assigned to T,
(b) cos(x), if c or C assigned to T, and
(c) tan(x), if t or T is assigned to t

using (i) if...else statement, and (ii) switch statement.
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
#define TITLE "TRIGONOMETRIC FUNCTION BASED ON INPUT"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define PI 3.1416

typedef struct Data_t {
	double x;
	char t;
	/* answer */
	double a;
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

void getX( Data* pdata )
{
	printf( "Enter the value of X (angle in radians): " );
	scanf( "%lf", &pdata->x );
	printf( "X is supplied as: %f\n", pdata->x );
}

void getT( Data* pdata )
{
	printf(	"Trigonometric Function Codes\n"
		"\tS for sin\n"
		"\tC for cos\n"
		"\tT for tan\n" );
	printf( "Enter trigonometric function code: " );
	fflush( stdin );
	scanf( "%c", &pdata->t );
	printf( "Value supplied as: %c\n", pdata->t );
}

/* (i) using if...else statement */
void process1( Data* pdata )
{
	double val = 0.0;
	val = PI / 180.0;
	printf( "\n\nProcessing X=%f & T=%c using method #1\n"
		, pdata->x, pdata->t );
	if ( pdata->t == 's' || pdata->t == 'S' ) {
		printf( "sin(%f) is: %f\n"
			, pdata->x, sin( pdata->x * val ) );
	} else if ( pdata->t == 'c' || pdata->t == 'C' ) {
		printf( "cos(%f) is: %f\n"
			, pdata->x, cos( pdata->x * val ) );
	} else if ( pdata->t == 't' || pdata->t == 'T' ) {
		printf( "tan(%f) is: %f\n"
			, pdata->x, tan( pdata->x * val ) );
	}
}

/* (ii) using switch statement */
void process2( Data* pdata )
{
	double val = 0.0;
	val = PI / 180.0;
	printf( "\n\nProcessing X=%f & T=%c using method #2\n"
		, pdata->x, pdata->t );
	switch ( pdata->t ) {
	case 83:
	case 115:
		printf( "sin(%f) is: %f\n"
			, pdata->x, sin( pdata->x * val ) );
		break;
	case 67:
	case 99:
		printf( "cos(%f) is: %f\n"
			, pdata->x, cos( pdata->x * val ) );
		break;
	case 84:
	case 116:
		printf( "tan(%f) is: %f\n"
			, pdata->x, tan( pdata->x * val ) );
		break;
	default:
		printf( "ERROR: Unknown operation!\n" );
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
	getX( pdata );
	getT( pdata );
	process1( pdata );
	process2( pdata );
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

