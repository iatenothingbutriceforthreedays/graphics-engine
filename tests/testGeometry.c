// testGeometry.c

// test geometry functions

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"

int main (int argc, char *argv[]) {
   printf("Testing geometry functions\n");

   printf("Testing sameSideOfLine\n");
   assert(sameSideOfLine(
      newVector(2,1,0),
      newVector(1,-3,0),
      newEdge(
         newVector(0,1,0),
         newVector(0,-1,0)
      )
   ));
   assert(!sameSideOfLine(
      newVector(-2,1,0),
      newVector(1,-3,0),
      newEdge(
         newVector(0,1,0),
         newVector(0,-1,0)
      )
   ));

   printf("Testing pointInTriangle\n");
   assert(pointInTriangle(
      newIntPair(2,2),
      newPixelTriangle(
         newIntPair(0,10),
         newIntPair(10,0),
         newIntPair(0,0)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(5,5),
      newPixelTriangle(
         newIntPair(0,10),
         newIntPair(10,0),
         newIntPair(0,0)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(0,0),
      newPixelTriangle(
         newIntPair(0,10),
         newIntPair(10,0),
         newIntPair(0,0)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(10,0),
      newPixelTriangle(
         newIntPair(0,10),
         newIntPair(10,0),
         newIntPair(0,0)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(0,10),
      newPixelTriangle(
         newIntPair(0,10),
         newIntPair(10,0),
         newIntPair(0,0)
      )
   ));

   assert(!pointInTriangle(
      newIntPair(10,10),
      newPixelTriangle(
         newIntPair(0,10),
         newIntPair(10,0),
         newIntPair(0,0)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(0,-1),
      newPixelTriangle(
         newIntPair(0,10),
         newIntPair(10,0),
         newIntPair(0,0)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(5,6),
      newPixelTriangle(
         newIntPair(0,10),
         newIntPair(10,0),
         newIntPair(0,0)
      )
   ));

   // a horizontal line triangle:
   assert(!pointInTriangle(
      newIntPair(5,0),
      newPixelTriangle(
         newIntPair(0,0),
         newIntPair(2,0),
         newIntPair(5,0)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(11,0),
      newPixelTriangle(
         newIntPair(0,0),
         newIntPair(2,0),
         newIntPair(10,0)
      )
   ));
   // a vertical line triangle
   assert(!pointInTriangle(
      newIntPair(0,5),
      newPixelTriangle(
         newIntPair(0,0),
         newIntPair(0,2),
         newIntPair(0,10)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(0,-1),
      newPixelTriangle(
         newIntPair(0,0),
         newIntPair(0,2),
         newIntPair(0,10)
      )
   ));
   // and a diagonal line
   assert(!pointInTriangle(
      newIntPair(5,5),
      newPixelTriangle(
         newIntPair(0,0),
         newIntPair(2,2),
         newIntPair(10,10)
      )
   ));
   assert(!pointInTriangle(
      newIntPair(5,6),
      newPixelTriangle(
         newIntPair(0,0),
         newIntPair(2,2),
         newIntPair(10,10)
      )
   ));

   printf("All geometry tests passed\n");
}

