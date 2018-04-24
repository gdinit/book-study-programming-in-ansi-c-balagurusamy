/* 02pe04.c  */

/* ===================================80 chars=============================== */

/*
	Write a program that requests two float type numbers from the user and
	then divides the first number by the second and display the result along
	with the numbers.
*/

#include <stdio.h>

/* Required to prevent -> "scanf: floating point formats not linked" */
#ifdef _WIN32
#elif defined __unix__
#elif defined __APPLE__
#else
extern unsigned _floatconvert;
#pragma extref _floatconvert
#endif

int main(void)
{
	char noNeed;

	float num1, num2, divResult;

	printf("Enter first floating point number: ");
	scanf("%f", &num1);
	printf("Enter second floating point number: ");
	scanf("%f", &num2);

	divResult = num1 / num2;

	printf("number1 = %f\n", num1);
	printf("number2 = %f\n", num2);
	printf("---------\n");
	printf("result = %f\n", divResult);

	printf("\n\n");
	printf("Press any key to quit \n");
	noNeed = getchar();
	noNeed = getchar();
	/* to suppress var not used! */
	noNeed = noNeed + 1;

	return 0;
}

/* ===================================80 chars=============================== */

/* EOF */
