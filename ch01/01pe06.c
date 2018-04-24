/* 01pe06.c */
/* ===================================80 chars=============================== */

/*
Given the radius of a circle, write a program to compute and display its
area. Use a symbolic constant to define the PI value and assume a suitable
value for radius.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

#define PI 3.14159265359
#define RADIUS 3.0

int main(void)
{
	/* INPUT: Radius */
	float area;

	/* CALCULATE: Area */
	area = PI * RADIUS * RADIUS;
	printf("PI = %f\tRadius = %f\tArea = %f\n", PI, RADIUS, area);

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
