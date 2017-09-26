/* ch01.sample-program-04.c */

/* ===================================80 chars=============================== */

/*____________ PROGRAM USING FUNCTION ____________ */

/*____________ DECLARATION ____________ */
int mul( int a, int b );

/*____________ MAIN PROGRAM BEGINS ____________ */
main()
{
	int a, b, c;
	a = 5;
	b = 10;
	c = mul( a, b );

	printf( "multiplication of %d and %d is %d", a, b, c );
}
/*____________ MAIN PROGRAM ENDS ____________ */

/*____________ MUL() FUNCTION STARTS ____________ */
int mul( int x, int y )
{
	int p;
	p = x * y;

	return( p );
}

/*____________ MUL() FUNCTION ENDS ____________ */

/* ===================================80 chars=============================== */

/* EOF */

