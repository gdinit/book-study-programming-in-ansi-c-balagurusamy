/* ch01.debugging-exercise-02.c */

/* ===================================80 chars=============================== */

/*
   PROBLEM:	wrong parenthesis type -> #include ( stdio.h )
   FIX:	Next line
 */
#include <stdio.h>

/*
   PROBLEM:	wrong main function return type -> void main( void )
   FIX:		Next line
 */
int main( void )
{
	/*
	   PROBLEM:	wrong function name -> print()
	   FIX:		Next line
	 */
	printf( "Hello C" );
}

/* Problem was: () instead of <> in include directive */

/* ===================================80 chars=============================== */

/* EOF */

