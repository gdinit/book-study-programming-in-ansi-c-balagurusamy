/* 03pe20.c */

/* ===================================80 chars=============================== */

/*
Write a program to illustrate the use of cast operator in a real life
situation.
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
/* Configuration */
#define NUMBEG 0
#define NUMEND 100
#define NUMINC 10

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void printHeader( void )
{
	printf(
		"-----------------------------------------------------------\n"
		"CAST\n" );
}

void printFooter( void )
{
	printf(
		"-----------------------------------------------------------\n" );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	printFooter();

	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf( "\n\n\nPress space to quit\n" );
	/* disable input buffer */
	setvbuf( stdin,	0, _IONBF, 0 );
	while ( ( ch = getchar() ) != ' ' && ch != EOF ) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

