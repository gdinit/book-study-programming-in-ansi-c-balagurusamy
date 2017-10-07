/* 04pe01.c */

/* ===================================80 chars=============================== */

/*
Given the string "WORDPROCESSING", write a program to read the string from the
terminal and display the same in the following formats:
(a) WORD PROCESSING
(b) WORD
    PROCESSING
(c) W.P.
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

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void printHeader( void )
{
	printf(	"***** STRING OPERATIONS DEMO *****\n" );
}

void printFooter( void )
{
	printf( "**********************************" );
}

void getString( char str [] )
{
	printf( "Please enter a text string (40 chars max): " );
	scanf( "%s", str );
}

/* Print first 4 characters of string + a space + rest of string */
void print4SpaceRest( char str [] )
{
	int n = 0;
	printf(	"\nOPERATION #1\nPrinting first 4 characters "
		"+ a space + rest of string:\n" );
	for ( n = 0; n <= 3; n++ ) {
		printf( "%c", str [ n ] );
	}
	printf( " " );
	for ( n = 4; str [ n ] != '\0'; n++ ) {
		printf( "%c", str [ n ] );
	}
	printf( "\n" );
}

/* Print first 4 characters + a newline + rest of string */
void print4NewlineRest( char str [] )
{
	int n = 0;
	printf( "\nOPERATION #2\nPrinting first 4 characters "
		"+ a newline + rest of string:\n" );
	for ( n = 0; n <= 3; n++ ) {
		printf( "%c", str [ n ] );
	}
	printf( "\n" );
	for ( n = 4; str [ n ] != '\0'; n++ ) {
		printf( "%c", str [ n ] );
	}
	printf( "\n" );
}

/* Print 1st character + a dot + 5th char + a dot */
void print1Dot5Dot( char str [] )
{
	printf(	"\nOPERATION #3\nPrinting 1st char + a dot "
		"+ 5th char + a dot\n" );
	printf( "%c",	str [ 0 ] );
	printf( "." );
	printf( "%c",	str [ 4 ] );
	printf( "." );
	printf( "\n" );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	char	str [ 80 ];
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush( stdin );
	printHeader();
	getString( str );
	printf( "String has been read as:\t%s\n", str );
	print4SpaceRest( str );
	print4NewlineRest( str );
	print1Dot5Dot( str );
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

