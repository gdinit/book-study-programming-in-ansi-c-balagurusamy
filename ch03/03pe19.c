/* 03pe19.c */

/* ===================================80 chars=============================== */

/*
Write a program that determines whether a given integer is odd or even and
displays the number and description on the same line.
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
/* Configuration */
#define NUMBEG 0
#define NUMEND 100
#define NUMINC 10

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

/* print cos(x) and sin(x) for a given x(degrees) */
int getRetNum(void)
{
	int n = -9999, i = 0;

	printf("Please enter an integer (0 to exit) and press ENTER: ");
	i = scanf("%d", &n);

	/*
	if(i >= 1) {
		printf("\tNew number read: %d\n", n);
	} else {
		printf("\n");
	}
	*/
	return n;
}

/* Check and report a given integer's even/oddness */
int checkRepNum(int n)
{
	if (n % 2 == 0) {
		printf("number %d is even!\n", n);
	} else {
		printf("number %d is odd!\n", n);
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
			checkRepNum(num);
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
