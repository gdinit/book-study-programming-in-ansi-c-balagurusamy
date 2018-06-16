/* 10pe09.c */
/* ===================================80 chars=============================== */

/*
 * Define a structure to represent a vector (a series of integer values) and
 * write a modular program to perform the following tasks:
 *
 * -To create a vector
 * -To modify the value of a given element
 * -To multiply by a scalar value
 * -To display the vector in the form
 *  (10, 20, 30, ...)
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe09.c -o binary/10pe09
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
#define TITLE "VECTOR STRUCT TO HOLD, DISPLAY, MANIPULATE INTEGER ELEMENTS"
#define CFGDEBUG 1
#define ELEMENT_COUNT 8 /* number of elements to hold in the vector */

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

struct vec_struct_t {
	int i[ELEMENT_COUNT];
};

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void displayVectorElementsHorizontally(struct vec_struct_t *v);
void displayMessageRequestFullVectorInput(void);
void displayMessageRequestSingleVectorElementInput(void);
void displayMsgReqSingleVecElIndexInput(void);
void takeInputForFullVector(struct vec_struct_t *v);
void takeInputForSingleVectorElement(struct vec_struct_t *v, const int index);
int takeInputForSingleVectorElementIndex(void);
void handleSingleElementInput(struct vec_struct_t *v);
void displayMessageRequestScalar(void);
int takeInputForScalar(void);
void multiplyVectorWithScalar(struct vec_struct_t *v, const int scalar);
void handleMultiplyVectorScalar(struct vec_struct_t *v);
void actionChoice(int choice, struct vec_struct_t *v);
void printMainMenu(void);
int getChoice(void);
void mainLoop(struct vec_struct_t *v);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct vec_struct_t v = {{0}};

	cls();
	displayHeaderLine();
	displayHeaderText();
	mainLoop(&v);
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
void displayVectorElementsHorizontally(struct vec_struct_t *v)
{
	int n;

	printf("Vector Elements: (");
	for (n = 0; n < ELEMENT_COUNT; n++) {
		printf("%d", v->i[n]);
		if (n != ELEMENT_COUNT - 1) {
			printf(", ");
		}
	}
	printf(")\n");
}

void displayMessageRequestFullVectorInput(void)
{
	printf("Enter " XSTR(
	    ELEMENT_COUNT) " Vector elements (e.g.: 1 2 7 9 "
			   "...)\nNote that first " XSTR(
			       ELEMENT_COUNT) " elements will be "
					      "stored\nany further elements "
					      "will be discarded: ");
}

void displayMessageRequestSingleVectorElementInput(void)
{
	printf("Enter a single vector element: ");
}

void displayMsgReqSingleVecElIndexInput(void)
{
	printf("Update which vector element? min = 0, max = %d: ",
	       ELEMENT_COUNT - 1);
}

void takeInputForFullVector(struct vec_struct_t *v)
{
	int n;
	for (n = 0; n < ELEMENT_COUNT; n++) {
		scanf("%d", &(v->i[n]));
	}
}

void takeInputForSingleVectorElement(struct vec_struct_t *v, const int index)
{
	scanf("%d", &(v->i[index]));
}

int takeInputForSingleVectorElementIndex(void)
{
	int ret;
	scanf("%d", &ret);
	return ret;
}

void handleSingleElementInput(struct vec_struct_t *v)
{
	int index;

	displayMsgReqSingleVecElIndexInput();
	index = takeInputForSingleVectorElementIndex();
	displayMessageRequestSingleVectorElementInput();
	takeInputForSingleVectorElement(v, index);
}

void displayMessageRequestScalar(void)
{
	printf("Enter the scalar value to multiply the vector with: ");
}

int takeInputForScalar(void)
{
	int ret;
	scanf("%d", &ret);
	return ret;
}

void multiplyVectorWithScalar(struct vec_struct_t *v, const int scalar)
{
	int n;
	printf("// Pre-Multiplication");
	displayVectorElementsHorizontally(v);
	for (n = 0; n < ELEMENT_COUNT; n++) {
		v->i[n] = scalar * v->i[n];
	}
	printf("// Post-Multiplication");
	displayVectorElementsHorizontally(v);
}

void handleMultiplyVectorScalar(struct vec_struct_t *v)
{
	int scalar;

	displayMessageRequestScalar();
	scalar = takeInputForScalar();
	multiplyVectorWithScalar(v, scalar);
}

void actionChoice(int choice, struct vec_struct_t *v)
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: ENTER/UPDATE a single vector element\n");
		handleSingleElementInput(v);
		break;
	case 2:
		printf("\nACTIONING: ENTER/UPDATE all vector elements\n");
		displayMessageRequestFullVectorInput();
		takeInputForFullVector(v);
		break;
	case 3:
		printf("\nACTIONING: MULTIPLY vector with a scalar value\n");
		handleMultiplyVectorScalar(v);
		break;
	case 4:
		printf("\nACTIONING: DISPLAY the vector\n");
		displayVectorElementsHorizontally(v);
		break;
	case 5:
		printf("\nACTIONING: EXIT program\nGoodbye!\n");
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

void printMainMenu(void)
{
	printf("\n\n\n*** STRUCT-VEC MAIN MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: ENTER/UPDATE a single vector element\n"
	       "\t2: ENTER/UPDATE all vector elements\n"
	       "\t3: MULTIPLY vector with a scalar value\n"
	       "\t4: DISPLAY the vector\n"
	       "\t5: EXIT program\n"
	       "Enter your choice: ");
}

int getChoice(void)
{
#define ENTRY_LOWEST 1
#define ENTRY_HIGHEST 5

	int num;

	do {
		printMainMenu();
		FLUSH
		scanf("%d", &num);
		if (num < ENTRY_LOWEST || num > ENTRY_HIGHEST) {
			printf("\n\nERROR: Invalid input!\n");
		}
	} while (num < ENTRY_LOWEST || num > ENTRY_HIGHEST);
	printf("Valid choice selected: %d\n", num);

	return num;
}

void mainLoop(struct vec_struct_t *v)
{
	int choice;

	while (1) {
		choice = getChoice();
		actionChoice(choice, v);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
