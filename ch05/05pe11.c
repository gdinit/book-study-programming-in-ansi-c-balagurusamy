/* 05pe11.c */

/* ===================================80 chars=============================== */

/*
Write a program to read three integer values from the keyboard and display the
output stating whether they are the sides of a right angled triangle.

---
e.g.: 5 4 3 = right angled

Definition of a Right Angle
A right angle is an angle that measures exactly 90 degrees. It is exactly a
quarter of a circle. When you cut a pie into four equal pieces, the tip of each
slice will form a right angle.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Required to prevent -> "scanf: floating point formats not linked"
*/
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _doubleconvert;
#pragma extref _doubleconvert
#endif

/* CONFIGURATION */
#define TITLE "TRIANGLE RIGHT-ANGLENESS CHECKER"
#define LINESTOCLEARSCREEN 90

typedef struct Triangle_t {
	int a, b, c, x, y, z;
} Triangle;

void cls( void )
{
	int n;
	for ( n = 0; n < LINESTOCLEARSCREEN; n++ ) {
		printf( "\n" );
	}
}

void displayHeader( void )
{
	char	s [] = TITLE;
	int	tmp = 0;
	for ( tmp = 0; tmp < 66; tmp++ ) {
		printf( "-" );
	}
	printf( "\n%s\n", s );
}

void displayFooter( void )
{
	int tmp = 0;
	for ( tmp = 0; tmp < 66; tmp++ ) {
		printf( "-" );
	}
	printf( "\n" );
}

void getValues( Triangle* pt )
{
	printf(	"Please enter the three sides of triangle, "
		"separated with space: " );
	fflush( stdin );
	scanf( "%d%d%d", &( pt->a ), &( pt->b ), &( pt->c ) );
}

void calcXYZ( Triangle* pt )
{
	printf(	"One moment please: calculating x, y, z...\n" );
	pt->x = pt->a * pt->a;
	pt->y = pt->b * pt->b;
	pt->z = pt->c * pt->c;
	printf(	"Done.\n" );
}

void testDisplayRightAngle( const Triangle* pt )
{
	if ( ( pt->a > pt->b ) && ( pt->a > pt->c ) &&
	     ( pt->x == pt->y + pt->z ) ) {
		printf( "Triangle IS right-angled.\n" );
	} else {
		printf( "Triangle IS NOT right-angled.\n" );
	}
}

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char		ch = '\0';
	Triangle	t;
	Triangle*	pt = &t;
	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	cls();
	displayHeader();
	getValues( pt );
	printf( "Triangle Side Values are: %d %d %d\n", t.a, t.b, t.c );
	calcXYZ( pt );
	printf( "X, Y, Z Values are: %d %d %d\n", t.x, t.y, t.z );
	testDisplayRightAngle( pt );
	displayFooter();
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf( "\nPress space to quit\n" );
	/* disable input buffer */
	setvbuf( stdin,	0, _IONBF, 0 );
	while ( ( ch = getchar() ) != ' ' && ch != EOF ) {
	}
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

