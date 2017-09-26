/* ch01.sample-program-03.c */

/* ===================================80 chars=============================== */

/*____________ INVESTMENT PROBLEM ____________ */
#define PERIOD 10
#define PRINCIPAL 5000.00
/*____________ MAIN PROGRAM BEGINS ____________ */
main()
{/*____________ DECLARATION STATEMENTS ____________ */
	int	year;
	float	amount, value, inrate;
	/*____________ ASSIGNMENT STATEMENTS ____________ */
	amount = PRINCIPAL;
	inrate = 0.11;
	year = 0;
	/*
	  ____________ COMPUTATION STATEMENTS ____________
	  ____________ COMPUTATION USING While LOOP ____________
	 */
	while ( year <= PERIOD ) {
		printf( "%2d   %8.2f\n", year, amount );
		value = amount + inrate * amount;
		year = year + 1;
		amount = value;
	}
	/*____________ While LOOP ENDS ____________ */
}
/*____________ PROGRAM ENDS ____________ */

/* ===================================80 chars=============================== */

/* EOF */

