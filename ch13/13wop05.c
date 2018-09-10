/* 13wop05.c */
/* ===================================80 chars=============================== */

/*
 * Worked Out Problem 13.4
 *
 * Write a function to insert a given item before a specified node known as key
 * node.
 */

/*
 * Compiled & tested on:
 *	Apple LLVM version 9.1.0 (clang-902.0.39.1)
 *	Target: x86_64-apple-darwin17.5.0
 * with:
 * 	clang -x c -std=c89 -pedantic-errors -Wall -Werror -Wextra -Wcomment \
 *	-Wparentheses -Wformat-zero-length 13wop05.c -o binary/13wop05
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
#define TITLE "LINKED LIST - DELETION DEMO"
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
node * insert(node *head);
node * find(node *list, int key);
node * delete(node *head);

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

	/*
	printf("inserting an item...\n");
	insert(head);
	*/
	printf("deleting an item...\n");
	delete(head);
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

node *insert(node *head)
{
	node *find(node *p, int a);
	node *new; /* pointer to new node */
	node *n1; /* pointer to node preceding key node */
	int key;
	int x; /* new item (number) to be inserted */

	printf("Value of new item?");
	scanf("%d", &x);
	printf("Value of key item? (type -999 if last) ");
	scanf("%d", &key);

	if(head->number == key) /* new node is first */ {
		new = (node *)malloc(sizeof(node));
		new->number = x;
		new->next = head;
		head = new;
	} else { /* find key node and insert new node before the key node */
		n1 = find(head, key); /* find key node */

		if (n1 == NULL) {
			printf("\nkey is not found\n");
		} else {
			new = (node *)malloc(sizeof(node));
			new->number = x;
			new->next = n1->next;
			n1->next = new;
		}
	}
	return(head);
}

node *find(node *list, int key)
{
	if (list->next->number == key) { /* key found */
		return(list);
	} else {
		if (list->next->next == NULL) { /* end */
		return(NULL);
		} else {
			find(list->next, key);
			return(NULL);
		}
	}
}

node * delete(node *head)
{
	node *find(node *p, int a);
	int key; /* item to be deleted */
	node *n1; /* pointer to node preceding key node */
	node *p; /* temporary pointer */

	printf("\nWhat is the item (number) to be deleted?");
	scanf("%d", &key);
	if(head->number == key) { /* first node to be deleted */
		p = head->next; /* pointer to 2nd node in list */
		free(head); /* release space of key node */
		head = p; /* make head point to 1st node */
	} else {
		n1 =  find(head, key);
		if (n1 == NULL) {
			printf("\nkey not found\n");
		} else { /* delete key node */
			p = n1->next->next; /* pointer to the node following
					     * the key node */
			free(n1->next); /* free key node */
			n1->next = p; /* establish link */
		}
	}
	return(head);
}
	/* USE FUNCTION find() HERE */

/* ===================================80 chars=============================== */
/* EOF */
