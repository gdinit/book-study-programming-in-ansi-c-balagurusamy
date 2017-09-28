/* ch01.programing-exercise-03.c */

/* ===================================80 chars=============================== */

/*
   Write a program to output the following multiplication table:
        5 x 1 = 5
        5 x 2 = 10
        5 x 3 = 15
        <snip>
        5 x 10 = 50
*/

/*
    Compiled & tested with:
    gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

#define NUMBER 5
#define HIGHERLIMIT 10

int main( void )
{
	int n;
	for ( n = 1; n <= HIGHERLIMIT; ++n )
		printf( "%d x %d = %d\n", NUMBER, n, ( NUMBER * n ) );
	printf( "\n" );

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

