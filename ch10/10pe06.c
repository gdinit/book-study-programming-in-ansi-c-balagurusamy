/* 10pe06.c */
/* ===================================80 chars=============================== */

/*
 * Modify the input function used in Exercise 10.4 such that it reads a value
 * that represents the date in the form of a long integer, like 19450815 for the
 * date 15-8-1945 (August 15, 1945) and assigns suitable values to the members
 * day, month, and year.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe06.c -o binary/10pe06
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
#define TITLE "DATE ENTRY USING LONG INTEGER FORMAT"
#define CFGDEBUG 0
#define YEAR_MIN 1000
#define YEAR_MAX 2400
#define YEAR_UNKNOWN -1
#define YEAR_COMMON 0
#define YEAR_LEAP 1
#define LEGALITY_UNKNOWN -9
#define LEGALITY_ILLEGAL -1
#define LEGALITY_LEGAL 0
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
void requestTakeDateInputDDMMYYYY(struct date_struct_t *d);
void validateDateInput(struct date_struct_t *d);
int checkCurrentDateLegality(struct date_struct_t *d);
int getThisMonthMaxDays(struct date_struct_t *d);
void incrementMonthCorrectly(struct date_struct_t *d);
void shiftDateIfNecessary(struct date_struct_t *d);
void addDay(struct date_struct_t *d);
int getDigitCountOfLongInt(long int n);
void displayDateDDMonthYYYYFormat(struct date_struct_t *d);
void displayDateDDMonthYYYYFormatPlain(struct date_struct_t *d);
void getInputYYYYMMDD(struct date_struct_t *d);
void getInputYYYYMMDDi(long int *i);
void displayMessageRequestInputYYYYMMDD(void);
void requestTakeDateInputYYYYMMDD(struct date_struct_t *d);
void requestTakeDateInputYYYYMMDDi(long int *i);
void splitDateInputLongIntSaveToStruct(long int *i, struct date_struct_t *d);

/* PROGRAM ENTRY POINT */
int main(void)
{
	long int i = 0;
	struct date_struct_t d;

	d.d = d.m = d.y = 0;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\nSupported year range: " XSTR(YEAR_MIN) " - " XSTR(
	    YEAR_MAX) "\n");
	requestTakeDateInputYYYYMMDDi(&i);
	printf("Entered long int is:\t%ld\n", i);
	splitDateInputLongIntSaveToStruct(&i, &d);
	validateDateInput(&d);
	printf("Entered date is:\t");
	displayDateDDMonthYYYYFormatPlain(&d);
	printf("\n");
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
	int r = YEAR_UNKNOWN;

	if (year % 4 != 0) {
		if (print_out) {
			printf("%d is a COMMON YEAR\n", year);
		}
		r = YEAR_COMMON;
	} else if (year % 100 != 0) {
		if (print_out) {
			printf("%d is a LEAP YEAR\n", year);
		}
		r = YEAR_LEAP;
	} else if (year % 400 != 0) {
		if (print_out) {
			printf("%d is a COMMON YEAR\n", year);
		}
		r = YEAR_COMMON;
	} else {
		if (print_out) {
			printf("%d is a LEAP YEAR\n", year);
		}
		r = YEAR_LEAP;
	}

	return r;
}

