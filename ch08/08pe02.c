/* 08pe02.c */
/* ===================================80 chars=============================== */

/*
Write a program to do the following:
(a) output the question "Who is the inventor of C?"
(b) accept an answer.
(c) print out "Good" and then stop, if the answer is correct.
(d) output the message "Try again", if the answer is wrong.
(e) display the correct answer when the answer is wrong even at the third
    attempt and stop.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
/* exit(), EXIT_FAILURE */
#include <math.h>
#include <stdlib.h>
#include <string.h>
/* tolower() */
#include <ctype.h>

/*
Required to prevent -> "scanf: floating point formats not linked"
*/
/*
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
extern		_floatconvert;
#pragma extref _floatconvert
#endif
*/

/* BEGIN: FLUSH */
#ifdef _WIN32
#define FLUSH fflush(stdin);
#elif defined __unix__
#define FLUSH fpurge(stdin);
#elif defined __APPLE__
#define FLUSH fpurge(stdin);
#else
#define FLUSH fflush(stdin);
#endif
/* END: FLUSH */

/* CONFIGURATION */
#define TITLE "INVENTOR OF C"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
#define INPUTMAXLEN 32
#define MAXTRIES 3
#define CFGDEBUG 0

void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeader(void)
{
	char s[] = TITLE;
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n%s\n\n", s);
}

void displayFooter(void)
{
	int tmp = 0;
	for (tmp = 0; tmp < DASH_COUNT_FOR_HEADER_FOOTER; tmp++) {
		printf("-");
	}
	printf("\n");
}

void clearInput(char *pUserInput)
{
	int n;
	for (n = 0; n < INPUTMAXLEN; n++) {
		pUserInput[n] = '\0';
	}
}
void printQandPrompt(void)
{
	printf("Who is the inventor of C?\tEnter the first and lastname: ");
}

/* get name from the user and save it in an array */
void getInput(char *pUserInput)
{
	FLUSH;
	scanf("%" XSTR(INPUTMAXLEN) "[^\n]", pUserInput);
}

/* return: 0=SUCCESS, 1=FAILURE */
int validate(char *pCorrectAnswer, char *pUserInput)
{
	int i, len = strlen(pUserInput), ret = 1, keepGoing = 1;

	if (len != strlen(pCorrectAnswer)) {
		if (CFGDEBUG) {
			printf("\nDEBUG: ERROR\tLength mismatch failure!\n");
		}
		return ret;
	} else {
		if (CFGDEBUG) {
			printf("\nDEBUG: OK Lengths match.\n");
		}
	}
	for (i = 0; i < len && keepGoing == 1; i++) {
		ret = 0;
		if (tolower(pUserInput[i]) != tolower(pCorrectAnswer[i])) {
			if (CFGDEBUG) {
				printf("DEBUG: ERROR\tMismatch detected at "
				       "character %2d (%c)!\n",
				       i + 1, pUserInput[i]);
			}
			len = 0;
			ret = 1;
			keepGoing = 0;
			break;
		} else {
			if (CFGDEBUG) {
				printf(
				    "DEBUG: OK\tCharacter %2d (%c) is a match."
				    "\n",
				    i + 1, pUserInput[i]);
			}
		}
	}
	return ret;
}

void mainLoop(char *pCorrectAnswer, char *pUserInput)
{
	int attemptCount = 1, guessedRight = 0;
	for (; attemptCount <= MAXTRIES && guessedRight != 1; attemptCount++) {
		printQandPrompt();
		clearInput(pUserInput);
		getInput(pUserInput);
		if (validate(pCorrectAnswer, pUserInput) == 0) {
			guessedRight = 1;
		}
		if (guessedRight == 1) {
			printf("Good\n");
			continue;
		} else {
			if (attemptCount == MAXTRIES) {
				printf(
				    "Sorry - too many (%d) incorrect answers"
				    "!\n\nCORRECT ANSWER was %s!\nGoodbye.\n",
				    MAXTRIES, pCorrectAnswer);

			} else {
				printf("Try again (wrong answers = %d)\n\n",
				       attemptCount);
			}
		}
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char correctAnswer[] = "Dennis Ritchie";
	char *pCorrectAnswer = &correctAnswer[0];
	char userInput[INPUTMAXLEN] = {'\0'};
	char *pUserInput = &userInput[0];
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	mainLoop(pCorrectAnswer, pUserInput);
	displayFooter();
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
