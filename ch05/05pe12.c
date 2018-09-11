/* 05pe12.c */

/* ===================================80 chars=============================== */

/*
An electricity board charges the following rates for the use of electricity:

For the first 200 units: GBP80 per unit
For the next 100 units: GBP90 per unit
Beyond 300 units: GBP1.00 per unit

All users are charged a minimum of GBP100 as meter charge. If the total amount
is more than GBP400, then an additional surcharge of 15% of total amount is
charged.

Write a program to read the names of users and number of units consumed and
print out the charges with names.
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
#include <string.h>

/*
Required to prevent -> "scanf: floating point formats not linked"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
#endif

/* CONFIGURATION */
#define TITLE "ELECTRIC BILL GENERATOR"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define CUST_ARR_SIZE 10
#define BASE_CHARGE 100
/* Bracket1 Upper Value */
#define BR1_UVAL 200
#define BR1_UNIT_PRICE 0.8
#define BR2_UVAL 300
#define BR2_UNIT_PRICE 0.9
#define BR3_LVAL 301
#define BR3_UNIT_PRICE 1.0
#define OVERUSE_THRESHOLD_LVAL 400.01
#define OVERUSE_SURCHARGE_RATIO 15

typedef struct customer_t {
	char fname[24];
	long int consumed;
	/* bill amount */
	double ba;
} customer;

void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeader(void)
{
	char s[] = TITLE;
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n%s\n", s);
}

void displayFooter(void)
{
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n");
}

void getCustomerData(customer *pcusta)
{
	int n = 0;
	while (n < CUST_ARR_SIZE && !(pcusta[n].consumed < 0)) {
		printf("\n[Customer %d] Please enter customer's Firstname\n"
		       "(or a single character to skip further data entry): ",
		       n + 1);
		scanf("%s", pcusta[n].fname);
		if (strlen(pcusta[n].fname) < 2) {
			break;
		}
		printf("\n[Customer %d] Please enter consumed Energy Units: ",
		       n + 1);
		scanf("%ld", &pcusta[n].consumed);
		printf("\n");
		n++;
	}
}

int countCustomers(void)
{
	int n;
	for (n = 0; n < CUST_ARR_SIZE; n++) {
		;
	}

	return n;
}

double calcCharge(long int consumed)
{
	double rv = BASE_CHARGE;
	long int c = consumed, b2 = 0, b3 = 0;
	if (c >= 0 && c <= BR1_UVAL) {
		rv += c * BR1_UNIT_PRICE;
	} else if (c > BR1_UVAL && c <= BR2_UVAL) {
		rv += BR1_UVAL * BR1_UNIT_PRICE;
		b2 = c - BR1_UVAL;
		rv += b2 * BR2_UNIT_PRICE;
	} else if (c >= BR3_LVAL && c <= OVERUSE_THRESHOLD_LVAL) {
		rv += BR1_UVAL * BR1_UNIT_PRICE;
		rv += (BR2_UVAL - BR1_UVAL) * BR2_UNIT_PRICE;
		b3 = c - BR2_UVAL;
		rv += b3 * BR3_UNIT_PRICE;
	} else if (c >= OVERUSE_THRESHOLD_LVAL) {
		rv += BR1_UVAL * BR1_UNIT_PRICE;
		rv += (BR2_UVAL - BR1_UVAL) * BR2_UNIT_PRICE;
		b3 = c - BR2_UVAL;
		rv += b3 * BR3_UNIT_PRICE;
		rv *= 1.15;
	}

	return rv;
}

void calcDisplayCharges(customer *pcusta)
{
	int n;
	for (n = 0; ((n < CUST_ARR_SIZE) && ((strlen(pcusta[n].fname) > 1)));
	     n++) {
		printf("\n\n"
		       "====================\n"
		       "ELECTRIC BILL\n"
		       "Customer name\t\t: %s\n",
		       pcusta[n].fname);
		printf("Total consumption\t: %ld\n", pcusta[n].consumed);
		printf("Bill Amount\t\t: %5.2f\n",
		       calcCharge(pcusta[n].consumed));
		/* while at it, let's store bill amount in the struct */
		pcusta[n].ba = calcCharge(pcusta[n].consumed);
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	customer custa[CUST_ARR_SIZE] = {0};
	customer *pcusta = &(custa[0]);
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	getCustomerData(pcusta);
	if (countCustomers() > 0) {
		calcDisplayCharges(pcusta);
	}
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
