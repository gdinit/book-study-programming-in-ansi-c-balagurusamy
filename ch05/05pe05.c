/* 05pe05.c */

/* ===================================80 chars=============================== */

/*
Admission to a professional course is subject to the following condition:
(a) Marks in Mathematics >= 60
(b) Marks in Physics >= 50
(c) Marks in Chemistry >= 40
(d) Total in all three subjects >= 200
or
Total in Mathematics and Physics >= 150.

Given the marks in the three subjects, write a program to process the
applications to list the eligible candidates.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
#define MAX_SUBJECTS 3
#define BLANK_MARK -1
#define COL_SIZE 20

void cls(void)
{
	int n;
	for (n = 0; n < LINESTOCLEARSCREEN; n++) {
		printf("\n");
	}
}

void printHeader(void)
{
	printf("----------------------------------------\n"
	       "COURSE ADMISSION EVALUATION\n");
}

void printFooter(void) { printf("----------------------------------------\n"); }

void initMarks(int *pmarks)
{
	int n;
	n = 0;
	for (n = 0; n < MAX_SUBJECTS; n++) {
		pmarks[n] = BLANK_MARK;
	}
}

void printSubject(int id)
{
	if (id == 0) {
		printf("[Mathematics]");
	} else if (id == 1) {
		printf("[Physics]");
	} else if (id == 2) {
		printf("[Chemistry]");
	}
}

void getMarks(int *pmarks)
{
	int n = 0, in = 0, mat = 0, pyh = 0, che = 0, id = 0;
	do {
		printSubject(id);
		printf(" Enter between 0 and 100, or -1 to abort: ");
		fflush(stdin);
		scanf("%d", &in);
		if (in >= 0 && in <= 100) {
			pmarks[n] = in;
			printf("Mark read as %.2d\n\n", in);
			n++;
			id++;
			/* evaluate early pass */
			if (n == 2 && pmarks[0] + pmarks[1] >= 150) {
				printf(
				    "Candidate is ELIGIBLE for the course.\n");

				return;
			}
		} else if (in < -1 || in > 100) {
			printf("ERROR: %2d is not a valid mark and has been "
			       "discarded!\n",
			       in);
			in = 101;
		} else if (in == -1) {
			printf("\nAborting on user request!\n");

			return;
		}
	} while (in >= 0 && n < MAX_SUBJECTS);
}

void prepPrintReport(int *pmarks)
{
	int passed = 0;
	if ((pmarks[0] >= 60 && pmarks[1] >= 50 && pmarks[2] >= 40 &&
	     pmarks[0] + pmarks[1] + pmarks[2] >= 200) ||
	    (pmarks[0] + pmarks[1] >= 150)) {
		passed = 1;
		printf("Candidate is ELIGIBLE for the course.\n");
	} else {
		printf("Candidate IS NOT ELIGIBLE for the course.\n");
	}
}

void printAllMarks(int *pmarks)
{
	int n = 0, col = 0;
	printf("\nTOTAL SUBJECTS = %.2d\n", MAX_SUBJECTS);
	for (n = 0; n < MAX_SUBJECTS; n++) {
		printSubject(n);
		if (pmarks[n] == -1) {
			printf(" __\n");
		} else {
			printf(" %.2d\n", pmarks[n]);
		}
		col++;
		if (col < COL_SIZE) {
			printf("");
		} else {
			printf("\n");
			col = 0;
		}
	}
	printf("\n");
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	int marks[MAX_SUBJECTS] = {-1};
	int *pmarks = &marks[0];
	int readCount = 0;
	int *preadCount = &readCount;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	printHeader();
	initMarks(pmarks);
	printAllMarks(pmarks);
	getMarks(pmarks);
	printAllMarks(pmarks);
	prepPrintReport(pmarks);
	printFooter();

	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf("\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
