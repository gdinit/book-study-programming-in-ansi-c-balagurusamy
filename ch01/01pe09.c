/* ch01.programing-exercise-09.c */

/* ===================================80 chars=============================== */

/*
   Write a program using one print statement to print the pattern of asterisks
   shown below:

        *
        *	*
        *	*	*
        *	*	*	*
*/

/*
	Compiled & tested with:
	gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

int main( void )
{
	printf(
		"*\n"
		"*\t*\n"
		"*\t*\t*\n"
		"*\t*\t*\t*\n"
		);
	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

