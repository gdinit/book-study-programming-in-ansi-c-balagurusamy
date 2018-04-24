/* 01pe08.c */
/* ===================================80 chars=============================== */

/*
ch01.programming-exercise 02:
Write a program that will print your mailing address in the following form:
First line	:	Name
Second line	:	Door No, Street
Third line	:	City, Pin code

ch01.programming-exercise 08:
Modify the above program to provide border lines to the address.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

int main(void)
{
	printf("First Line\t\t: Anthony Hopkins\n");
	printf("Second Line\t\t: |=====================|\n");
	printf("Third Line\t\t: | 21b, Park High Road\t|\n");
	printf("Fourth Line\t\t: | London, W1 G4U\t|\n");
	printf("Fifth Line\t\t: |=====================|\n\n");

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
