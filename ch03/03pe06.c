/* 03pe06.c */

/* ===================================80 chars=============================== */

/*
The straight-line method of computing the yearly depreciation of the value
of an item is given by:

                        Purchase Price - Salvage Value
        Depreciation = --------------------------------
                                Years of Service

Write a program to determine the salvage value of an item when the purchase
price, years of service, and the annual depreciation are given.
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
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

#define LINESTOCLEARSCREEN 90

void cls( void )
{
	int n;

	for ( n = 0; n < LINESTOCLEARSCREEN; n++ )
		printf( "\n" );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char		gotChar = '\0';
	long long int	dep = 0, pri = 0, yrs = 0, sal = 0;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printf(
		"|---------------------------------------|\n"
		"|\tSALVAGE VALUE CALCULATOR\t|\n"
		"|\t\t\t\t\t|\n"
		"| Please provide annual depreciation,\t|\n"
		"| purchase price, and years of service\t|\n"
		"|---------------------------------------|\n"
		);
	printf( "\nDEPRECIATION: " );
	scanf( "%lld", &dep );
	printf( "\nPURCHASE PRICE: " );
	scanf( "%lld", &pri );
	printf( "\nYEARS OF SERVICE: " );
	scanf( "%lld", &yrs );
	sal = pri - ( dep * yrs );
	if ( sal < 0 ) {
		sal = -1;
	}
	printf( "\n\n"
		"|---------------------------------------\n"
		"|  DATA READ\n"
		"|\n"
		"|  Depreciation\t\t%lld\n"
		"|  Purchase Price\t%lld\n"
		"|  Years of Service\t%lld\n"
		"|---------------------------------------\n"
		"\n"
		"|---------------------------------------\n"
		"|  CALCULATION RESULT\n"
		"|\n"
		"|  Salvage Value\t%lld\n"
		"|---------------------------------------\n"
		, dep, pri, yrs, sal );

	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */

	/* disable input & output buffers */
	setvbuf(	stdout, 0,	_IONBF, 0 );
	setvbuf(	stdin,	0,	_IONBF, 0 );
	printf( "\n\n" );
	printf( "\n\nPress any key to quit \n" );
	gotChar = getchar();
	/* required to suppress "Error: var not used!" */
	gotChar += 1;
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

