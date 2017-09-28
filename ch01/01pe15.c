/* ch01.programing-exercise-15.c */

/* ===================================80 chars=============================== */

/*
        The line joining the points (2,2) and (5,6) which lie on the
        circumference of the circle is the diameter of the circle.
        Write a program to compute the area of the circle.
*/

/*
        Compiled & tested with:
        gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
/* Required for: exit() */
#include <stdlib.h>
/* Required for: sqrt() */
#include <math.h>
/* Required for: assertions */
#include <assert.h>
#include "round.h"

typedef struct {
	int x, y;
} Point;

#define P1X 2
#define P1Y 2
#define P2X 5
#define P2Y 6
#define PI 3.14159265359

/*
        Distance between two points (x₁, y₁) and (x₂, y₂) is governed by the
        formula:	D² = (x₂ - x₁)² + (y₂ - y₁)²
*/
int pointDistanceInt( Point p1, Point p2 )
{
	return round( sqrt( ( ( p2.x - p1.x ) * ( p2.x - p1.x ) ) +
			( ( p2.y - p1.y ) * ( p2.y - p1.y ) ) ) );
}

float pointDistanceFloat( Point p1, Point p2 )
{
	return sqrt( ( ( p2.x - p1.x ) * ( p2.x - p1.x ) ) +
		( ( p2.y - p1.y ) * ( p2.y - p1.y ) ) );
}

int main( void )
{
	/* Origin */
	Point	p1;
	/* Given Point */
	Point	p2;
	float	radiusFloat;
	float	diameterFloat;
	float	circumferenceFloat;
	float	areaFloat;

	/* origin */
	p1.x = P1X;
	p1.y = P1Y;
	/* given point */
	p2.x = P2X;
	p2.y = P2Y;

	radiusFloat = pointDistanceFloat( p2, p1 ) / 2;
	diameterFloat = ( float )2 * radiusFloat;
	circumferenceFloat = PI * diameterFloat;
	areaFloat = ( float )PI * radiusFloat * radiusFloat;

	printf( "\n\n" );
	printf( "--------------------------------------------\n" );
	printf( "INPUT\n\n" );
	printf( "Points\t\t\t: p1=%d,%d   p2=%d,%d\n", p1.x, p1.y, p2.x, p2.y );
	printf( "--------------------------------------------\n" );
	printf( "\n\n" );
	printf( "--------------------------------------------\n" );
	printf( "CALCULATION RESULTS\n\n" );
	printf( "*** FLOAT **********************************\n" );
	printf( "pointDistanceFloat (p2->p1 distance)\t: %f\n"
		,	pointDistanceFloat( p2, p1 ) );
	printf( "radiusFloat\t\t\t\t: %f\n",	radiusFloat );
	printf( "diameterFloat\t\t\t\t: %f\n",	diameterFloat );
	printf( "circumferenceFloat\t\t\t: %f\n"
		, circumferenceFloat );
	printf( "areaFloat\t\t\t\t: %f\n",	areaFloat );
	printf( "--------------------------------------------\n" );
	printf( "\n" );

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

