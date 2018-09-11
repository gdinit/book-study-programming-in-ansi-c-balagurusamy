/* 02pe10.c */

/* ===================================80 chars=============================== */

/*
Write a program to illustrate the use of symbolic constants in a real-life
application.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define PI 3.14159265359
#define RADIUS 3

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char gotChar = '\0';
	float pi = PI;
	float radius = RADIUS;
	float area;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */

	/* Calculate Area = Pi * r * r */
	area = pi * radius * radius;
	printf("PI = %f\tRadius = %f\tArea = %f\n", pi, radius, area);
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
	fflush(stdout);
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
