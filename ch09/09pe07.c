/* 09pe07.c */
/* ===================================80 chars=============================== */

/*
 * Write a function prime that returns 1 if its argument is a prime number and
 * returns zero otherwise.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe07.c -o binary/09pe07
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
/* ********************************** */
#define TITLE "FUNCTION: PRIME NUMBER FINDER"
#define CFGDEBUG 1
/* both inclusive */
#define BEGIN 0
#define END 50

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
int prime(unsigned long int *num);

/* GLOBALS */

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	int begin = BEGIN;
	int end = END;
	unsigned long int n;
	int ret = 0;
	int num_count = 0;
	int prime_sum = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	for (n = begin; n <= (unsigned long int)end; n++) {
		num_count++;
		ret = prime(&n);
		if (ret == 1) {
			printf("%lu is a prime.\n", n);
			prime_sum += ret;
		}
	}
	printf("Total numbers checked between %d and %d (incl.) is: %d\n",
	       begin, end, num_count);
	printf("Prime numbers sum between these numbers is: %d\n", prime_sum);
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	displayFooter();
	/* END: Standard Footer Section ************************************* */

	return EXIT_SUCCESS;
}

/* FUNCTIONS */
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
	printf("\n%s\n\n", s);
}

void displayFooter(void)
{
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n");
}

/* return values:
 *	0 = n is not a prime number
 *	1 = n is a prime number
 * A prime number (or a prime) is a natural number greater than 1 that cannot be
 * formed by multiplying two smaller natural numbers.
 */
int prime(unsigned long int *num)
{
	int n = *num, i, flag = 0;

	if (n < 2) {
		return 0;
	}

	for (i = 2; i <= n / 2; ++i) {
		/* condition for nonprime number */
		if (n % i == 0) {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		return 1;
	} else {
		return 0;
	}
}

/* ===================================80 chars=============================== */
/* EOF */
