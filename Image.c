// implementation of Image ADT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "shared.h"

#include "Image.h"

static int pointToIndex(Image img, intPair point);

typedef struct _image {
   intPair dimensions;
   color *pixels;
} image;

Image newImage (intPair dimensions) {
   // I think this works...

   Image toReturn = malloc (sizeof(image));

   int numPixels = dimensions.x * dimensions.y;

   // allocate enough memory for the pixel array:
   toReturn->pixels = malloc (numPixels * sizeof(color));
   assert (toReturn->pixels != NULL);

   // allocate enough memory for the image
   // this memory accounts for dimensions,
   // and a pointer to pixels,
   // but not the actual data in the pixel array.
   // I think that's ok, because we already
   // allocated memory for that.

   toReturn->dimensions = dimensions;

   return toReturn;
}

void destroyImage (Image img) {
   free (img->pixels);
   free (img);
}

void setAt(Image img, intPair point, color c) {
   // set pixel at point to color c.
   int pixelIndex = pointToIndex(img, point);

   img->pixels[pixelIndex] = c;
}

color getAt(Image img, intPair point) {

   int pixelIndex = pointToIndex(img, point);

   return img->pixels[pixelIndex];
}

intPair getDimensions(Image img) {
   return img->dimensions;
}

static int pointToIndex (Image img, intPair point) {
   // convert (x,y) to index of that pixel
   assert (0 <= point.x && point.x < img->dimensions.x);
   assert (0 <= point.y && point.y < img->dimensions.y);

   return img->dimensions.x*point.y + point.x;
}