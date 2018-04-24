/* 01pe07.c */
/* ===================================80 chars=============================== */

/*
Given two integers 20 and 10, write a program that uses a function add() to
add these two numbers and sub() to find the difference of these two numbers
and then display the sum and difference in the following form:
20 + 10 = 30
20 - 10 = 10
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

int add(int a, int b)
{
	int r;

	r = a + b;

	return r;
}

int sub(int a, int b)
{
	int r;

	r = a - b;

	return r;
}

int main(void)
{
#define NUM1 20
#define NUM2 10
	int result;
	result = add(NUM1, NUM2);
	printf("add(%d, %d) = %d\n", NUM1, NUM2, result);

	result = sub(NUM1, NUM2);
	printf("sub(%d, %d) = %d\n", NUM1, NUM2, result);

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
