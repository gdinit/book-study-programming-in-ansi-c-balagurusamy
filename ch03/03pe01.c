/* 03pe01.c */

/* ===================================80 chars=============================== */

/*
Given the values of the variables x, y and z, write a program to rotate their
values such that x has the value of y, y  has the value of z, and z has the
value of x.
*/

/*
Compiled & tested with:
gcc -std=c89 -pedantic -Wall -Werror $filename.c -o binary/$filename
*/

#include <stdio.h>

#define X 10
#define Y 20
#define Z 30

int main( void )
{
	/* BEGIN: Declare Variables ***************************************** */
	char	gotChar = '\0';
	int	x = X, y = Y, z = Z, zz = 99;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Program Main Code ***************************************** */
	printf(	"\n|---------------------------------------|\n"
		"|\t      INITIAL VALUES\t\t|\n"
		"|\tx=%d\ty=%d\tz=%d\t\t|\n"
		"|---------------------------------------|\n"
		, x, y, z );
	zz = z;
	z = y;
	y = x;
	x = zz;
	printf(	"\n|---------------------------------------|\n"
		"|\t      SHIFTED VALUES\t\t|\n"
		"|\tx=%d\ty=%d\tz=%d\t\t|\n"
		"|---------------------------------------|\n"
		, x, y, z );
	/* END: Program Main Code ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */

	/* disable input & output buffers */
	setvbuf(	stdout, 0,	_IONBF, 0 );
	setvbuf(	stdin,	0,	_IONBF, 0 );
	printf( "\n\n" );
	printf( "\n\nPress any key to quit \n" );
	gotChar = getchar();
	/* required to suppress "Error: var not used!" */
	gotChar += 1;
	/* fflush( stdout ); */
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */

