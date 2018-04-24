/* 05pe01.c */

/* ===================================80 chars=============================== */

/*
Write a program to determine whether a given number is 'odd' or 'even' and print
the message:
NUMBER IS EVEN
or
NUMBER IS ODD
(a) without using else option, and
(b) with else option
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

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

void printHeader(void)
{
	printf("-----------------------------------------------------------\n"
	       "EVEN/ODD DETECTOR\n");
}

void printFooter(void)
{
	printf("Thanks and have a nice day!\n"
	       "-----------------------------------------------------------\n");
}

int getRetNum(void)
{
	int n = -9999;
	printf("Please enter an integer (0 to exit) and press ENTER: ");
	scanf("%d", &n);

	return n;
}

void checkRepNumA(int n)
{
	if (n % 2 == 0) {
		printf("NUMBER %d IS EVEN!\n", n);

		return;
	}
	printf("NUMBER %d IS ODD!\n", n);
}

void checkRepNumB(int n)
{
	if (n % 2 == 0) {
		printf("NUMBER %d IS EVEN!\n", n);
	} else {
		printf("NUMBER %d IS ODD!\n", n);
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	int num = 1;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	do {
		num = getRetNum();
		if (num != 0) {
			checkRepNumA(num);
		}
	} while (num != 0);
	printFooter();

	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf("\n\n\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
