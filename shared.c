// some shared convenience functions and definitions.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shared.h"

intTriple newIntTriple(int a, int b, int c) {
   intTriple toReturn = {.a = a, .b = b, .c = c};
   return toReturn;
}

intPair newIntPair (int x, int y) {
   intPair toReturn = {.x = x, .y = y};
   return toReturn;
}


void swapInt(int *first, int *second) {
   // for use in Bresenham's alg

   int swap;
   swap = *first; // put the value of first into swap
   *first = *second; // put the value of second into first
   *second = swap; // put swap into second
}

void swapDouble(double *first, double *second) {
   // for use in Bresenham's

   double swap;
   swap = *first; // put the value of first into swap
   *first = *second; // put the value of second into first
   *second = swap; // put swap into second
}

int maxInt (int a, int b) {
   int toReturn;
   if (a < b) {
      toReturn = b;
   } else {
      toReturn = a;
   }
   return toReturn;
}

int minInt (int a, int b) {
   int toReturn;
   if (a < b) {
      toReturn = a;
   } else {
      toReturn = b;
   }
   return toReturn;
}

boolean equalIntPair(intPair a, intPair b) {
   boolean toReturn;
   if (a.x == b.x
    && a.y == b.y) {
      toReturn = TRUE;
   } else {
      toReturn = FALSE;
   }
   return toReturn;
}

boolean closeEnough (double a, double b) {
   // tests if two doubles are very close together,
   // for unit testing.
   // this is necessary since doubles aren't stored to
   // an arbitary degree of precision.
   boolean toReturn;

   if (fabs(a - b) < THRESHOLD) {
      toReturn = TRUE;
   } else {
      toReturn = FALSE;
   }
   return toReturn;
}

