/* 09pe09.c */
/* ===================================80 chars=============================== */

/*
 * Develop a top-down modular program to implement a calculator. The program
 * should request the user to input two numbers and display one of the following
 * as per the desire of the user:
 *
 *	(a) Sum of the numbers
 *	(b) Difference of the numbers
 *	(c) Product of the numbers
 *	(d) Division of the numbers
 *
 * Provide separate functions for performing various tasks such as reading,
 * calculating and displaying. Calculating module should call second level
 * modules to perform the individual mathematical operations. The main function
 * should have only function calls.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe09.c -o binary/09pe09
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
/* ********************************** */
#define TITLE "SIMPLE CALCULATOR"
#define CFGDEBUG 1
/* both inclusive */
#define BEGIN 0
#define END 50

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
	long int n1;
	long int n2;
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
void add(struct dataCard_t *p_myData);
void subtract(struct dataCard_t *p_myData);
void multiply(struct dataCard_t *p_myData);
void divide(struct dataCard_t *p_myData);

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

void zInit(struct dataCard_t *p_myData)
{
	p_myData->n1 = 0;
	p_myData->n2 = 0;
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
	printf("\n\n\n*** SIMPLE-CALC MAIN MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: Enter/update number 1 [current value: %ld]\n"
	       "\t2: Enter/update number 2 [current value: %ld]\n"
	       "\t3: ADD\n"
	       "\t4: SUBTRACT\n"
	       "\t5: MULTIPLY\n"
	       "\t6: DIVIDE\n"
	       "\t7: EXIT program\n"
	       "Enter your choice: ",
	       p_myData->n1, p_myData->n2);
}

void actionChoice(int choice, struct dataCard_t *p_myData)
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: Enter/update number 1\n");
		getNumber(&p_myData->n1);
		break;
	case 2:
		printf("\nACTIONING: Enter/update number 2\n");
		getNumber(&p_myData->n2);
		break;
	case 3:
		printf("\nACTIONING: ADD\n");
		add(p_myData);
		break;
	case 4:
		printf("\nACTIONING: SUBTRACT\n");
		subtract(p_myData);
		break;
	case 5:
		printf("\nACTIONING: MULTIPLY\n");
		multiply(p_myData);
		break;
	case 6:
		printf("\nACTIONING: DIVIDE\n");
		divide(p_myData);
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

void add(struct dataCard_t *p_myData)
{
	printf("%ld + %ld = %ld", p_myData->n1, p_myData->n2,
	       p_myData->n1 + p_myData->n2);
}

void subtract(struct dataCard_t *p_myData)
{
	printf("%ld - %ld = %ld", p_myData->n1, p_myData->n2,
	       p_myData->n1 - p_myData->n2);
}

void multiply(struct dataCard_t *p_myData)
{
	printf("%ld * %ld = %ld", p_myData->n1, p_myData->n2,
	       p_myData->n1 * p_myData->n2);
}

void divide(struct dataCard_t *p_myData)
{
	printf("%ld / %ld = %.2f", p_myData->n1, p_myData->n2,
	       (double)p_myData->n1 / (double)p_myData->n2);
}

/* ===================================80 chars=============================== */
/* EOF */
