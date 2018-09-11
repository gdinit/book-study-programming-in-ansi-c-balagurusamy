/* 08pe09.c */
/* ===================================80 chars=============================== */

/*
Adapted:
Write a program that reads the cost of an item in the form PPPP.pp (Where PPPP
denotes Pounds (GBP) and pp denotes pennies) and converts the value to a string 
of words that expresses the numeric value in words. For example, if we input
125.75, the output should be "ONE HUNDRED TWENTY FIVE POUNDS AND SEVENTY FIVE
PENCE".

Original:
Write a program that reads the cost of an item in the form RRRR.PP (Where RRRR
denotes Rupees and PP denotes Paise) and converts the value to a string of words
that expresses the numeric value in words. For example, if we input 125.75, the
output should be "ONE HUNDRED TWENTY FIVE AND PAISE SEVENTY FIVE".
*/

/*
Compiled & tested with:
	gcc -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment
		-Wparentheses -Wformat-zero-length 08pe09.c -o binary/08pe09
*/

/*
Future Improvement Ideas
-Fix the "press space to exit" section (make it cross platform or remove it).
-Improvement: Price entry such as "120.8" logically should mean 120.80, however
 at the moment it is parsed as "120.08". We could improve this behaviour.
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
/* exit(), EXIT_FAILURE, strtol() */
#include <stdlib.h>
#include <string.h>
/* tolower() */
#include <ctype.h>

/*
Required to prevent -> "scanf: floating point formats not linked" in Borland 3
*/
/*
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
extern		_floatconvert;
#pragma extref _floatconvert
#endif
*/

/* BEGIN: FLUSH */
#ifdef _WIN32
#define FLUSH fflush(stdin);
#elif defined __unix__
#define FLUSH fpurge(stdin);
#elif defined __APPLE__
#define FLUSH fpurge(stdin);
#else
#define FLUSH fflush(stdin);
#endif
/* END: FLUSH */

