/* round.c */

/*
	see header for copyright information
*/

/* ===================================80 chars=============================== */

long round( double number )
/*
	Returns the rounded (long) value of the number.
	Handles negative numbers as well as positive.
*/
{
   int remainder = (number - (long)number) * 10;

   return ( number + (remainder>4) - (remainder<(-4)) );
}

/* ===================================80 chars=============================== */

/* EOF */

