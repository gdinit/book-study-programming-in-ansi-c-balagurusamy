/* 08pe12.c */
/* ===================================80 chars=============================== */

/*
Write a program to read a line of text from the keyboard and print out the
number of occurrences of a given substring using the function strstr().
*/

/*
Compiled & tested with:
	gcc -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment
	-Wparentheses -Wformat-zero-length 08pe12.c -o binary/08pe12
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
/* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <stdlib.h>
#include <string.h>
/* tolower() */
#include <ctype.h>

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
#define TITLE "SUBSTRING COUNTER"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define TEXTMAXLEN 80
#define WORDMAXLEN 12
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 0

/* FUNCTION PROTOTYPES */
void cls(void);
void displayHeader(void);
void displayFooter(void);
void getText(char *t);
void getWord(char *w);
void searchCountPrint(char *word, char *text);

/* PROGRAM ENTRY POINT */
int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char text[TEXTMAXLEN + 1] = "";
	char word[WORDMAXLEN + 1] = "";
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	getText(text);
	printf("Text is set to: \"%s\"\n\n", text);

	getWord(word);
	printf("Word is set to: \"%s\"\n", word);

	searchCountPrint(word, text);

	displayFooter();
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	/* TODO space works in DOS but is not cross platform. fix or remove */
	printf("\nPress space to quit\n");
	/* disable input buffer */
	setvbuf(stdin, 0, _IONBF, 0);
	while ((ch = getchar()) != ' ' && ch != EOF) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* FUNCTIONS */
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

void getText(char *t)
{
	printf("Please enter the text to be searched (" XSTR(TEXTMAXLEN) 
	       " chars max): ");
	FLUSH;
	scanf("%" XSTR(TEXTMAXLEN) "[^\n]", t);
}

void getWord(char *w)
{
	printf("Please enter the word to look for in the text (" 
	       XSTR(WORDMAXLEN) " chars max): ");
	FLUSH;
	scanf("%" XSTR(WORDMAXLEN) "[^\n]", w);
}

void searchCountPrint(char *word, char *text)
{
	int w_len, t_len;

	t_len = strlen(text);
	if (t_len == 0) {
		printf("\nERROR: text length = 0!\n");
		exit(EXIT_FAILURE);
	}

	w_len = strlen(word);
	if (w_len == 0) {
		printf("\nERROR: search word length == 0!\n");
		exit(EXIT_FAILURE);
	}

	if (w_len > t_len) {
		printf("\nERROR: search word is longer than the text!\n");
		exit(EXIT_FAILURE);
	}
	if (CFGDEBUG) {
		printf("\n[DEBUG] SUCCESS:\tINPUT VALIDATION passed.\n");
		printf("[DEBUG] Text is set to: \"%s\"\n", text);
		printf("[DEBUG] Word is set to: \"%s\"\n", word);
		printf("[DEBUG] word_len is: %d\n", w_len);
		printf("[DEBUG] text_len is: %d\n", t_len);
	}


	/* OK, go ahead with the search & count */
	{
		char *p = text;
		int count = 0;

		while ((p = strstr(p, word)) != NULL ) {
			count++;
			p++;
		}
		/* report */

		printf("\nThe substring '%s' appears %d times in '%s'\n",
			word, count, text);
	}
}
/* ===================================80 chars=============================== */
/* EOF */