/* CONFIGURATION */
#define TITLE "PRICE TO STRING"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STRMAXLEN 64
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 1

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
void takeValInput(unsigned long int *p_price);
unsigned long int getPenny(unsigned long int *p_price);
void print_number(long int num);
void print_price(unsigned long int *p_price);

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	unsigned long int price = 0;
	unsigned long int *p_price = &price;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	takeValInput(p_price);
	if (CFGDEBUG) {
		printf("[DEBUG] PRICE is set to: GBP%lu.%02lu\n",
		       *p_price / 100, getPenny(p_price));
	}
	printf("PRICE IS ");
	print_price(p_price);

	displayFooter();
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	/* TODO space works in DOS but is not cross platform. fix or remove */
	printf("\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
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

void takeValInput(unsigned long int *p_price)
{
	unsigned long int pound = 0, penny = 0, sum = 0;

	printf("Please enter the price (e.g. 120.50): ");
	FLUSH;
	scanf("%lu.%lu", &pound, &penny);
	if (CFGDEBUG) {
		printf("[DEBUG] takeValInput() VALUES READ pound: %lu\tpenny: "
		       "%02lu\n",
		       pound, penny);
	}

	/* a penny value between 1 & 99 (incl.) is adequate to validate */
	if (penny > 0 && penny <= 99) {
		if (CFGDEBUG) {
			printf("[DEBUG] takeValInput() VALIDATION OK (1).\n");
		}
		/* or perhaps, pound value is adequate to validate
		 * and penny is not invalid (such as 100 or more)
		 **/
	} else if (pound > 0 && penny < 100) {
		if (CFGDEBUG) {
			printf("[DEBUG] takeValInput() VALIDATION OK (2).\n");
		}
	} else {
		printf("takeValInput() VALIDATION failed!\nTerminating");
		exit(EXIT_FAILURE);
	}

	sum = (pound * 100) + penny;
	if (CFGDEBUG) {
		printf("[DEBUG] getPrice() SUM CALCULATED: %lu\n", sum);
	}
	*p_price = sum;
}

/* returns Penny field of a given Price */
unsigned long int getPenny(unsigned long int *p_price)
{
	unsigned long int j = *p_price;
	unsigned long int ret = 0;

	/*
	if (CFGDEBUG) {
		printf("[DEBUG] getPenny() Received price: %lu\n", *p_price);
	}
	*/

	/* return last 2 digits as a new unsigned long int number */
	ret = j % 100;

	/*
	if (CFGDEBUG) {
		printf("[DEBUG] getPenny() Returning penny = %02lu\n", ret);
	}
	*/
	return ret;
}

/*
 * print_number()
 *
 * Function programmed by EVOEx
 * https://cboard.cprogramming.com/member.php?u=33651
 *
 * Originally published at:
 * https://cboard.cprogramming.com/c-programming/112410-program-reads-number-
 * between-1-999-spells-english-post836745.html#post836745
 *
 **/
static struct {
	long int value;
	const char *name;
} number_scales[] = {
    {1000000, "MILLION"}, {1000, "THOUSAND"}, {100, "HUNDRED"}};

void print_number(long int num)
{
	unsigned int i;

	if (num < 0) {
		printf("minus ");
		num = -num;
	}

	for (i = 0; i < sizeof(number_scales) / sizeof(*number_scales); i++) {
		int scale_value = num / number_scales[i].value;
		if (!scale_value) {
			continue;
		}

		print_number(scale_value);
		printf("%s ", number_scales[i].name);
		num %= number_scales[i].value;
		if (num == 0) {
			return;
		}
	}

	if (num >= 20) {
		switch (num / 10) {
		case 2:
			printf("TWENTY ");
			break;
		case 3:
			printf("THIRTY ");
			break;
		case 4:
			printf("FORTY ");
			break;
		case 5:
			printf("FIFTY ");
			break;
		case 6:
			printf("SIXTY ");
			break;
		case 7:
			printf("SEVENTY ");
			break;
		case 8:
			printf("EIGHTY ");
			break;
		case 9:
			printf("NINETY ");
			break;
		default:
			break;
		}

		num %= 10;
		if (num == 0) {
			return;
		}
	}

	switch (num) {
	case 0:
		printf("ZERO ");
		break;
	case 1:
		printf("ONE ");
		break;
	case 2:
		printf("TWO ");
		break;
	case 3:
		printf("THREE ");
		break;
	case 4:
		printf("FOUR ");
		break;
	case 5:
		printf("FIVE ");
		break;
	case 6:
		printf("SIX ");
		break;
	case 7:
		printf("SEVEN ");
		break;
	case 8:
		printf("EIGHT ");
		break;
	case 9:
		printf("NINE ");
		break;
	case 10:
		printf("TEN ");
		break;
	case 11:
		printf("ELEVEN ");
		break;
	case 12:
		printf("TWELVE ");
		break;
	case 13:
		printf("THIRTEEN ");
		break;
	case 14:
		printf("FOURTEEN ");
		break;
	case 15:
		printf("FIFTEEN ");
		break;
	case 16:
		printf("SIXTEEN ");
		break;
	case 17:
		printf("SEVENTEEN ");
		break;
	case 18:
		printf("EIGHTEEN ");
		break;
	case 19:
		printf("NINETEEN ");
		break;
	default:
		break;
	}
}

/*
 * print_price()
 *
 * A couple of potential cases here:
 * 1) price without penny = print nothing
 * 2) price with a single penny = print PENNY
 * 3) price with more than one penny = print PENCE
 **/
void print_price(unsigned long int *p_price)
{
	unsigned long int pound = 0;
	unsigned long int *p_pound = &pound;

	unsigned long int penny = 0;
	unsigned long int *p_penny = &penny;

	pound = *p_price / 100;
	penny = getPenny(p_price);

	/* print POUND part but only if POUND is greater than zero */
	if (*p_pound > 0) {
		print_number(*p_pound);
		printf("POUNDS");
		printf(" ");
	}

	/* print PENNY part (if needed) */
	if (*p_penny == 0) {
		printf(".\n");
	} else if (*p_penny == 1) {
		if (*p_pound > 0) {
			printf("AND ");
		}
		print_number(*p_penny);
		printf("PENNY.\n");
	} else if (*p_penny > 1) {
		if (*p_pound > 0) {
			printf("AND ");
		}
		print_number(*p_penny);
		printf("PENCE.\n");
	}
}
/* ===================================80 chars=============================== */
/* EOF */
