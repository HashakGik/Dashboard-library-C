#include "utils.h"

double cos(double x)
{
    /* Simply call sin(x + pi / 2). */
    return sin(x + 3.14159265358979323846 / 2);
}

double sin(double x)
{

    double s;

    /* Bring x in [-pi; +pi] for a better approximation. */
    while (x > 3.14159265358979323846)
	x -= 2 * 3.14159265358979323846;
    while (x < -3.14159265358979323846)
	x += 2 * 3.14159265358979323846;

    /* Fast sine approximation taken from:
       https://stackoverflow.com/questions/23837916/
       a-faster-but-less-accurate-fsin-for-intel-asm */
    s = x + (x * x * x) * (-0.16612511580269618f +
			   x * x * (8.0394356072977748e-3f +
				    x * x * -1.49414020045938777495e-4f));

    return s;
}

void sort(int a[], int n)
{
    /* For now it's a simple bubblesort. For the dashboard use-case,
       stdlib's quicksort doesn't seem to be much faster... */

    int j, tmp;
    j = 0;
    while (j < n - 1) {
	if (a[j] > a[j + 1]) {
	    tmp = a[j];
	    a[j] = a[j + 1];
	    a[j + 1] = tmp;
	    if (j > 0)
		j--;
	} else
	    j++;
    }
}
