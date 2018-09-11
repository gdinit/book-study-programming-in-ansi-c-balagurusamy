/* 03pe12.c */

/* ===================================80 chars=============================== */

/*
Write a program to print the size of various data types in C.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>

/*
Required to prevent -> "scanf: floating point formats not linked
"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

#define LINESTOCLEARSCREEN 90

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	int j = 0;
	signed long int prev = 0;

	signed char sc = '\0';
	unsigned char usc = '\0';

	signed short int ssn = 0;
	unsigned short int usn = 0;
	signed long int sln = 0;
	unsigned long int uln = 0;
	signed long long int slln = 0;
	unsigned long long int ulln = 0;

	float f = 0.f;
	double d = 0.f;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	fflush(stdin);
	printf("|--------------------------------------------------------\n"
	       "| LIST OF C  DATA TYPES AND DEMONTSRATION OF LIMITS\n|\n|\n");
	printf("sizeof(char) %d\n", sizeof(char));
	printf("sizeof(int) %d\n", sizeof(int));
	printf("sizeof(float) %d\n", sizeof(float));
	printf("sizeof(double) %d\n", sizeof(double));
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf("\n\n\nPress space bar key to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
