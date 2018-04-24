/* 02pe05.c  */

/* ===================================80 chars=============================== */

/*
	The price of one kg of rice is GBP16.75 and one kg of sugar is
	GBP 15.00.

	Write a program to get these values from the user and display the prices
	as follows:

	*** LIST OF ITEMS ***
	Item		Price
	Rice		GBP 16.75
	Sugar		GBP 15.00
*/

#include <stdio.h>

/*
	Required to prevent -> "scanf: floating point formats not linked"
*/
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

	float priceRice, priceSugar;

	printf("\n\n");
	printf("Enter the price of RICE (GBP, per kg):  ");
	scanf("%f", &priceRice);
	printf("Enter the price of SUGAR (GBP, per kg):  ");
	scanf("%f", &priceSugar);

	printf("\n\n");
	printf("*** LIST OF ITEMS ***\n");
	printf("Item\t\tPrice\n");
	printf("Rice\t\tGBP %*.*f per kg\n", 2, 2, priceRice);
	printf("Sugar\t\tGBP %*.*f per kg\n", 2, 2, priceSugar);
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
