/* ch01.programing-exercise-10.c */

/* ===================================80 chars=============================== */

/*
   Write a program that will print the following figure using suitable
   characters

        |-------|				|-------|
        |	|	>>--------->		|	|
        |-------|				|-------|
*/

/*
        Compiled & tested with:
        gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

int main( void )
{
	printf( "\n" );
	printf( "\t|-------|\t\t\t\t|-------|\n" );
	printf( "\t|\t|\t>>--------->\t\t|\t|\n" );
	printf( "\t|-------|\t\t\t\t|-------|\n" );
	printf( "\n" );

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

