/* 02pe01.c */

/* ===================================80 chars=============================== */

/*
	Write a program to determine and print the sum of the following harmonic
	series for a given value of n:
		1 + 1/2 + 1/3 + ... + 1/n
*/

/*
	Compiled & tested with:
	gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Required to prevent -> "scanf: floating point formats not linked" */
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	int limit;
	int n;
	float sum;

	printf("Enter the Harmonic Series limit: ");
	scanf("%d", &limit);
	printf("Limit input read as %d\n", limit);
	sum = 1.0;
	n = 0;
	while (n < limit) {
		n++;
		/* for accurate tab alignment */
		if (n < 10) {
			printf("[Addition #%d]\t\tnew sum = %f\n", n, sum);
		} else if (n > 9 && n < 100) {
			printf("[Addition #%d]\tnew sum = %f\n", n, sum);
		} else if (n > 100) {
			printf("[Addition #%d]\tnew sum = %f\n", n, sum);
		}
		sum = sum + (float)1 / (float)n;
	}
	printf("Total number of additions completed: %d\n", limit);
	printf("FINAL VALUE: %f\n", sum);

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
