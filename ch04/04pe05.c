/* 04pe05.c */

/* ===================================80 chars=============================== */

/*
Write an interactive program to demonstrate the process of multiplication. The
program should ask the user to enter two two-digit integers and print the
product of integers as shown below.

		  45
	x         37
	------------
    7 x 45 is	 315
    3 x 45 is    135
	------------
    Add them    1665
	------------
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

typedef struct twoInt_t {
	int n1;
	int n2;
} twoInt;

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printHeader(void)
{
	printf("-------------- TWO INT MULTIPLICATION --------------\n");
}

void printFooter(void)
{
	printf("----------------------------------------------------\n");
}

unsigned int countDigits(unsigned int i)
{
	unsigned int ret = 1;
	while (i /= 10) {
		ret++;
	}

	return ret;
}

int valNums(twoInt *pti)
{
	if (countDigits(pti->n1) == 2 && countDigits(pti->n2) == 2) {
		return 1;
	} else {
		return 0;
	}
}

void getNumbers(twoInt *pti)
{
	printf("Please enter two two-digit integers: ");
	scanf("%d %d", &(pti->n1), &(pti->n2));
}

/* break apart a number, save digits as separate variables in an array */
void breakApartNum(int n, char *parr)
{
	unsigned int digits = 0;
	digits = countDigits(n);
	while (digits--) {
		parr[digits] = n % 10;
		n /= 10;
	}
}

void printSolution(twoInt *pti, char *parr)
{
	int c, i, n, d0, d1;
	c = i = n = d0 = d1 = 0;
	n = pti->n2;
	c = countDigits(n);
	d0 = parr[0];
	d1 = parr[1];
	printf("\n");
	printf("\t\t\t%4d\n", pti->n1);
	printf("\t\tx\t%4d\n", pti->n2);
	printf("\t\t------------\n");
	printf("\t%d x %d   is\t%4d\n", parr[1], pti->n1, parr[1] * pti->n1);
	printf("\t%d x %d   is\t%4d\n", parr[0], pti->n1, parr[0] * pti->n1);
	printf("\t\t------------\n");
	printf("\tAdd them\t%4d\n",
	       (parr[1] * pti->n1) + (parr[0] * pti->n1) * 10);
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	twoInt ti;
	twoInt *pti = &ti;
	char arr[2] = {'\0'};
	char *parr = &arr[0];

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	do {
		getNumbers(pti);
	} while (valNums(pti) != 1);
	breakApartNum(pti->n2, parr);
	printSolution(pti, parr);
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
