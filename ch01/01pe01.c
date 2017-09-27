/* ch01.programing-exercise-03.c */

/* ===================================80 chars=============================== */

/*
   Write a program to display the equation of a line in the form "ax + by = c"
   for a=5, b=8, and c=18
*/

/*
	Compiled & tested with:
	gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

#define a 5
#define b 8
#define c 18

int main( void )
{
	printf( "\n" );
	printf( "%dx + %dy = %d\n", a, b, c );
	printf( "\n" );
	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

