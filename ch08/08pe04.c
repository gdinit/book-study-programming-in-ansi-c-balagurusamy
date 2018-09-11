/* 08pe04.c */
/* ===================================80 chars=============================== */

/*
Write a program which will read a text and count all occurences of a
particular word.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
/* exit(), EXIT_FAILURE */
#include <math.h>
#include <stdlib.h>
#include <string.h>
/* tolower() */
/* #include <ctype.h> */

/*
Required to prevent -> "scanf: floating point formats not linked" in Borland 3
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
#define TITLE "WORD COUNTER"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define WORDMAXLEN 64
#define TEXTMAXLEN 512
#define STR(x) #x
#define XSTR(x) STR(x)
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

/* remove whitespace, remove anything after first whitespace */
void strip(char *pword)
{
	int n, len = strlen(pword), cleaningNeeded = 0;
	if (CFGDEBUG) {
		printf("DEBUG: pword length is: %d chars\n", len);
	}
	for (n = 0; cleaningNeeded == 0 && n < len; n++) {
		if (pword[n] == ' ') {
			if (CFGDEBUG) {
				printf("DEBUG: whitespace char found; strip"
				       "needed!\n");
			}
			cleaningNeeded = 1;
			continue;
		}
	}
	if (cleaningNeeded) {
		for (n = 0; n < len; n++) {
			if (pword[n] == ' ') {
				pword[n] = '\0';
				break;
			}
		}
	}
}

void printPreWord(void)
{
	printf("\nThis program will count how many times a search word appears"
	       " in a user-supplied text.\n"
	       "Type in the search word (" XSTR(WORDMAXLEN) " chars max): ");
}

void printPostWord(char *pword)
{
	if (CFGDEBUG) {
		printf("DEBUG: Pre-strip search word is read as: \"%s\"\n",
		       pword);
	}
	strip(pword);
	if (CFGDEBUG) {
		printf("DEBUG: Post-strip search word is set to: \"%s\"\n",
		       pword);
	} else {
		printf("Search word is set to: \"%s\"\n", pword);
	}
}

void getWord(char *pword)
{
	FLUSH;
	scanf("%" XSTR(WORDMAXLEN) "[^\n]", pword);
}

void getText(char *pword)
{
	FLUSH;
	scanf("%" XSTR(TEXTMAXLEN) "[^\n]", pword);
}

void searchCountAndReport(char *pword, char *ptext)
{
	/* progressing in a word */
	int inWord;
	/* length of text & word */
	int lent, lenw;
	/* position in search text/word, hit count */
	int post, posw, hits;
	int it;

	/* pre-search text  */
	printf("\nSearch Word = \"%s\"\n", pword);
	printf("Search Text = \"%s\"\n", ptext);

	/* search here... */
	/*
	NOTES
	state could be one of these:
		1) outsideword & searching for firstletter
		2) inword & searching nextLetter
	increment 'count' variable upon full hit only
ab	<- search word
abab	<- text
	int inWord = 0;
	int lent = 0;
	int posw, post, count;
	*/
	lent = strlen(ptext);
	lenw = strlen(pword);
	posw = 0;
	post = 0;
	hits = 0;
	inWord = 0;
	it = 0;
	for (; post < lent; (post++, posw++, it++)) {
		if (CFGDEBUG) {
			printf("for-loop-iteration begins run #%d\t"
			       "post=%d posw=%d\tchars text=%c word=%c\n",
			       it + 1, post, posw, ptext[post], pword[posw]);
		}
		/* in word stuff here */
		if (inWord == 1) {
			/* end-of-search-word AND a match */
			if (posw + 1 == lenw && ptext[post] == pword[posw]) {
				if (CFGDEBUG) {
					printf("A hit!\tposw == lenw\n\tAND\n"
					       "\tptext[post(%d)] %c == pword"
					       "[posw(%d)] %c\n",
					       post, ptext[post], posw,
					       pword[posw]);
				}
				hits++;
				inWord = 0;
				/* posw must start from the beginning */
				posw = -1;
				/* end-of-search-word AND no match */
			} else if (posw + 1 == lenw &&
				   ptext[post] != pword[posw]) {
				if (CFGDEBUG) {
					printf("end-of-search-word AND no match"
					       "\n");
				}
				inWord = 0;
				/* posw must start from the beginning */
				posw = -1;
				/* did we just miss a match here? */
				post--;
				post--;
				/* no end-of-search-word AND match */
			} else if (posw + 1 != lenw &&
				   ptext[post] == pword[posw]) {
				if (CFGDEBUG) {
					printf("no end-of-search-word AND match"
					       "\n");
				}
				/* no end-of-search-word AND match */
			} else if (posw + 1 != lenw &&
				   ptext[post] == pword[posw]) {
				if (CFGDEBUG) {
					printf("no end-of-search-word "
					       "AND match\n");
				}
				/* no end-of-search-word AND no match */
			} else if (posw + 1 != lenw &&
				   ptext[post] != pword[posw]) {
				if (CFGDEBUG) {
					printf("no end-of-search-word AND no "
					       "match [%c] != [%c]\n",
					       ptext[post], pword[posw]);
				}
				inWord = 0;
				/* posw must start from the beginning */
				posw = -1;
			}
			/* outsideword stuff here */
		} else {
			/* do we have a hit on search word 1st letter? */
			if (ptext[post] == pword[posw]) {
				if (CFGDEBUG) {
					printf("FIRST LETTER HIT: ptext[post=%d"
					       "/%c] == pword[posw=%d/%c]\n",
					       post, ptext[post], posw,
					       pword[posw]);
				}
				/* yes we have a hit! */
				inWord = 1;
			} else {
				/* no hit - keep looking for the 1st char! */
				/* posw must start from the beginning */
				posw = -1;
			}
		}
	}

	/* post search text */
	printf("COUNT = %d\n", hits);
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char text[TEXTMAXLEN + 1];
	char *ptext = &text[0];
	char word[WORDMAXLEN + 1] = "";
	char *pword = &word[0];
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	printPreWord();
	getWord(pword);
	printPostWord(pword);

	printf("\nNow, type in the text to search in (" XSTR(
	    TEXTMAXLEN) " chars max): ");
	getText(ptext);
	printf("Text is set to: \"%s\"\n", ptext);

	/* search for WORD in TEXT, count occurrences, print result */
	searchCountAndReport(pword, ptext);

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
