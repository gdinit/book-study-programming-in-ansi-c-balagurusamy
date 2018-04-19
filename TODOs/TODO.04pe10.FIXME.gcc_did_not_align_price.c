/* 04pe10.c */

/* ===================================80 chars=============================== */

/*
Write a program to read and display the following table of data.

        Name	Code	Price
        Fan	67831	1234.50
        Motor	450	5786.70

The name and code must be left-justified and price must be right-justified.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

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
#define MAXLEN 20

typedef struct twoProduct_t {
	/* name */
	char p1n [ MAXLEN ];
	char p2n [ MAXLEN ];
	/* code */
	unsigned long int p1c;
	unsigned long int p2c;
	/* price */
	float p1p;
	float p2p;
} twoProduct;

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void printHeader( void )
{
	printf(	"-----------------------------------------------------\n" );
}

void printFooter( void )
{
	printf(	"-----------------------------------------------------\n" );
}

void getTwoProducts( twoProduct* ptp )
{
	/*
	char s1[]="Fan";
	char s2[]="Motor";

	strcpy (ptp->p1n, s1);
	ptp->p1c = 67831;
	ptp->p1p = 1234.50;

	strcpy (ptp->p2n, s2);
	ptp->p2c = 450;
	ptp->p2p = 5786.70;
	*/

	fflush( stdin );
	printf( "Enter Product 1 Details. Name, Code and Price: " );
	scanf( "%s%ld%f", &( ptp->p1n ), &( ptp->p1c ), &( ptp->p1p ) );
	printf( "Enter Product 2 Details. Name, Code and Price: " );
	scanf( "%s%ld%f", &( ptp->p2n ), &( ptp->p2c ), &( ptp->p2p ) );
	/*
	*/
}

void listTwoProducts( twoProduct* ptp )
{
	printf( "Name\t\tCode\t\tPrice\n" );
	printf( "%s\t\t%ld\t\t%4.2f\n", ptp->p1n,	ptp->p1c
		, ptp->p1p );
	printf( "%s\t\t%ld\t\t%4.2f\n", ptp->p2n,	ptp->p2c
		, ptp->p2p );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char		ch = '\0';
	twoProduct	tp;
	twoProduct*	ptp = &tp;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	getTwoProducts( ptp );
	listTwoProducts( ptp );
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

