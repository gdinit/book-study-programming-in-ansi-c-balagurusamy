/* 02pe06.c  */

/* ===================================80 chars=============================== */

/*
Write a program to count and print the number of negative and positive
numbers lastInput a given set of numbers. Test your program with a suitable set
of numbers. Use scanf to read the numbers. Reading should be terminated
when the value 0 is encountered.
*/

#include <stdio.h>

/* Required to prevent -> "scanf: floating point formats not linked" */
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

int promptReadFirstNumber(void)
{
	int lastInput_;

	printf("\n\n");
	printf("Enter the first number & press ENTER (0 to exit): ");
	scanf("%d", &lastInput_);

	return lastInput_;
}

int promptReadAdditionalNumber(void)
{
	int lastInput_;

	printf("\n\n");
	printf("Enter another number & press ENTER (0 to exit): ");
	scanf("%d", &lastInput_);

	return lastInput_;
}

void displayStats(int lastInput_, int negCount_, int posCount_)
{
	if (lastInput_ < 0) {
		printf("\n\nYou have entered a negative number (%d).\n\n",
		       lastInput_);
	} else if (lastInput_ > 0) {
		printf("\n\nYou have entered a positive number (%d).\n\n",
		       lastInput_);
	}
	printf("--- CURRENT STATS -----------------------\n"
	       "Negatives: %d\tPositives: %d\tTotal: %d\n"
	       "-----------------------------------------\n",
	       negCount_, posCount_, negCount_ + posCount_);
}

void displayFinalStats(int negCount_, int posCount_)
{
	printf("\n\n\nTERMINATION REQUESTED\n\n"
	       "--- FINAL STATS -----------------------\n"
	       "Negatives: %d\tPositives: %d\tTotal: %d\n"
	       "-----------------------------------------\n",
	       negCount_, posCount_, negCount_ + posCount_);
}

int main(void)
{
	char gotChar;
	static int lastInput, negCount, posCount, keepGoing;

	keepGoing = 1;
	negCount = 0;
	posCount = 0;

	lastInput = promptReadFirstNumber();
	if (lastInput == 0) {
		keepGoing = 0;
	} else if (lastInput < 0) {
		negCount += 1;
		displayStats(lastInput, negCount, posCount);
	} else if (lastInput > 0) {
		posCount += 1;
		displayStats(lastInput, negCount, posCount);
	}

	while (keepGoing) {
		lastInput = promptReadAdditionalNumber();
		if (lastInput == 0) {
			keepGoing = 0;
		} else if (lastInput < 0) {
			negCount += 1;
			displayStats(lastInput, negCount, posCount);
		} else if (lastInput > 0) {
			posCount += 1;
			displayStats(lastInput, negCount, posCount);
		}
	}
	displayFinalStats(negCount, posCount);

	printf("\n\n");
	printf("Press any key to quit \n");
	gotChar = getchar();
	gotChar = getchar();
	/* to suppress var not used! */
	gotChar = gotChar + 1;

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
