/* 08pe06.c */
/* ===================================80 chars=============================== */

/*
Write a program to replace a particular word by another word in a given string.
For example, the word "PASCAL" should be replaced by "C" in the text
"It is good to program in PASCAL language."
*/

/*
Compiled & tested with:
	gcc -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment 
	-Wparentheses -Wformat-zero-length 08pe06.c str5cpy.c -o binary/08pe06
*/

/*
Future Improvement Ideas
-shift to right if replace word is longer
-shift to left if search word is longer
-validate after each takeInput step
-rerun please "enter x: " if input is empty. after 3rd failure, give up & quit.
-fix the space to exit thing (make it cross platform or remove)
*/

#include <math.h>
#include <stdio.h>
/* exit(), EXIT_FAILURE */
#include <stdlib.h>
#include <string.h>
/* tolower() */
#include <ctype.h>
/* str5cpy (safe copy) */
#include "str5.h"

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
#define TITLE "STRING WORD REPLACER"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define TEXTMAXLEN 255
#define SEARCHMAXLEN 63
#define REPLACEMAXLEN 63
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 0

int str5cpy(char *dst, size_t dstsize, const char *src, size_t nb, size_t mode);

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

void getSearchWord(char *p_search_word)
{
	printf("Please enter the word to SEARCH: ");
	FLUSH;
	scanf("%" XSTR(SEARCHMAXLEN) "[^\n]", p_search_word);
}

void getReplaceWord(char *p_replace_word)
{
	printf("Please enter the word to REPLACE with: ");
	FLUSH;
	scanf("%" XSTR(REPLACEMAXLEN) "[^\n]", p_replace_word);
}

void getText(char *p_text)
{
	printf("Please enter the TEXT: ");
	FLUSH;
	scanf("%" XSTR(TEXTMAXLEN) "[^\n]", p_text);
}

void copyText(const char *p_text, char *p_new_text)
{
	int ret = 0;
	ret = str5cpy(p_new_text, TEXTMAXLEN, p_text, TEXTMAXLEN, NOTRUNC);
	if (ret < 0) {
		/* something went wrong with the str copy! */
		printf("ERROR: str5cpy returned %d!\n", ret);
		exit(EXIT_FAILURE);
	} else if (CFGDEBUG) {
		printf("OK\tNEW TEXT has been copied as: %s\n", p_new_text);
	}
}

int validateSize(const char *p_new_text, const char *p_search_word,
		 const char *p_replace_word)
{
	int nt_len = -1, sw_len = -1, rw_len = -1;

	nt_len = strlen(p_new_text);
	if (nt_len <= 0) {
		printf("new text length <= 0 [value = %d]!\n", nt_len);
		exit(EXIT_FAILURE);
	}
	sw_len = strlen(p_search_word);
	if (sw_len <= 0) {
		printf("search word length <= 0 [value = %d]!\n", sw_len);
		exit(EXIT_FAILURE);
	}
	rw_len = strlen(p_replace_word);
	if (rw_len <= 0) {
		printf("replace word length <= 0 [value = %d]!\n", rw_len);
		exit(EXIT_FAILURE);
	}
	if (sw_len < rw_len) {
		printf("ERROR: sw_len < rw_len! (shamefully, shifting is not implemented yet)\n");
		exit(EXIT_FAILURE);
	}
	if (CFGDEBUG) {
		printf("OK\tINPUT VALIDATION passed.\n\n");
	}
	return 0;
}

/*
 * findstr - Return Codes
 *	-1: error
 *	0: substring has been found in string
 *	1: substring has NOT been found in string
 */
int findStr(const char *p_string, const char *p_substr, char **p_pos)
{
	int ret = -1;
	*p_pos = strstr(p_string, p_substr);
	if (*p_pos == NULL) {
		ret = 1;
		if (CFGDEBUG) {
			printf("SEARCH: NOT FOUND!\tsubstr does NOT exist in "
			       "string\n");
		}
	} else {
		ret = 0;
		if (CFGDEBUG) {
			printf("SEARCH: FOUND!\tsubstr has been located in "
			       "string.\n\there is the substr: %s\n", *p_pos);
		}
	}
	return ret;
}

void replace(char *p_new_text, const char *p_search_word,
	     const char *p_replace_word)
{
	unsigned long int sw_len = strlen(p_search_word);
	unsigned long int rw_len = strlen(p_replace_word);
	unsigned long int n = 0;
	int ret = -1;
	int position = -1;
	char *p_pos = NULL;

	ret = findStr(p_new_text, p_search_word, &p_pos);
	if (ret == -1) {
		printf("ERROR: findStr returned %d!", ret);
		exit(EXIT_FAILURE);
	} else if (ret == 1) {
		/* not found = nothing to do */
	} else if (ret == 0) {
		/* found = replace here */
		/* TODO delete this debug print */
		if (CFGDEBUG) {
			printf("ret is zero (%d)\nsubstring is: %s\n\nProceeding "
			       "with replace...\n",
			       ret, p_pos);
		}
		position = p_pos - p_new_text;
		/* STEP 1: replace each char-array-slot with whitespace */
		for(n = 0; n < sw_len; n++) {
			p_new_text[position + n] = ' ';
		}

		/* STEP 2: stamp each char-array-slow with replace word */
		for(n = 0; n < rw_len; n++) {
			p_new_text[position + n] = p_replace_word[n];
		}
	}
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char text[TEXTMAXLEN + 1] = "";
	char new_text[TEXTMAXLEN + 1] = "";
	char search_word[SEARCHMAXLEN + 1] = "";
	char replace_word[REPLACEMAXLEN + 1] = "";
	char *p_text = text;
	char *p_new_text = new_text;
	char *p_search_word = search_word;
	char *p_replace_word = replace_word;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	printf("Note that only the very first occurence of SEARCH word will be "
	       "replaced with the\nREPLACE word.\n\n");
	getSearchWord(p_search_word);
	/* cast is needed for Borland 3.1 otherwise it prints 181453651 */
	printf("SEARCH word is set to: \"%s\"\tlen=%lu\n\n", p_search_word,
	       (unsigned long int) strlen(p_search_word));
	getReplaceWord(p_replace_word);
	printf("REPLACE word is set to: \"%s\"\tlen=%lu\n\n", p_replace_word,
	       (unsigned long int) strlen(p_replace_word));
	getText(p_text);
	printf("TEXT is set to: \"%s\"\tlen=%lu\n\n", p_text,
	       (unsigned long int) strlen(p_text));
	copyText(p_text, p_new_text);
	validateSize(p_new_text, p_search_word, p_replace_word);
	replace(p_new_text, p_search_word, p_replace_word);
	printf("Final text: \"%s\"\n", p_new_text);
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

/* ===================================80 chars=============================== */
/* EOF */
