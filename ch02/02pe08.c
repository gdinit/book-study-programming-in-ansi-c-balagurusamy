/* 02pe08.c  */

/* ===================================80 chars=============================== */

/*
Write a program to read two floating point numbers using a scanf statement,
assign their sum to an integer variable, and then output the values of all the
three variable.
*/

#include <stdio.h>

int main(void)
{
	char gotChar;
	float num1 = 0, num2 = 0;

	printf("Please enter two floating point numbers: ");
	scanf("%f %f", &num1, &num2);
	printf("\nFIRST number read as: %f", num1);
	printf("\nSECOND number read as: %f", num2);
	printf("\nQUOTIENT is: %d", (int)(num1 / num2));

	/* STANDARD END SECTION ********************************************* */

	/* Disable Input & Output buffers. */
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stdin, 0, _IONBF, 0);
	printf("\n\n");
	printf("\n\nPress any key to quit \n");
	gotChar = getchar();
	/* to suppress var not used! */
	gotChar = gotChar + 1;
	/* STANDARD END SECTION ********************************************* */

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
