/* 03pe04.c */

/* ===================================80 chars=============================== */

/*
Write a program that will obtain the length and width of a rectangle from the
user and compute its area and perimeter.
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
/*
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif
*/

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
	int len = 0, wid = 0, area = 0;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printf("Please enter rectangle's length: ");
	scanf("%d", &len);
	printf("Please enter rectangle's width: ");
	scanf("%d", &wid);
	printf("|---------------------------------------|\n"
	       "|\t      INITIAL VALUES\t\t|\n"
	       "|\t\t\t\t\t|\n"
	       "|\t\tLength\t%d\t\t|\n"
	       "|\t\tWidth\t%d\t\t|\n"
	       "|---------------------------------------|\n",
	       len, wid);
	printf("\n\n");
	area = len * wid;
	printf("|---------------------------------------|\n"
	       "|\t      CALCULATED VALUE\t\t|\n"
	       "|\t\t\t\t\t|\n"
	       "|\t\tArea\t%d\t\t|\n"
	       "|---------------------------------------|\n",
	       area);

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
