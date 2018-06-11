/* 09pe15.c */
/* ===================================80 chars=============================== */

/*
 * Develop your own functions for performing following operations on strings:
 *
 * (a) Copying one string to another
 * (b) Comparing two strings
 * (c) Adding a string to the end of another string
 *
 * Write a driver program to test your functions.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 *	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 09pe15.c -o binary/09pe15
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <math.h> /* ceil() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort() */
#include <string.h> /* for title */
#include <time.h>   /* srand(time()) */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "STRING FUNCTIONS"
#define CFGDEBUG 0
#define STRING_MAX_SIZE  32
#define FAILURE -1
#define SUCCESS 0

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

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void myStrCpy(char * dst, int dstSize, const char * src);
int myStrCmp(const char *str1, const char *str2);
void myStrCat(char *dst, const char *src);

/* PROGRAM ENTRY POINT */
int main(void)
{
	int r;
	char s1[STRING_MAX_SIZE] = "First string";
	char s2[STRING_MAX_SIZE] = "Second string";

	cls();
	displayHeaderLine();
	displayHeaderText();

	printf("\n1) INITIAL STRINGS\n");
	printf("   s1: %s\n", s1);
	printf("   s2: %s\n", s2);


	r = myStrCmp(s1, s2);
	printf("\n2) STRING COMPARISON\n"
	       "   Executing `myStrCmp(s1, s2)`...\n"
	       "   Result is: %d\n", r);

	printf("\n3) STRING COPY\n"
	       "   Executing `myStrCpy(s2, sizeof(s2), s1)`...\n");
	myStrCpy(s2, sizeof(s2), s1);
	printf("   Strings After Copy Operation:\n");
	printf("   s1: %s\n", s1);
	printf("   s2: %s\n", s2);
	r = myStrCmp(s1, s2);
	printf("\n4) STRING CONCATENATION\n");
	printf("   Executing `myStrCat(s1, s2)`...\n");
	printf("   Strings After Concatenation Operation:\n");
	myStrCat(s1, s2);
	printf("   s1: %s\n", s1);
	printf("   s2: %s\n", s2);

	displayFooter();

	return EXIT_SUCCESS;
}
/**************************************/
void cls(void)
{
	int n;
	for (n = 0; n < LINES_TO_CLEAR_SCREEN; n++) {
		printf("\n");
	}
}

void displayHeaderLine(void)
{
	int n;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}

void displayHeaderText(void)
{
	char s[] = TITLE;
	printf("%s\n", s);
}

void displayFooter(void)
{
	int n = 0;
	for (n = 0; n < DASH_COUNT_FOR_HEADER_FOOTER; n++) {
		printf("-");
	}
	printf("\n");
}
/**************************************/
/* myStrCpy: copies the string pointed to by src (including the terminating null
 * character) to the destination array of size dstsize pointed to by dst.
 * Truncation is allowed.
 *
 * Return codes: 0 for success, -1 for error
 */
void myStrCpy(char * dst, int dstSize, const char * src)
{
	int n, nullSpotted = 0;

	/* keep copying till a null terminator has been found (copy it too)
	 * if null not found, quit copying after copying dstSize many chars */
	for (n = 0; n < dstSize && !nullSpotted; n++) {
		dst[n] = src[n];
		if(src[n] == '\0') {
			nullSpotted = 1;
			break;
		}
	}
}

/*
 * return value	indicates
 * <0 the first character that does not match has a lower value in ptr1 than in 
 *    ptr2
 * 0 the contents of both strings are equal
 * >0 the first character that does not match has a greater value in ptr1 than
 *    in ptr2
 */
int myStrCmp(const char *str1, const char *str2)
{
	unsigned long len1, len2, n;
	int r = 0;

	len1 = strlen(str1);
	len2 = strlen(str2);

	for(n = 0; n < strlen(str1); n++) {
		if (str1[n] != str2[n]) {
			r = str1[n] - str2[n];
			return r;
		}
	}
	return 0;
}

void myStrCat(char *dst, const char *src)
{
	int i, n;

	i = strlen(dst);

	for (n = 0; src[n] != '\0'; n++) {
		dst[i + n] = src[n];
	}
}

/* ===================================80 chars=============================== */
/* EOF */
