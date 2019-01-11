#ifndef UTILS_H
#define UTILS_H

/* Utility functions. They might be optimized for the architecture/use-case
   better than standard functions. */

/**
   Cosine function.

   @param x angle in radians.
   @returns cosine of x.
 */
double cos(double x);

/**
   Sine function.

   @param x angle in radians.
   @returns sine of x.
 */
double sin(double x);

/**
   Array in-place sort function.

   @param a Array to be sorted (the elements will be swapped in place).
   @param n Elements of the array.
 */
void sort(int a[], int n);

#endif
