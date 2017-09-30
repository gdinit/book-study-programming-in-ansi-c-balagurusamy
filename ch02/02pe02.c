/* 02pe02.c  */

/* ===================================80 chars=============================== */

/*
        Write a program to read the price of an item in decimal form (like
        15.95) and print the output in GBP (like GBP15.95).
*/

#include <stdio.h>

/* Required to prevent -> "scanf: floating point formats not linked" */
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

int main( void )
{
	char	noNeed;

	float	price;

	price = 0;

	printf( "Enter the price of item (e.g.: 7.00):  " );
	scanf( "%f", &price );
	printf( "Price is: GBP%*.*f\n", 2, 2, price );

	printf( "Press any key to quit \n" );
	noNeed = getchar();
	noNeed = getchar();
	/* to suppress var not used! */
	noNeed = noNeed + 1;

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

