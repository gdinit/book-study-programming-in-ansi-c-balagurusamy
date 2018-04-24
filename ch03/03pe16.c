/* 03pe16.c */

/* ===================================80 chars=============================== */

/*
The cost of one type of mobile service is GBP250.00 plus GBP1.25 for each call
made over and above 100 calls. Write a program to read customer codes and calls
made, and print the bill for each customer.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <math.h>
#include <stdio.h>

/*
Required to prevent -> "scanf: floating point formats not linked
"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

#define LINESTOCLEARSCREEN 90
/* Configuration */
#define FEE_BASE 250.f
#define FEE_EXTRA 1.25f
#define INCLUDED_CALLS 100
/* Customer Call Count List:
A fake database, showing how many calls each subscriber placed during the last
billing period */
#define CCC01 180
#define CCC02 125
#define CCC03 217
#define CCC04 378
#define CCC05 25

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printBillHeader(void)
{
	printf("\n---------------------------------------\n"
	       "CUSTOMER ID\tCALL COUNT\tBILL\n");
}

void printBillFooter(void)
{
	printf("---------------------------------------\n");
}

void printBill(int customer_id, int callsTotal)
{
	float feeBase = FEE_BASE;
	float feeExtra = FEE_EXTRA;
	float amountDue = 0.f;
	int callsIncluded = INCLUDED_CALLS;
	int callsExtra = 0;

	if (callsTotal > callsIncluded) {
		callsExtra = callsTotal - callsIncluded;
		amountDue = feeBase + (callsExtra * feeExtra);
	} else {
		amountDue = (float)feeBase;
	}
	printf("%d\t\t%d\t\t%.2f\n", customer_id, callsTotal, amountDue);
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush(stdin);
	printBillHeader();
	printBill(01, CCC01);
	printBill(02, CCC02);
	printBill(03, CCC03);
	printBill(04, CCC04);
	printBill(05, CCC05);
	printBillFooter();

	/* END: Program Main Code ******************************************* */
	/* BEGIN: Standard Footer Section *********************************** */
	printf("\n\n\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
