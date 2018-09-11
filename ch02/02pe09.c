/* 02pe09.c  */

/* ===================================80 chars=============================== */

/*
Write a program to illustrate the use of typedef declaration in a program
*/

/* Needed to stop annoying MS _s warnings when compiled with llvm on Windows! */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

typedef unsigned int Age;

int main(void)
{
	/* BEGIN: Declare Variables ***************************************** */
	char gotChar = '\0';
	Age age = 21;

	/* END: Declare Variables ******************************************* */

	/* BEGIN: Standard Footer Section *********************************** */
	printf("Age is: %d\n", age);
	/* END: Program Main() ********************************************** */

	/* BEGIN: Standard Footer Section *********************************** */

	/* Disable Input & Output buffers. */
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
	printf("\n\n");
	printf("\n\nPress any key to quit \n");
	gotChar = getchar();
	/* to suppress var not used! */
	gotChar += 1;
	fflush(stdout);
	/* END: Standard Footer Section ************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
