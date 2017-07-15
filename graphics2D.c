#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"
#include "Image.h"

#include "graphics2D.h"

void fillImage (Image img, color c) {
   // set every pixel in img
   // to color c.

   intPair dimensions = getDimensions(img);

   // the point to write to:
   intPair pen;
   pen.x = 0;

   while (pen.x < dimensions.x) {
      pen.y = 0;
      while (pen.y < dimensions.y) {
         setAt(img, pen, c);
         pen.y++;
      }
      pen.x++;
   }
}

void drawLine(Image img, pixelLine line, color c) {
   // using Bresenham's algorithm. very inefficient atm
   // adapted from
   // http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Optimization

   // currently deals with lines which extend outside
   // the screen, but not in an efficient way.

   boolean steep;
   // is the line steeper than gradient = 1?
   if (abs(line.b.y - line.a.y) > abs(line.b.x - line.a.x)) {
      steep = TRUE;
   } else {
      steep = FALSE;
   }

   // do some swaps so that we can pretend we're dealing with the
   // 1st octant (ENE), where gradient is between 0 and 1, and
   // x is increasing

   if (steep) {
      swapInt(&line.a.x,&line.a.y);
      swapInt(&line.b.x,&line.b.y); 
   }
   if (line.a.x > line.b.x) {
      swapInt(&line.a.x, &line.b.x);
      swapInt(&line.a.y, &line.b.y);
   }

   int deltaX = line.b.x - line.a.x;
   int deltaY = abs(line.b.y - line.a.y);

   int error = deltaX/2;

   int yStep;

   intPair pen = line.a; // position to draw to

   if (line.a.y < line.b.y) {
      yStep = 1;
   } else {
      yStep = -1;
   }

   intPair dimensions = getDimensions(img);

   while (pen.x <= (int) line.b.x) {
      if (steep) {
         swapInt(&pen.x,&pen.y);
      }
      if ((0 <= pen.x && pen.x < dimensions.x) &&
          (0 <= pen.y && pen.y < dimensions.y))
      {
         // ^ only draw if line is within boundaries
         // a more efficient way to to this would be to test the endpoints
         // of the line to begin with and adjust
         // the line accordingly.

         setAt(img, pen, c);
      }
      if (steep) {
         swapInt(&pen.x, &pen.y); //swap back
      }

      error -= deltaY;
      if (error < 0) { // if it's time to shift up
         pen.y += yStep;
         error += deltaX;
      }
      pen.x++;
   }
}

void drawTri(Image img, pixelTriangle tri, color c) {
   pixelLine lineAB = {.a = tri.a, .b=tri.b};
   pixelLine lineBC = {.a = tri.b, .b=tri.c};
   pixelLine lineAC = {.a = tri.a, .b=tri.c};
   
   drawLine(img, lineAB, c);
   drawLine(img, lineBC, c);
   drawLine(img, lineAC, c);
}

void drawFilledTri(Image img, pixelTriangle tri, color c) {

   // draws a filled triangle to pixel buffer pixels.
   // tests every pixel in the bounding box
   // this is not efficient but is very simple to implement.
   // if speed becomes an issue this can be changed.



   
   intPair dimensions = getDimensions(img);
   if (isTriangleWithin(tri, dimensions)) {

      // generate a bounding box
      intPair bottomLeft;
      bottomLeft.x = minInt(minInt(tri.a.x,tri.b.x),tri.c.x);
      bottomLeft.y = minInt(minInt(tri.a.y,tri.b.y),tri.c.y);

      intPair topRight;
      topRight.x = maxInt(maxInt(tri.a.x,tri.b.x),tri.c.x);
      topRight.y = maxInt(maxInt(tri.a.y,tri.b.y),tri.c.y);

      intPair pen;
      pen.x = bottomLeft.x;

      while (pen.x <= topRight.x) {
         pen.y = bottomLeft.y;
         while (pen.y <= topRight.y) {
            if (pointInTriangle (pen, tri)) {
              if ((0 <= pen.x && pen.x < dimensions.x) &&
                  (0 <= pen.y && pen.y < dimensions.y)){
                 // this is not the best way to do it

                 setAt(img, pen,c);
              }
            }
            pen.y++;
         }
         pen.x++;
      }
      drawTri(img, tri, c);
   }

}

