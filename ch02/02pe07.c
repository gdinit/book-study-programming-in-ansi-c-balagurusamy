/* 02pe07.c  */

/* ===================================80 chars=============================== */

/*
Write a program to do the following
(a) Declare x and y as integer variables, and z as short integer variable
(b) Assign two 6 digit numbers to x and y
(c) Assign the sum of x and y to z
(d) Output the values of x, y, and z
Comment on the output.
*/

#include <stdio.h>

#define NUM1 982442
#define NUM2 209348
#define LINESTOCLEARSCREEN 90

void cls( void )
{
	int n;

	for ( n = 0; n < LINESTOCLEARSCREEN; n++ )
		printf( "\n" );
}

int main( void )
{
	char		gotChar;

	int		x = NUM1, y = NUM2;
	short int	z = x + y;
	long int	x2 = NUM1, y2 = NUM2;

	cls();
	printf( "Supplied values were:\n"
		"\t\t\tx = %ld && y = %ld\n\n\n", x2, y2 );

	printf(	"Now, after assignments, variables hold the "
		"following incorrect values:\n"
		"\t\t\tx = %d\n"
		"\t\t\ty = %d\n"
		"\t\t\tz = %d\n", x, y, z );

	/* STANDARD END SECTION ********************************************* */

	/* Disable Input & Output buffers. */
	setvbuf(	stdout, 0,	_IONBF, 0 );
	setvbuf(	stdin,	0,	_IONBF, 0 );
	printf( "\n\n" );
	printf( "\n\nPress any key to quit \n" );
	gotChar = getchar();
	/* to suppress var not used! */
	gotChar = gotChar + 1;
	/* STANDARD END SECTION ********************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