void displayDateMonthDDYYYYFormat(struct date_struct_t *d)
{
	printf("Date is: ");
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

void requestTakeDateInputDDMMYYYY(struct date_struct_t *d)
{
	displayMessageRequestInputDDMMYYYY();
	getInputDDMMYYYY(d);
}

void validateDateInput(struct date_struct_t *d)
{
	int is_leap = checkIfLeap(d->y, 0);

	/* Eliminate obvious issues: YEAR */
	if (d->y < YEAR_MIN) {
		printf("ERROR: Illegal year -- too low value: %d! Supported "
		       "min year is: " XSTR(YEAR_MIN) "\n",
		       d->y);
		exit(EXIT_FAILURE);
	} else if (d->y > YEAR_MAX) {
		printf("ERROR: Illegal year -- too high value: %d! Supported "
		       "max year is: " XSTR(YEAR_MAX) "\n",
		       d->y);
		exit(EXIT_FAILURE);
	}

	/* Eliminate obvious issues: MONTH */
	if (d->m < 1 || d->m > 12) {
		printf("ERROR: Illegal month: %d!\n", d->m);
		exit(EXIT_FAILURE);
	}

	/* Eliminate obvious issues: DAY */
	if (d->d < 1 || d->d > 31) {
		printf("ERROR: Illegal day of month: %d!\n", d->d);
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
	case 2:				       /* FEB */
		if (d->d >= 1 && d->d <= 28) { /* legal */
			break;
		} else if (is_leap && d->d == 29) { /* legal */
			break;
		} else if (!is_leap && d->d == 29) {
			printf("%d is a common year, February cannot be %d days"
			       "! \n",
			       d->y, d->d);
			exit(EXIT_FAILURE);
		} else if (d->d >= 30) {
			printf("February can never have %d days!\n", d->d);
			exit(EXIT_FAILURE);
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
		printf("ERROR: INVALID MONTH ENTRY (d->m = %d)\n", d->m);
		exit(EXIT_FAILURE);
	}
}

/* eliminate year errors first, months errors next, day errors last */
int checkCurrentDateLegality(struct date_struct_t *d)
{
	int is_leap = -1;
	int this_month_max_days = -1;
	int day_legality = LEGALITY_UNKNOWN;

	if (d->y < YEAR_MIN || d->y > YEAR_MAX) {
		day_legality = LEGALITY_ILLEGAL;
		if (CFGDEBUG) {
			printf("DEBUG\tcheckCurrentDateLegality reports:\t"
			       "Illegal because year = %d!\n",
			       d->y);
		}
		return day_legality;
	}

	if (d->m < 1 || d->m > 12) {
		day_legality = LEGALITY_ILLEGAL;
		if (CFGDEBUG) {
			printf("DEBUG\tcheckCurrentDateLegality reports:\t"
			       "Illegal because month = %d!\n",
			       d->m);
		}
		return day_legality;
	}

	if (d->d < 1) {
		day_legality = LEGALITY_ILLEGAL;
		if (CFGDEBUG) {
			printf("DEBUG\tcheckCurrentDateLegality reports:\t"
			       "Illegal because day = %d!\n",
			       d->d);
		}
		return day_legality;
	} else {
		switch (d->m) {
		case 2: /* FEB */
			is_leap = checkIfLeap(d->y, 0);
			if (is_leap) {
				this_month_max_days = 29;
				break;
			} else {
				this_month_max_days = 28;
				break;
			}
		case 1:  /* JAN */
		case 3:  /* MAR */
		case 5:  /* MAY */
		case 7:  /* JUL */
		case 8:  /* AUG */
		case 10: /* OCT */
		case 12: /* DEC */
			this_month_max_days = 31;
			break;
		case 4:  /* APR */
		case 6:  /* JUN */
		case 9:  /* SEP */
		case 11: /* NOV */
			this_month_max_days = 30;
			break;
		default:
			printf("ERROR: Invalid month entry %d!\n", d->m);
			return day_legality;
		}
	}
	if (d->d > this_month_max_days) {
		day_legality = LEGALITY_ILLEGAL;
		if (CFGDEBUG) {
			printf("DEBUG\tcheckCurrentDateLegality reports:\t"
			       "Illegal because month=%d && day=%d!\n",
			       d->m, d->d);
		}
		return day_legality;
	} else if (d->d <= this_month_max_days) {
		day_legality = LEGALITY_LEGAL;
		if (CFGDEBUG) {
			printf("DEBUG\tcheckCurrentDateLegality reports:\t"
			       "Legal.\n");
		}
		return day_legality;
	}

	return day_legality;
}

int getThisMonthMaxDays(struct date_struct_t *d)
{
	int is_leap = -1;
	int this_month_max_days = -1;

	switch (d->m) {
	case 2: /* FEB */
		is_leap = checkIfLeap(d->y, 0);
		if (is_leap) {
			this_month_max_days = 29;
			break;
		} else {
			this_month_max_days = 28;
			break;
		}
	case 1:  /* JAN */
	case 3:  /* MAR */
	case 5:  /* MAY */
	case 7:  /* JUL */
	case 8:  /* AUG */
	case 10: /* OCT */
	case 12: /* DEC */
		this_month_max_days = 31;
		break;
	case 4:  /* APR */
	case 6:  /* JUN */
	case 9:  /* SEP */
	case 11: /* NOV */
		this_month_max_days = 30;
		break;
	default:
		printf("ERROR: Invalid month entry %d!\n", d->m);
		exit(EXIT_FAILURE);
	}
	return this_month_max_days;
}

void incrementMonthCorrectly(struct date_struct_t *d)
{
	if (d->m < 1) {
		printf("ERROR in incrementMonthCorrectly(): invalid month %d!"
		       "\n",
		       d->m);
		exit(EXIT_FAILURE);
	} else if (d->m >= 1 && d->m <= 11) {
		d->m++;
	} else if (d->m == 12) {
		d->m = 1;
		d->y++;
	}
}

void shiftDateIfNecessary(struct date_struct_t *d)
{
	int this_month_max_days;
	int day_legality = checkCurrentDateLegality(d);

	while (day_legality == LEGALITY_ILLEGAL) {
		this_month_max_days = getThisMonthMaxDays(d);
		d->d -= this_month_max_days;
		incrementMonthCorrectly(d);
		day_legality = checkCurrentDateLegality(d);
	}
}

void addDay(struct date_struct_t *d)
{
	d->d++;
	shiftDateIfNecessary(d);
}

int getDigitCountOfLongInt(long int n)
{
	int ret = 1;
	while (n /= 10) {
		ret++;
	}
	return ret;
}
void displayDateDDMonthYYYYFormat(struct date_struct_t *d)
{
	printf("Date is: ");
	printf("%d ", d->d);
	printMonthName(d);
	printf(" %d\n", d->y);
}

void displayDateDDMonthYYYYFormatPlain(struct date_struct_t *d)
{
	printf("%d ", d->d);
	printMonthName(d);
	printf(" %d", d->y);
}

void getInputYYYYMMDD(struct date_struct_t *d)
{
	scanf("%4d%2d%2d", &d->y, &d->m, &d->d);
}

void getInputYYYYMMDDi(long int *i) { scanf("%ld", i); }

void displayMessageRequestInputYYYYMMDD(void)
{
	printf("Enter the date in YYYYMMDD format with leading zeros (e.g.: "
	       "19450815): ");
}

void requestTakeDateInputYYYYMMDD(struct date_struct_t *d)
{
	displayMessageRequestInputYYYYMMDD();
	getInputYYYYMMDD(d);
}

void requestTakeDateInputYYYYMMDDi(long int *i)
{
	displayMessageRequestInputYYYYMMDD();
	getInputYYYYMMDDi(i);
}

/*
 * Expects an 8 digit long int representation of a date between years 1 to 2400
 *
 * Earliest possible date:	10000101 = 1 January 1000
 * Latest possible date:	24001201 = 31 December 2400
 */
void splitDateInputLongIntSaveToStruct(long int *i, struct date_struct_t *d)
{
	long int num = *i;
	int digits = getDigitCountOfLongInt(*i);
	int year, month, day;
	int digit_array[8] = {0};

	year = month = day = 0;
	if (digits != 8) {
		printf("\nERROR:\tInput length must be 8 but it is %d!\n"
		       "\tPlease enter the date in the following format without"
		       " spaces, such as: 1945081\n\n",
		       digits);
		exit(EXIT_FAILURE);
	}
	while (digits--) {
		digit_array[digits] = num % 10;
		num /= 10;
	}
	year += digit_array[0] * 1000;
	year += digit_array[1] * 100;
	year += digit_array[2] * 10;
	year += digit_array[3] * 1;
	month += digit_array[4] * 10;
	month += digit_array[5] * 1;
	day += digit_array[6] * 10;
	day += digit_array[7] * 1;

	d->y = year;
	d->m = month;
	d->d = day;
}

/* ===================================80 chars=============================== */
/* EOF */
