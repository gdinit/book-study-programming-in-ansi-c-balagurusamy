/* 13wop03.c */
/* ===================================80 chars=============================== */

/*
 * Worked Out Problem 13.3
 *
 * Write a program to create a linear linked list interactively and print out
 * the list and the total number of items in the list.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 13wop03.c -o binary/13wop03
 */

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h> /* tolower() */
#include <stdio.h>
#include <stdlib.h> /* exit(), EXIT_FAILURE, strtol(), qsort(), atoi()) */
#include <string.h> /* for title */

/* CONFIGURATION */
#define LINES_TO_CLEAR_SCREEN 90
#define DASH_COUNT_FOR_HEADER_FOOTER 66
#define STR(x) #x
#define XSTR(x) STR(x)
/**************************************/
#define TITLE "LINKED LIST DEMO"
#define CFGDEBUG 1
#ifndef NULL
#define NULL 0
#endif

struct linked_list {
	int number;
	struct linked_list *next;
};

typedef struct linked_list node;

void cls(void);
void displayHeaderLine(void);
void displayHeaderText(void);
void displayFooter(void);
/**************************************/
void create(node *p);
void print(node *p);
int count(node *p);

/* PROGRAM ENTRY POINT */
int main(void)
{
	node *head;

	cls();
	displayHeaderLine();
	displayHeaderText();
	printf("\n");

	head = (node *)malloc(sizeof(node));
	create(head);
	printf("\n");
	print(head);
	printf("\n");
	printf("\nNumber of items = %d\n", count(head));;

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
void create(node *list)
{
	printf("Input a number\t(type -999 at end): ");
	scanf("%d", &list->number);

	if (-999 == list->number) {
		list->next = NULL;
	} else { /* create next node */
		list->next = (node *)malloc(sizeof(node));
		create(list->next); /* recursion occurs  */
	}

	return;
}

void print(node *list)
{
	if (list->next != NULL) {
		printf("%d-->", list->number); /*print current item*/

		if (list->next->next == NULL) {
			printf("%d", list->next->number);
		}

		print(list->next); /*move to next item*/
	}
	return;
}

int count(node *list)
{
	if (list->next == NULL) {
		return (0);
	} else {
		return (1 + count(list->next));
	}
}

/* ===================================80 chars=============================== */
/* EOF */
