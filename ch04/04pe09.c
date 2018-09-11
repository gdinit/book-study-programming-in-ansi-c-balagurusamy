/* 04pe09.c */

/* ===================================80 chars=============================== */

/*
Write a program to read the name ANIL KUMAR GUPTA in three parts using the
scanf statement and to display the same in the following format using the
printf statement:
(a) ANIL K. GUPTA
(b) A. K. GUPTA
(c) GUPTA A. K.
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
#define MAXLEN 40

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printHeader(void)
{
	printf("-----------------------------------------------------\n");
}

void printFooter(void)
{
	printf("-----------------------------------------------------\n");
}

void getNames(char *pn1, char *pn2, char *pn3)
{
	fflush(stdin);
	printf("Enter Firstname Middlename Lastname: ");
	scanf("%s%s%s", pn1, pn2, pn3);
}

void printNames(char *pn1, char *pn2, char *pn3)
{
	printf("\nFirstname is read as: %-40s\n", pn1);
	printf("\nMiddlename is read as: %-40s\n", pn2);
	printf("\nLastname is read as: %-40s\n", pn3);
	printf("\n(a) %s %.1s. %s\n", pn1, pn2, pn3);
	printf("(b) %.1s. %.1s. %s\n", pn1, pn2, pn3);
	printf("(c) %s %.1s. %.1s.\n", pn3, pn1, pn2);
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char name1[MAXLEN];
	char name2[MAXLEN];
	char name3[MAXLEN];
	char *pn1 = &name1[0];
	char *pn2 = &name2[0];
	char *pn3 = &name3[0];
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	getNames(pn1, pn2, pn3);
	printNames(pn1, pn2, pn3);
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
