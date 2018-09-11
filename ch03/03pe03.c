/* 03pe03.c */

/* ===================================80 chars=============================== */

/*
Modify the above program to display the two right-most digits of the integral
part of the number.
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
	Required to prevent -> "scanf: floating point formats not linked"
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

	for (n = 0; n < LINESTOCLEARSCREEN; n++)
		printf("\n");
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char gotChar = '\0';
	double number = 0.f;
	double intg = 0.f, frac = 0.f;
	int rght2 = 0;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printf("Please enter a floating point number: ");
	scanf("%lf", &number);
	printf("|---------------------------------------|\n"
	       "|\t      INITIAL VALUE\t\t|\n"
	       "|\t\t\t\t\t|\n"
	       "|\tnumber\t%f\t\t|\n"
	       "|---------------------------------------|\n",
	       number);
	frac = modf(number, &intg);
	rght2 = (int)intg % 100;
	printf("\n\n");
	printf("|---------------------------------------|\n"
	       "|\t      CALCULATED VALUES\t\t|\n"
	       "|\t\t\t\t\t|\n"
	       "|\tnumber\t%f\t\t|\n"
	       "|\t\t\t\t\t|\n"
	       "|\tintg\t%f\t\t|\n"
	       "|\tfrac\t%f\t\t|\n"
	       "|\trght2\t%d\t\t\t|\n"
	       "|---------------------------------------|\n",
	       number, intg, frac, rght2);
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */

	/* disable input & output buffers */
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
	printf("\n\n");
	printf("\n\nPress any key to quit \n");
	gotChar = getchar();
	/* required to suppress "Error: var not used!" */
	gotChar += 1;
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
