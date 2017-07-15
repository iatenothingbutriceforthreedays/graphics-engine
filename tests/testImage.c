// test Image ADT
// compile along with Image.c

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "shared.h"

#include "Image.h"

int main (int argc, char *argv[]) {
   printf("Testing Image ADT\n");

   intPair dimensions = {.x = 5, .y = 10};
   Image testImage = newImage(dimensions);
   assert(getDimensions(testImage).x == 5);

   intPair point = {.x = 2, .y = 4};
   color c = {.red = 100, .blue = 4, .green = 10};
   setAt(testImage, point, c);
   color result =  getAt(testImage,point);
   assert(result.red = c.red);
   assert(result.blue = c.blue);
   assert(result.green = c.green);

   destroyImage(testImage);

   printf("Image ADT tests passed\n");
   return EXIT_SUCCESS;
}