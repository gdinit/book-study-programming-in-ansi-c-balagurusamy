/* 10pe04.c */
/* ===================================80 chars=============================== */

/*
 * Define a structure data type named date containing three integer members day,
 * month, and year. Develop an interactive modular program to perform the
 * following tasks:
 *
 * To read data into structure members by a function
 * To validate the date entered by another function
 * To print the date in the format
 *				April 29, 2002
 * by a third function.
 *
 * The input data should be three integers like 29, 4, and 2002 corresponding to
 * day, month, and year. Examples of invalid data:
 *				31 4 2002 -- April has only 30 days
 *				29 2 2002 -- 2002 is not a leap year
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe04.c -o binary/10pe04
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "DATE STRUCT WITH INPUT AND VALIDATION"
#define CFGDEBUG 0
#define UNKNOWN_YEAR -1
#define COMMON_YEAR 0
#define LEAP_YEAR 1
#define MAX_MONTH_CHARS 10 /* longest month name is September = 9 chars */

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

struct date_struct_t {
	int d;
	int m;
	int y;
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
const char *printMonthName(struct date_struct_t *d);
int checkIfLeap(int year, int print_out);
void displayDateMonthDDYYYYFormat(struct date_struct_t *d);
void displayMessageRequestInputDDMMYYYY(void);
void getInputDDMMYYYY(struct date_struct_t *d);
void requestTakeDateInput(struct date_struct_t *d);
void validateDateInput(struct date_struct_t *d);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct date_struct_t d;

	d.d = d.m = d.y = 0;
	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("Supported year range: 1 - 2400\n");
	requestTakeDateInput(&d);
	validateDateInput(&d);
	displayDateMonthDDYYYYFormat(&d);

	displayFooter();

	return EXIT_SUCCESS;
}
/**************************************/
void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeaderLine(void)
{
	int n;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}

void displayHeaderText(void)
{
	char s[] = TITLE;
	printf("%s\n", s);
}

void displayFooter(void)
{
	int n = 0;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}
/**************************************/
const char *printMonthName(struct date_struct_t *d)
{
	static char s[MAX_MONTH_CHARS] = "";

	switch (d->m) {
	case 1:
		strcpy(s, "January");
		printf("January");
		break;
	case 2:
		printf("February");
		break;
	case 3:
		printf("March");
		break;
	case 4:
		printf("April");
		break;
	case 5:
		printf("May");
		break;
	case 6:
		printf("June");
		break;
	case 7:
		printf("July");
		break;
	case 8:
		printf("August");
		break;
	case 9:
		printf("September");
		break;
	case 10:
		printf("October");
		break;
	case 11:
		printf("November");
		break;
	case 12:
		printf("December");
		break;
	default:
		printf("ERROR: INVALID MONTH ENTRY!\n");
		exit(EXIT_FAILURE);
	}

	return s;
}

int checkIfLeap(int year, int print_out)
{
	int r = UNKNOWN_YEAR;

	if (year % 4 != 0) {
		if (print_out) {
			printf("%d is a COMMON YEAR\n", year);
		}
		r = COMMON_YEAR;
	} else if (year % 100 != 0) {
		if (print_out) {
			printf("%d is a LEAP YEAR\n", year);
		}
		r = LEAP_YEAR;
	} else if (year % 400 != 0) {
		if (print_out) {
			printf("%d is a COMMON YEAR\n", year);
		}
		r = COMMON_YEAR;
	} else {
		if (print_out) {
			printf("%d is a LEAP YEAR\n", year);
		}
		r = LEAP_YEAR;
	}

	return r;
}

void displayDateMonthDDYYYYFormat(struct date_struct_t *d)
{
	printf("Entered Date is: ");
	printMonthName(d);
	printf(" %d, %d\n", d->d, d->y);
}

void displayMessageRequestInputDDMMYYYY(void)
{
	printf("Enter the date in DD MM YYYY format: ");
}

void getInputDDMMYYYY(struct date_struct_t *d)
{
	scanf("%d %d %d", &d->d, &d->m, &d->y);
}

void requestTakeDateInput(struct date_struct_t *d)
{
	displayMessageRequestInputDDMMYYYY();
	getInputDDMMYYYY(d);
}

void validateDateInput(struct date_struct_t *d)
{
	int is_leap = checkIfLeap(d->y, 0);

	/* Eliminate obvious issues: DAY */
	if (d->d < 1 || d->d > 31) {
		printf("ERROR: Illegal day of month: %d!\n", d->d);
		exit(EXIT_FAILURE);
	}

	/* Eliminate obvious issues: MONTH */
	if (d->m < 1 || d->m > 12) {
		printf("ERROR: Illegal month: %d!\n", d->m);
		exit(EXIT_FAILURE);
	}

	/* Eliminate obvious issues: YEAR */
	if (d->y < 1 || d->y > 2400) {
		printf("ERROR: Illegal year: %d!\n", d->y);
		exit(EXIT_FAILURE);
	}

	/*
	Second Pass on Month

	The 12 Months
	The Gregorian calendar consists of the following 12 months:
		January - 31 days
		February - 28 days in a common year and
			   29 days in leap years
		March - 31 days
		April - 30 days
		May - 31 days
		June - 30 days
		July - 31 days
		August - 31 days
		September - 30 days
		October - 31 days
		November - 30 days
		December - 31 days
	*/

	switch (d->m) {
	case 2: /* FEB */
		if (d->d >= 30) {
			printf("month %d can never have %d days!\n", d->m,
			       d->d);
			exit(EXIT_FAILURE);
		} else if (!is_leap && d->d == 29) {
			printf("%d is a common year, month %d cannot be"
			       " %d days! \n",
			       d->y, d->m, d->d);
			exit(EXIT_FAILURE);
		} else if (is_leap && d->d == 29) {
			break;
		}
	case 1:  /* JAN */
	case 3:  /* MAR */
	case 5:  /* MAY */
	case 7:  /* JUL */
	case 8:  /* AUG */
	case 10: /* OCT */
	case 12: /* DEC */
		if (d->d > 31) {
			printf("ERROR: Too many days %d in month %d!\n", d->d,
			       d->m);
			exit(EXIT_FAILURE);
		} else {
			break;
		}
	case 4:  /* APR */
	case 6:  /* JUN */
	case 9:  /* SEP */
	case 11: /* NOV */
		if (d->d > 30) {
			printf("ERROR: Too many days %d in month %d!\n", d->d,
			       d->m);
			exit(EXIT_FAILURE);
		} else {
			break;
		}
	default:
		printf("ERROR: INVALID MONTH ENTRY\n");
		exit(EXIT_FAILURE);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
