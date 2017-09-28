/* ch01.programing-exercise-04.c */

/* ===================================80 chars=============================== */

/*
   Given the values of three variables a, b and c, write a program to compute
   and display the value of x, where:
                a
        x =   ------
                b-c

    Execute your program for the following values:
        (a) a = 250, b = 85, c = 25
        (b) a = 300, b = 70, c = 70
*/

/*
        Compiled & tested with:
        gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

#define	A1 250
#define	B1 85
#define	C1 25

#define	A2 300
#define	B2 70
#define	C2 70

int main( void )
{
	int	a, b, c;
	float	result;
	/* ================================== */
	a = A1;
	b = B1;
	c = C1;

	result = a / ( float )( b - c );

	printf( "\nValues for the computation:\n" );
	printf( "a = %d\n",		a );
	printf( "b = %d\n",		b );
	printf( "c = %d\n",		c );
	printf( "result = %f\n",	result );
	/* ================================== */
	a = A2;
	b = B2;
	c = C2;

	result = a / ( float )( b - c );

	printf( "\nValues for the computation:\n" );
	printf( "a = %d\n",		a );
	printf( "b = %d\n",		b );
	printf( "c = %d\n",		c );
	printf( "result = %f\n",	result );

	/* ================================== */
	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

