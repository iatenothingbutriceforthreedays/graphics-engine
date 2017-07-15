// testShared.c

// test shared functions

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "shared.h"

int main (int argc, char *argv[]) {
   printf("Testing functions from shared.c\n");
   printf("Testing closeEnough\n");
   assert(closeEnough(1.0,1.0));
   assert(closeEnough(4.0/3.0, 2*2*2*2/12.0));
   assert(closeEnough(-10.0, -10.0+THRESHOLD/2));
   assert(!closeEnough(4.0,5.0));
   assert(!closeEnough(-5.0,5.0));
   assert(!closeEnough(3.0/4.0,1.0));
   assert(!closeEnough(-10.0,-10.0 + 2*THRESHOLD));

   printf("Testing equalIntPair\n");
   assert(equalIntPair(
             newIntPair(3,3),
             newIntPair(3,3)));
   assert(equalIntPair(
             newIntPair(-4,2),
             newIntPair(-4,2)));
   assert(equalIntPair(
             newIntPair(0,1),
             newIntPair(0,1)));
   assert(!equalIntPair(
             newIntPair(1,0),
             newIntPair(0,1)));
   assert(!equalIntPair(
             newIntPair(10,11),
             newIntPair(10,9)));

   printf("Testing maxInt\n");
   assert(maxInt(3,-4) == 3);
   assert(maxInt(-4,3) == 3);
   assert(maxInt(4,3) == 4);
   assert(maxInt(-4,-3) == -3);

   printf("Testing minInt\n");
   assert(minInt(3,-4) == -4);
   assert(minInt(-4,3) == -4);
   assert(minInt(4,3) == 3);
   assert(minInt(-4,-3) == -4);

   printf("Testing swapInt\n");
   int a = 5;
   int b = 10;
   swapInt (&a, &b);
   assert(a == 10);
   assert(b == 5);

   printf("Testing swapDouble\n");
   double c = 0.2;
   double d = 2.0;
   swapDouble (&c, &d);
   assert(closeEnough(c, 2.0));
   assert(closeEnough(d, 0.2));
   
   printf("All shared tests passed\n");
}