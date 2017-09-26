/* ch01.programing-exercise-05.c */

/* ===================================80 chars=============================== */

/*
   Relationship between Celsius and Fahrenheit is governed by the formula:
             9C
        F = ---- + 32
             5

   Write a program to convert the temperature:
        (a) from Celsius to Fahrenheit, and
        (b) from Fahrenheit to Celsius.
*/
#include <stdio.h>

int main( void )
{
	#define CVAL 25.0
	#define FVAL 94.0

	float c, f;

	/* 25 C = ? F */
	f = ( 9 * CVAL / 5 ) + 32;
	printf( "%f Celsius = %f Fahrenheit\n", CVAL, f );

	/* 94 F = ? C */
	c = ( FVAL - 32 ) * 5 / 9;
	printf( "%f Fahrenheit = %f Celsius\n", FVAL, c );
}

/* ===================================80 chars=============================== */

/* EOF */

