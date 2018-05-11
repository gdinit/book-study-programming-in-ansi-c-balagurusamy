/* 08pe08c.c */
/* ===================================80 chars=============================== */

/*
Write a program that reads a string from the keyboard and determines whether the
string is a palindrome or not. (A string is a palindrome if it can be read from
left and right with the same meaning. For example, Madam and Anna are palindrome
strings. Ignore capitalization).
*/

/*
Compiled & tested with:
	gcc -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment
		-Wparentheses -Wformat-zero-length 08pe08.c -o binary/08pe08
*/

/*
Future Improvement Ideas
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
/* 
NOT NEEDED for this exercise 
#include "str5.h"
*/

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
#define TITLE "PALINDROME DETECTOR"
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STRMAXLEN 64
/* needed to set macro-variable buffer size for scanf() */
#define STR(x) #x
#define XSTR(x) STR(x)
#define CFGDEBUG 0

/*
int str5cpy(char *dst, size_t dstsize, const char *src, size_t nb, size_t mode);
*/

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

void getStr(char *p_str)
{
	printf("Please enter a string to test for PALINDROME (max " 
		XSTR(STRMAXLEN) " chars): ");
	FLUSH;
	scanf("%" XSTR(STRMAXLEN) "[^\n]", p_str);
}

void toLowerStr(char *p_str)
{
	unsigned long int n;
	unsigned long int len = strlen(p_str);

	for (n = 0; n < len; n++) {
		p_str[n] = tolower(p_str[n]);
	}
}

int validateSize(const char *p_str)
{
	unsigned long int len = 0;

	len = strlen(p_str);
	if (len == 0) {
		printf("STRING size is zero!\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}

/* RETURN values
	-1:	error
	 0:	not a palindrome
	 1:	it is a palindrome
*/
int checkPalindrome(char *p_str)
{
	unsigned long int forward = 0;
	unsigned long int backward = 0;
	unsigned long int flen = 0;
	int palindrome;

	/*
	1	5
	2       4
	3       3
	4       2
	5       1
	*/
	flen = strlen(p_str);
	if(CFGDEBUG) {
		printf("The string I got is: \"%s\"\tlen=%lu\n", p_str, flen);
	}
	forward = 0;
	backward = flen - 1;
	/* assume palindrome, until a character in string proves us wrong */
	palindrome = 1;
	for ( ; forward < flen; (forward++, backward--) ) {
		if(CFGDEBUG) {
			printf("forward char is \"%c\"\tbackward char is \"%c\""
			       "\n", p_str[forward], p_str[backward]);
		}
		if (p_str[forward] != p_str[backward]) {
			palindrome = 0;
		}
	}
	return palindrome;
}

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char ch = '\0';
	char str[STRMAXLEN + 1] = "";
	char *p_str = str;
	int ret = -1;
	unsigned long int len = 0;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();

	getStr(p_str);
	if(validateSize(p_str) != 0) {
		printf("ERROR: validateSize returned an error!\n");
		exit(EXIT_FAILURE);
	}
	/* delete this - cast is no more! */
	/* cast is needed for Borland 3.1 otherwise it prints 181453651 */
	toLowerStr(p_str);
	len = strlen(p_str);
	printf("STRING is set to: \"%s\"\tlen=%lu\n", p_str, len);

	ret = checkPalindrome(p_str);
	if (ret == -1) {
		printf("ERROR: return value is -1!\n");
	} else if (ret == 0) {
		printf("TEST RESULT: Not a palindrome.\n");
	} else if (ret == 1) {
		printf("TEST RESULT: It's a palindrome!\n");
	}

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
