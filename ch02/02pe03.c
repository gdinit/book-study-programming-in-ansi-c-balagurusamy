/* 02pe03.c  */

/* ===================================80 chars=============================== */

/*
	Write a program that prints the even numbers from 1 to 100
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void)
{
	char noNeed;

	int num;

	printf("List of all even numbers between 1-100 (incl.):\n");
	for (num = 1; num <= 100; num++) {
		/* printf("Num is %d\n", num); */
		if (num % 2 == 0) {
			printf("%d\n", num);
		}
	}

	printf("Press any key to quit \n");
	noNeed = getchar();
	noNeed = getchar();
	/* to suppress var not used! */
	noNeed = noNeed + 1;

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
