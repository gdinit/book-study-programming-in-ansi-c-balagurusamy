/* ch01.programing-exercise-11.c */

/* ===================================80 chars=============================== */

/*
   Area of a triangle is given by the formula:

        A = SQRT( S (S-a) (S-b) (S-c)  )
   Where a, b, and c are sides of the triangle and 2S = a + b + c.
   Write a program to compute the area of the triangle given the values of a, b,
   and c.

        //--------------------------------
        Area=SQRT(s(s-a)(s-b)(s-c)),
        where s=(a+b+c)/2 or perimeter/2
        //--------------------------------
*/
#include <stdio.h>
/* Required for: sqrt() */
#include <math.h>

/*
#define A 12
#define B 10
#define C 8
*/

#define A 14
#define B 6
#define C 12

int main( void )
{
	int	a, b, c;
	int	perimeter;
	float	s;
	float	area;

	a = A;
	b = B;
	c = C;

	/*
	the Triangle Inequality Theorem
	The Triangle Inequality Theorem states that the sum of any 2 sides of a triangle must be greater than the measure of the third side.
	Note: This rule must be satisfied for all 3 conditions of the sides.
	In other words, as soon as you know that the sum of 2 sides is less than (or equal to ) the measure of a third side, then you know that the sides do not make up a triangle.
	*/

	perimeter = a + b + c;
	s = perimeter / 2;
	area = sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) );

	printf( "\n\n" );
	printf( "sides:\ta=%d\tb=%d\tc=%d\n",		a, b, c );
	printf( "----------------------------------------\n" );
	printf( "perimeter calculated as: %d\n",	perimeter );
	printf( "s calculated as: %f\n",		s );
	printf( "area calculated as: %f\n",		area );
	printf( "----------------------------------------\n" );

	printf( "\n\n" );
	printf( "----------------------------------------\n" );
	printf( "*** DEBUG ***\n" );
	printf( "perimeter = %d\n",	perimeter );
	printf( "s = %f\n",		s );
	printf( "s-a = %f\n",		s - a );
	printf( "s-b = %f\n",		s - b );
	printf( "s-c = %f\n",		s - c );
	printf( "(s-a) (s-b) (s-c) = %f\n"
		, ( s - a ) * ( s - b ) * ( s - c ) );
	printf( "s * (s-a) * (s-b) * (s-c) = %f\n"
		, s * ( ( s - a ) * ( s - b ) * ( s - c ) ) );
	printf( "s = %f\n", area );
}

/* ===================================80 chars=============================== */

/* EOF */

