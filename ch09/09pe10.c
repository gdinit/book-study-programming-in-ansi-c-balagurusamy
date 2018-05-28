/* 09pe10.c */
/* ===================================80 chars=============================== */

/*
 * Develop a modular interactive program using functions that reads the values
 * of three sides of a triangle and displays either its area or its perimeter as
 * per the request of the user. Given the three sides a, b and c.
 *
 *		Perimeter = a + b + c
 *		Area = SQUAREROOT((s-a)(s-b)(s-c))
 *
 * where	s = (a+b+c) / 2
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe10.c -o binary/09pe10
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
#define TITLE "TRIANGLE AREA/PERIMETER CALCULATOR"
#define CFGDEBUG 1

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

struct dataCard_t {
	long int a;
	long int b;
	long int c;
};

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
/* ********************************** */
void zInit(struct dataCard_t *p_myData);
void mainLoop(struct dataCard_t *p_myData);
int getChoice(struct dataCard_t *p_myData);
void printMainMenu(struct dataCard_t *p_myData);
void actionChoice(int choice, struct dataCard_t *p_myData);
void getNumber(long int *num);
int checkTriangleIsOk(int a, int b, int c);
void calcArea(struct dataCard_t *p_myData);
void calcPerimeter(struct dataCard_t *p_myData);
void calcAreaPerimeter(struct dataCard_t *p_myData);

/* GLOBALS */

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	struct dataCard_t myData;
	struct dataCard_t *p_myData = &myData;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	zInit(p_myData);
	mainLoop(p_myData);
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

/* load some data for debug builds - saves data entry time! */
void zInit(struct dataCard_t *p_myData)
{
	if (CFGDEBUG) {
		p_myData->a = 10;
		p_myData->b = 10;
		p_myData->c = 10;
	} else {
		p_myData->a = 0;
		p_myData->b = 0;
		p_myData->c = 0;
	}
}

void mainLoop(struct dataCard_t *p_myData)
{
	int choice;

	while (1) {
		choice = getChoice(p_myData);
		actionChoice(choice, p_myData);
	}
}

int getChoice(struct dataCard_t *p_myData)
{
#define ENTRY_LOWEST 1
#define ENTRY_HIGHEST 7

	int num;

	do {
		printMainMenu(p_myData);
		FLUSH
		scanf("%d", &num);
		if (num < ENTRY_LOWEST || num > ENTRY_HIGHEST) {
			printf("\n\nERROR: Invalid input!\n");
		}
	} while (num < ENTRY_LOWEST || num > ENTRY_HIGHEST);
	printf("Valid choice selected: %d\n", num);

	return num;
}

void printMainMenu(struct dataCard_t *p_myData)
{
	printf("\n\n\n*** TITLE MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: Enter/update side A [current value: %ld]\n"
	       "\t2: Enter/update side B [current value: %ld]\n"
	       "\t3: Enter/update side C [current value: %ld]\n"
	       "\t4: Calculate AREA\n"
	       "\t5: Calculate PERIMETER\n"
	       "\t6: Calculate AREA and PERIMETER\n"
	       "\t7: EXIT program\n"
	       "Enter your choice: ",
	       p_myData->a, p_myData->b, p_myData->c);
}

void actionChoice(int choice, struct dataCard_t *p_myData)
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: Enter/update side A\n");
		getNumber(&p_myData->a);
		break;
	case 2:
		printf("\nACTIONING: Enter/update side B\n");
		getNumber(&p_myData->b);
		break;
	case 3:
		printf("\nACTIONING: Enter/update side C\n");
		getNumber(&p_myData->c);
		break;
	case 4:
		printf("\nACTIONING: Calculate AREA\n");
		calcArea(p_myData);
		break;
	case 5:
		printf("\nACTIONING: Calculate PERIMETER\n");
		calcPerimeter(p_myData);
		break;
	case 6:
		printf("\nACTIONING: Calculate AREA and PERIMETER\n");
		calcAreaPerimeter(p_myData);
		break;
	case 7:
		printf("\nACTIONING: EXIT program\nGoodbye!\n");
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

void getNumber(long int *num)
{
	printf("Please enter a number: ");
	FLUSH
	scanf("%ld", num);
}

/*
 * The Triangle Inequality Theorem
 *
 * The Triangle Inequality Theorem states that the sum of any 2 sides of a
 * triangle must be greater than the measure of the third side. Note: This
 * rule must be satisfied for all 3 conditions of the sides. In other
 * words, as soon as you know that the sum of 2 sides is less than (or
 * equal to ) the measure of a third side, then you know that the sides do
 * not make up a triangle.
 *
 * return 0: if triangle is LEGAL
 * return 1: if triangle is ILLEGAL
 */
int checkTriangleIsOk(int a, int b, int c)
{
	int ret;

	/* ASSERT: a + b > c */
	if ((a + b > c)
	    /* ASSERT: a + c > b */
	    && (a + c > b)
	    /* ASSERT: b + c > a */
	    && (b + c > a)) {
		ret = 0;
	} else {
		ret = 1;
	}

	return ret;
}

void calcArea(struct dataCard_t *p_myData)
{
	long int a = p_myData->a;
	long int b = p_myData->b;
	long int c = p_myData->c;
	long int perimeter = 0;
	float s = 0.f;
	float area = 0.f;

	if (checkTriangleIsOk(a, b, c) == 1) {
		printf("[INPUT VALIDATION] ERROR Invalid Triangle Ratio!\n");
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("[INPUT VALIDATION] OK Triangle is valid.\n");
		}
	}

	perimeter = a + b + c;
	s = perimeter / 2;
	area = sqrt(s * (s - a) * (s - b) * (s - c));

	printf("AREA = %.3f\n", area);
}

void calcPerimeter(struct dataCard_t *p_myData)
{
	long int a = p_myData->a;
	long int b = p_myData->b;
	long int c = p_myData->c;
	long int perimeter = 0;
	float s = 0.f;
	float area = 0.f;

	if (checkTriangleIsOk(a, b, c) == 1) {
		printf("[INPUT VALIDATION] ERROR Invalid Triangle Ratio!\n");
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("[INPUT VALIDATION] OK Triangle is valid.\n");
		}
	}

	perimeter = a + b + c;
	s = perimeter / 2;
	area = sqrt(s * (s - a) * (s - b) * (s - c));

	printf("PERIMETER = %ld\n", perimeter);
}

void calcAreaPerimeter(struct dataCard_t *p_myData)
{
	long int a = p_myData->a;
	long int b = p_myData->b;
	long int c = p_myData->c;
	long int perimeter = 0;
	float s = 0.f;
	float area = 0.f;

	if (checkTriangleIsOk(a, b, c) == 1) {
		printf("[INPUT VALIDATION] ERROR Invalid Triangle Ratio!\n");
		exit(EXIT_FAILURE);
	} else {
		if (CFGDEBUG) {
			printf("[INPUT VALIDATION] OK Triangle is valid.\n");
		}
	}

	perimeter = a + b + c;
	s = perimeter / 2;
	area = sqrt(s * (s - a) * (s - b) * (s - c));

	printf("AREA = %.3f\n", area);
	printf("PERIMETER = %ld\n", perimeter);
}

/* ===================================80 chars=============================== */
/* EOF */
