/* ch01.sample-program-05.c */

/* ===================================80 chars=============================== */

/*____________ PROGRAM USING COSINE FUNCTION ____________ */
#include <math.h>

#define PI 3.1416
#define MAX 180

main()
{
	int	angle;
	float	x, y;
	angle = 0;
	printf( "Angle      Cos(angle)\n\n" );
	while ( angle <= MAX ) {
		x = ( PI / MAX ) * angle;
		y = cos( x );
		printf( "%15d %13.4f\n", angle, y );
		angle = angle + 10;
	}
}

/* ===================================80 chars=============================== */

/* EOF */

