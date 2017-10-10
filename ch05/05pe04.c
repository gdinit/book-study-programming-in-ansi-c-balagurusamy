/* 05pe04.c */

/* ===================================80 chars=============================== */

/*
Given a list of marks ranging from 0 to 100, write a program to compute and
print the number of students:
(a) who have obtained more than 80 marks,
(b) who have obtained more than 60 marks,
(c) who have obtained more than 40 marks,
(d) who have obtained 40 or less marks,
(e) in the range of 81 to 100,
(f) in the range of 61 to 80,
(g) in the range of 41 to 60,
(h) in the range of 0 to 40.
The program should use a minimum number of if statements.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
#define	BLANK_MARK -1
#define	COL_SIZE 20
#define MAX_MARKS 100

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void printHeader( void )
{
	printf(	"----------------------------------------\n"
		"MARKS\n" );
}

void printFooter( void )
{
	printf(	"----------------------------------------\n" );
}

void initMarks( int* pmarks )
{
	int n;
	n = 0;
	for ( n = 0; n < MAX_MARKS; n++ ) {
		pmarks [ n ] = BLANK_MARK;
	}
}

void printAllMarks( int* pmarks )
{
	int n = 0, col = 0;
	printf("\nTotal Mark Slots = %.2d.\n", MAX_MARKS );
	for ( n = 0; n < MAX_MARKS; n++ ) {
		if( pmarks [ n ] == -1 ) {
			printf("__");
		} else {
			printf( "%.2d", pmarks [ n ] );
		}
		col++;
		if ( col < COL_SIZE ) {
			printf( " " );
		} else {
			printf( "\n" );
			col = 0;
		}
	}
	printf( "\n" );
}

void printReadMarks( int* pmarks, int* preadCount )
{
	int n, col;
	n = col = 0;
	for ( n = 0; n < *preadCount; n++ ) {
		printf( "%.2d", pmarks [ n ] );
		col++;
		if ( col < COL_SIZE ) {
			printf( " " );
		} else {
			printf( "\n" );
			col = 0;
		}
	}
	printf( "\n" );
}

void getMarks( int* pmarks, int* preadCount )
{
	int n, in;
	n = in = 0;
	do {

		printf( "[ENTER MARK #%.2d] Between 0 and 100, or -1 to exit: ",
			n + 1 );
		fflush( stdin );
		scanf( "%d", &in );
		if ( in >= 0 && in <= 100 ) {
			pmarks [ n ] = in;
			printf( "New mark read as %.2d\n\n", in );
			n++;
		} else if ( in < -1 || in > 100 ) {
			printf(
				"ERROR: %2d is not a valid mark and has been discarded!\n",
				in );
			in = 101;
		} else if ( in == -1 ) {
			printf( "\nDATA ENTRY COMPLETED - %.2d MARKS READ.\n",
				n );
		}
	} while ( in >= 0 && n < MAX_MARKS );
	*preadCount += n;
}

void prepPrintReport( int* pmarks, int* preadCount )
{
	int	n = 0;
	int	m40orLess = 0, m41orMore = 0, m61orMore = 0, m81orMore = 0;
	int	m0to40 = 0, m41to60 = 0, m61to80 = 0, m81to100 = 0;
	for ( n = 0; n < *preadCount; n++ ) {
		if ( pmarks [ n ] <= 40 ) {
			m0to40++;
			m40orLess++;
		} else if ( pmarks [ n ] >= 41 && pmarks [ n ] <= 60 ) {
			m41to60++;
			m41orMore++;
		} else if ( pmarks [ n ] >= 61 && pmarks [ n ] <= 80 ) {
			m61to80++;
			m41orMore++;
			m61orMore++;
		} else if ( pmarks [ n ] >= 81 ) {
			m81to100++;
			m41orMore++;
			m61orMore++;
			m81orMore++;
		}
	}
	printf(	"----------------------------------------\n"
		"MARK BREAKDOWN\n"
		"a. Number of students scored more than 80\t: %2d\n"
		"b. Number of students scored more than 60\t: %2d\n"
		"c. Number of students scored more than 40\t: %2d\n"
		"d. Number of students scored 40 or less\t\t: %2d\n"
		"e. Marks in the range of 81 to 100\t\t: %2d\n"
		"f. Marks in the range of 61 to 80\t\t: %2d\n"
		"g. Marks in the range of 41 to 60\t\t: %2d\n"
		"h. Marks in the range of  0 to 40\t\t: %2d\n"
		, m81orMore
		, m61orMore
		, m41orMore
		, m40orLess
		, m81to100
		, m61to80
		, m41to60
		, m0to40 );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	ch = '\0';
	int	marks [ MAX_MARKS ] = { -1 };
	int*	pmarks = &marks [ 0 ];
	int	readCount = 0;
	int*	preadCount = &readCount;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	initMarks( pmarks );
	printAllMarks( pmarks );
	getMarks( pmarks, preadCount );
	/* printReadMarks( pmarks, preadCount ); */
	printAllMarks( pmarks );
	prepPrintReport( pmarks, preadCount );
	printFooter();

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

