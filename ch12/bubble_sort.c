/*
 * C Bubble Sort implementation
 *
 * Authors:	ProgrammingSimplified.com Team
 * URL:		https://www.programmingsimplified.com/about
 */

void bubble_sort_asc_int(int list[], int n)
{
	int c, d, t;
	for (c = 0; c < n - 1; c++) {
		for (d = 0; d < n - c - 1; d++) {
			if (list[d] > list[d + 1]) {
				/* Swapping */
				t = list[d];
				list[d] = list[d + 1];
				list[d + 1] = t;
			}
		}
	}
}

void bubble_sort_asc_long(long list[], long n)
{
	long c, d, t;
	for (c = 0; c < n - 1; c++) {
		for (d = 0; d < n - c - 1; d++) {
			if (list[d] > list[d + 1]) {
				/* Swapping */
				t = list[d];
				list[d] = list[d + 1];
				list[d + 1] = t;
			}
		}
	}
}
