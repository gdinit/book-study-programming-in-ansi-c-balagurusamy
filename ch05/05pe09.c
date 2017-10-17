/* 05pe09.c */

/* ===================================80 chars=============================== */

/*
Write a program that will read the value of x and evaluate the following
function:

                { 1	for x<0
        y =     { 0	for x=0
                {-1	for x>0
using
(a) nested if statements,
(b) else if statements, and
(c) conditional operator ?:
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Required to prevent -> "scanf: doubleing point formats not linked																															"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
#endif

/* CONFIGURATION */
#define TITLE "READ X EVAL FUNC"
#define LINESTOCLEARSCREEN 90
/*
#define MAX_LINES 14
#define UNIT_BASE_COST_MC 49.99
#define UNIT_BASE_COST_HI 89.99
*/

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void displayHeader( void )
{
	char	s [] = TITLE;
	int	tmp = 0;
	for ( tmp = 0; tmp < 66; tmp++ ) {
		printf( "-" );
	}
	printf( "\n%s\n", s );
}

void displayFooter( void )
{
	int tmp = 0;
	for ( tmp = 0; tmp < 66; tmp++ ) {
		printf( "-" );
	}
	printf( "\n" );
}

int getMethod( void )
{
	int m = 0;
	fflush( stdin );
	scanf( "%d", &m );

	return m;
}

void dispChooseMethodInst( void )
{
	printf(	"METHODS\n"
		"\t1. Nested if statements\n"
		"\t2. Else if statements\n"
		"\t3. Conditional operator\n"
		"Your choice: " );
}

void methodOne( void )
{
	printf(	"Nested If Statements selected. Unfortunately this method is "
		"not available! :(\n" );
}

void methodTwo( void )
{
	int x = -333, y = -444;
	printf( "Else If Statements selected.\nENTER value of x: " );
	fflush( stdin );
	scanf( "%d", &x );
	printf(	"\nx is set to %d\t and ", x );
	if ( x < 0 ) {
		y = 1;
	} else if ( x == 0 ) {
		y = 0;
	} else if ( x > 0 ) {
		y = -1;
	}
	printf( "y is calculated as %d\n", y );
}

void methodThree( void )
{
	int x = -555, y = -666;
	printf( "Conditional Operator ? : selected.\nENTER value of x: " );
	fflush( stdin );
	scanf( "%d", &x );
	printf(	"\nx is set to %d\tand ",	x );
	/* NOTE: paranthesis needed for conditional operator subsections
	in Borland C++ v.3.01 */
	x <= 0 ? ( x < 0 ? ( y = 1 ) : ( y = 0 ) ) : ( y = -1 );
	printf( "y is calculated as %d\n",	y );
}

void handleMethod( int m )
{
	switch ( m ) {
	case 1:
		methodOne();
		break;
	case 2:
		methodTwo();
		break;
	case 3:
		methodThree();
		break;
	}
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	int	m = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	dispChooseMethodInst();
	m = getMethod();
	printf( "Method read as: %d\n", m );
	handleMethod( m );
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

