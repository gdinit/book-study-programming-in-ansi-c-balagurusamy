/* 03pe09.c */

/* ===================================80 chars=============================== */

/*
In inventory management, the Economic Order Quantity (EOQ) for a single item is
given by:
           (  2 x demand rate x setup costs	)
EOQ = SQRT ( ---------------------------------- )
           (  holding cost per item unit time	)

and the optimal Time Between Orders (TBO):
           (		2 x setup costs			)
TBO = SQRT ( ------------------------------------------	)
           ( demand rate x holding cost per unit time	)

Write a program to compute EOQ and TBO, given demand rate (items per unit time),
setup costs (per order), and the holding cost (per unit per time).
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>

/*
Required to prevent -> "scanf: floating point formats not linked"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

#define LINESTOCLEARSCREEN 90

void cls( void )
{
	int n;

	for ( n = 0; n < LINESTOCLEARSCREEN; n++ )
		printf( "\n" );
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	gotChar = '\0';
	/*
	        dr:	Demand Rate (items per unit time)
	        sc:	Setup Costs (per order)
	        hc:	Holding Cost (per item per unit time)
	        eoq:	Economic Order Quantity (units)
	        tbo:	Time Between Orders (unit time)
	*/
	float	dr = 0, sc = 0, hc = 0, eoq = 0, tbo = 0;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printf(	"|--------------------------------------------------------\n"
		"| INVENTORY CALCULATOR\n"
		"|\n"
		"| Please enter the values for computation\n"
		"|\n"
		"|\n"
		);
	printf(	"Enter DEMAND RATE (items/day): " );
	fflush( stdin );
	scanf( "%f", &dr );
	printf(	"Enter SETUP COSTS (per order): " );
	fflush( stdin );
	scanf( "%f", &sc );
	printf(	"Enter HOLDING COST (item/day): " );
	fflush( stdin );
	scanf( "%f", &hc );
	printf( "|\n"
		"|\n"
		"|  DATA READ\n"
		"|\n"
		"|  DEMAND RATE (item/day)\t%.2f\n"
		"|  SETUP COSTS (per order)\tGBP%.2f\n"
		"|  HOLDING COST (item/day)\tGBP%.2f\n"
		"|\n"
		"|\n"
		, dr, sc, hc );
	eoq = sqrt( ( 2 * dr * sc ) / ( hc ) );
	tbo = sqrt( ( 2 * sc ) / ( dr * hc ) );
	printf(	"| CALCULATION RESULTS\n"
		"|\n"
		"|  EOQ (Economic Order Quantity)\t%.0f items\n"
		"| oTBO (optimal Time Between Orders)\t%.1f days\n"
		"|--------------------------------------------------------\n"
		"\n"
		, eoq, tbo );
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */

	/* disable input & output buffers */
	setvbuf(	stdout, 0,	_IONBF, 0 );
	setvbuf(	stdin,	0,	_IONBF, 0 );
	printf( "\n\n" );
	printf( "\n\nPress any key to quit \n" );
	gotChar = getchar();
	/* required to suppress "Error: var not used!" */
	gotChar += 1;
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

