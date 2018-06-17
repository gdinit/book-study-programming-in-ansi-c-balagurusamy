/* 10pe10.c */
/* ===================================80 chars=============================== */

/*
 * Add a function to the program of Exercise 10.9 that accepts two vectors as
 * input parameters and return the addition of two vectors.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 10pe10.c -o binary/10pe10
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
#define TITLE "VECTOR STRUCT ADDITION"
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
void addVectors(struct vec_struct_t *v1, struct vec_struct_t *v2,
		struct vec_struct_t *v3);
void actionChoice(int choice, struct vec_struct_t *v1, struct vec_struct_t *v2,
		  struct vec_struct_t *v3);
void printMainMenu(void);
int getChoice(void);
void mainLoop(struct vec_struct_t *v1, struct vec_struct_t *v2,
	      struct vec_struct_t *v3);

/* PROGRAM ENTRY POINT */
int main(void)
{
	struct vec_struct_t v1 = {{0}};
	struct vec_struct_t v2 = {{0}};
	struct vec_struct_t v3 = {{0}};

	cls();
	displayHeaderLine();
	displayHeaderText();
	mainLoop(&v1, &v2, &v3);
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

void addVectors(struct vec_struct_t *v1, struct vec_struct_t *v2,
		struct vec_struct_t *v3)
{
	int n;
	for (n = 0; n < ELEMENT_COUNT; n++) {
		v3->i[n] = v1->i[n] + v2->i[n];
	}
}

void actionChoice(int choice, struct vec_struct_t *v1, struct vec_struct_t *v2,
		  struct vec_struct_t *v3)
{
	switch (choice) {
	case 1:
		printf("\nACTIONING: Vector1 ENTER/UPDATE a single vector "
		       "element\n");
		handleSingleElementInput(v1);
		break;
	case 2:
		printf("\nACTIONING: Vector1 ENTER/UPDATE all vector "
		       "elements\n");
		displayMessageRequestFullVectorInput();
		takeInputForFullVector(v1);
		break;
	case 3:
		printf("\nACTIONING: Vector2 ENTER/UPDATE a single vector "
		       "element\n");
		handleSingleElementInput(v2);
		break;
	case 4:
		printf("\nACTIONING: Vector2 ENTER/UPDATE all vector "
		       "elements\n");
		displayMessageRequestFullVectorInput();
		takeInputForFullVector(v2);
		break;
	case 5:
		printf("\nACTIONING: ADD Vectors 1 & 2, store result as Vector "
		       "3\n");
		addVectors(v1, v2, v3);
		break;
	case 6:
		printf("\nACTIONING: DISPLAY Vector1\n");
		displayVectorElementsHorizontally(v1);
		break;
	case 7:
		printf("\nACTIONING: DISPLAY Vector2\n");
		displayVectorElementsHorizontally(v2);
		break;
	case 8:
		printf("\nACTIONING: DISPLAY Vector3\n");
		displayVectorElementsHorizontally(v3);
		break;
	case 9:
		printf("\nACTIONING: EXIT program\nGoodbye!\n");
		exit(EXIT_SUCCESS);
		break;
	default:
		break;
	}
}

void printMainMenu(void)
{
	printf("\n\n\n*** STRUCT-VEC ADDITION MAIN MENU ***\n"
	       "Valid Choices:\n"
	       "\t1: Vector1 ENTER/UPDATE a single vector element\n"
	       "\t2: Vector1 ENTER/UPDATE all vector elements\n"
	       "\t3: Vector2 ENTER/UPDATE a single vector element\n"
	       "\t4: Vector2 ENTER/UPDATE all vector elements\n"
	       "\t5: ADD Vectors 1 & 2, store result as Vector 3\n"
	       "\t6: DISPLAY Vector1\n"
	       "\t7: DISPLAY Vector2\n"
	       "\t8: DISPLAY Vector3\n"
	       "\t9: EXIT program\n"
	       "Enter your choice: ");
}

int getChoice(void)
{
#define ENTRY_LOWEST 1
#define ENTRY_HIGHEST 9

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

void mainLoop(struct vec_struct_t *v1, struct vec_struct_t *v2,
	      struct vec_struct_t *v3)
{
	int choice;

	while (1) {
		choice = getChoice();
		actionChoice(choice, v1, v2, v3);
	}
}

/* ===================================80 chars=============================== */
/* EOF */
