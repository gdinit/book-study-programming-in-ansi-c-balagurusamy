/* ch01.debugging-exercise-03.c */

/* ===================================80 chars=============================== */

/*
   PROBLEM:	missing pound sign & capital 'I' -> Include <math.h>
   FIX:		Next line
 */
#include <math.h>

/*
   PROBLEM:	stdio.h include is missing. unable to print to screen!
   FIX:		Next line
 */
#include <stdio.h>

/*
   PROBLEM:	missing 'int'. wrong type of parenthesis -> main {}
   FIX:		Next line
 */
int main()
{
	/*
	   PROBLEM:	ISO C90 forbids mixing declarations and code
	                [-Werror,-Wdeclaration-after-statement]
	   FIX:		Next line (Y declaration moved above X = 2.5 statement)
	 */
	float	Y;
	float	X;
	/*
	   PROBLEM:	missing variable type identifier -> Y = ex(x);
	                wrong capitalization -> ex(x);
	   FIX:		Next line
	 */
	X = 2.5;

	/*
	   PROBLEM:	ISO C90 forbids mixing declarations and code
	                -> float Y = exp( X );
	   FIX:		Next line
	 */

	Y = exp( X );
	/*
	   PROBLEM:	wrong printf function name && wrong format
	                && wrong capitalization -> Print(x,y);
	   FIX:		Next line
	 */
	printf( "%f, %f", X, Y );
}

/* ===================================80 chars=============================== */

/* EOF */

