/* 05pe08.c */

/* ===================================80 chars=============================== */

/*
A cloth showroom has announced the following seasonal discounts on purchase of
items:

Purchase Amount			Discount
			Mill cloth	Handloom items
0-100			-		5%
101-200			5%		7.5%
201-300			7.5%		10.0%
Above 300		10.0%		15.0%

Write a program using switch and if statements to compute the net amount to be
paid by a customer.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
Required to prevent -> "scanf: doubleing point formats not linked
"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
#endif

/* CONFIGURATION */
#define TITLE "*** CLOTH SHOWROOM DISCOUNTS ***"
#define LINESTOCLEARSCREEN 90
#define MAX_LINES 14
#define UNIT_BASE_COST_MC 49.99
#define UNIT_BASE_COST_HI 89.99

typedef struct Order_t {
	int mc;
	int hi;
} Order;

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void displayHeader(void)
{
	char s[] = TITLE;
	int tmp = 0;
	for (tmp = 0; tmp < 66; tmp++) {
		printf("-");
	}
	printf("\n%s\n", s);
}

void displayFooter(void)
{
	int tmp = 0;
	for (tmp = 0; tmp < 66; tmp++) {
		printf("-");
	}
	printf("\n");
}

void displayBasePrices(void)
{
	double ubc_mc = UNIT_BASE_COST_MC;
	double ubc_hi = UNIT_BASE_COST_HI;
	printf("\nBASE UNIT PRICES\n"
	       "PRODUCT\t\t\t\t\t\tPRICE\n"
	       "Mill Cloth\t\t\t\t\t%3.2f\n"
	       "Handloom Items\t\t\t\t\t%3.2f\n\n",
	       ubc_mc, ubc_hi);
}

int eligibleForDiscount(Order *o)
{
	if (o->mc >= 101 || o->hi > 0) {
		return 1;
	} else {
		return 0;
	}
}

double calcDiscLineItemMc(Order *pord)
{
	int qty = pord->mc;
	double dis = 0.0, rv = 0.0;
	if (qty >= 0 && qty <= 100) {
		dis = 0.0;
	} else if (qty >= 101 && qty <= 200) {
		dis = .05;
	} else if (qty >= 201 && qty <= 300) {
		dis = .075;
	} else if (qty > 300) {
		dis = .1;
	}
	rv = (qty * UNIT_BASE_COST_MC) - (qty * UNIT_BASE_COST_MC * dis);

	return rv;
}

double calcDiscLineItemHi(Order *pord)
{
	int qty = pord->hi;
	double dis = 0.0, rv = 0.0;
	if (qty >= 0 && qty <= 100) {
		dis = .05;
	} else if (qty >= 101 && qty <= 200) {
		dis = .075;
	} else if (qty >= 201 && qty <= 300) {
		dis = .1;
	} else if (qty > 300) {
		dis = .15;
	}
	rv = (qty * UNIT_BASE_COST_HI) - (qty * UNIT_BASE_COST_HI * dis);

	return rv;
}

void displayOrder(Order *pord)
{
	int el = eligibleForDiscount(pord);

	if (el) {
		double limc = .0, lihi = .0, norm = .0, disc = .0, savi = .0;
		limc = calcDiscLineItemMc(pord);
		lihi = calcDiscLineItemHi(pord);
		norm =
		    pord->mc * UNIT_BASE_COST_MC + pord->hi * UNIT_BASE_COST_HI;
		disc = limc + lihi;
		savi = norm - disc;
		printf("\nCURRENT ORDER\n"
		       "PRODUCT\t\t\t   UNITS\t\tSUBTOTAL\n"
		       "Mill Cloth\t\t%7d\t\t\t%8.2f\n",
		       pord->mc, (double)pord->mc * UNIT_BASE_COST_MC);
		printf("Handloom Items\t\t%7d\t\t\t%8.2f\n", pord->hi,
		       (double)pord->hi * UNIT_BASE_COST_HI);
		printf("GRAND TOTAL\t\t%7.0d\t\t\t%8.2f\n", pord->mc + pord->hi,
		       norm);
		printf("SAVINGS\t\t\t\t\t\t%8.2f\n", savi);
		printf("DISCOUNTED TOTAL\t\t\t\t%8.2f\n", limc + lihi);
	} else {
		printf("CURRENT ORDER\n"
		       "PRODUCT\t\t\t   UNITS\t\tSUBTOTAL\n"
		       "Mill Cloth\t\t%7d\t\t\t%8.2f\n"
		       "Handloom Items\t\t%7d\t\t\t%8.2f\n"
		       "GRAND TOTAL\t\t%7.0f\t\t\t%8.2f\n",
		       pord->mc, (double)pord->mc * UNIT_BASE_COST_MC, pord->hi,
		       (double)pord->hi * UNIT_BASE_COST_HI,
		       (double)pord->mc + pord->hi,
		       (double)pord->mc * UNIT_BASE_COST_MC +
			   (double)pord->hi * UNIT_BASE_COST_HI);
	}
}

void displayPreQtyText(void)
{
	printf("\nPlease enter quantities Mill Cloth & Handloom Items,\n"
	       "separated with a space: ");
}

void getQtys(Order *pord)
{
	fflush(stdin);
	scanf("%d %d", &pord->mc, &pord->hi);
	printf("\nAdded %d & %d items to the order.\n", pord->mc, pord->hi);
}

void run(Order *pord)
{
	displayBasePrices();
	displayPreQtyText();
	getQtys(pord);
	displayOrder(pord);
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	Order ord = {190, 430};
	Order *pord = &ord;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	run(pord);
	displayFooter();
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf("\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
