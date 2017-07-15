// testGraphics2D.c
// by Darwin Vickers
// compile along with:
// testGraphics2D.c BMPFunctions.c graphics2D.c Image.c shared.c vector.c

// for testing graphics2D.c
// as well as BMPFunctions.c
// and Image.c.
// expected output should be two sets of images:
// 1. sixteen images, each 16x16, on a white background
// for each of the 16 compass points. those pointing north or horizontal should
// be red, while others are blue
// those pointing east or vertical have black background, others
// have white background
// note coordinates follow 1st quadrant Cartesian convention, with (0,0) in the
// bottom left corner.
// 2. nine images featuring different triangles,
// all on a white background, outlined black and filled red
// one triangle pointing in each direction (u, d ...),
// one right angle triangle in each quadrant (q1, q2...)
// and one that's a bit wonky (wonky.bmp).

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"

#include "Image.h"
#include "BMPFunctions.h"
#include "graphics2D.h"

#define SIZE 16
#define OUTPUT_FOLDER "./output/testOutput/"
 
int main (int argc, char *argv[]) {

   color red;
   red.red = 255;
   red.green = 0;
   red.blue = 0;

   color blue;
   blue.red = 0;
   blue.green = 0;
   blue.blue = 255;

   color black = {.red = 0, .blue = 0, .green = 0};
   color white = {.red = 255, .blue = 255, .green = 255};

   intPair c =   {.x =  7, .y =  7};
   intPair n =   {.x =  7, .y = 13};
   intPair nne = {.x =  9, .y = 12};
   intPair ne =  {.x = 11, .y = 11};
   intPair ene = {.x = 12, .y =  9};
   intPair e =   {.x = 13, .y =  7};
   intPair ese = {.x = 12, .y =  5};
   intPair se =  {.x = 11, .y =  3};
   intPair sse = {.x =  9, .y =  2};
   intPair s =   {.x =  7, .y =  1};
   intPair ssw = {.x =  5, .y =  2};
   intPair sw =  {.x =  3, .y =  3};
   intPair wsw = {.x =  2, .y =  5};
   intPair w =   {.x =  1, .y =  7};
   intPair wnw = {.x =  2, .y =  9};
   intPair nw =  {.x =  3, .y = 11};
   intPair nnw = {.x =  5, .y = 12};

   // test cases:
   int numToTest = 16;
   intPair vectors[numToTest];
   char *names[numToTest];
   color colors[numToTest];
   color bgColors[numToTest];

   vectors[ 0] = n;   names[ 0] = "n.bmp";   colors[ 0] = red;  bgColors[ 0] = black; 
   vectors[ 1] = nne; names[ 1] = "nne.bmp"; colors[ 1] = red;  bgColors[ 1] = black;
   vectors[ 2] = ne;  names[ 2] = "ne.bmp";  colors[ 2] = red;  bgColors[ 2] = black;
   vectors[ 3] = ene; names[ 3] = "ene.bmp"; colors[ 3] = red;  bgColors[ 3] = black;
   vectors[ 4] = e;   names[ 4] = "e.bmp";   colors[ 4] = red;  bgColors[ 4] = black;
   vectors[ 5] = ese; names[ 5] = "ese.bmp"; colors[ 5] = blue; bgColors[ 5] = black;
   vectors[ 6] = se;  names[ 6] = "se.bmp";  colors[ 6] = blue; bgColors[ 6] = black;
   vectors[ 7] = sse; names[ 7] = "sse.bmp"; colors[ 7] = blue; bgColors[ 7] = black;
   vectors[ 8] = s;   names[ 8] = "s.bmp";   colors[ 8] = blue; bgColors[ 8] = black;
   vectors[ 9] = ssw; names[ 9] = "ssw.bmp"; colors[ 9] = blue; bgColors[ 9] = white;
   vectors[10] = sw;  names[10] = "sw.bmp";  colors[10] = blue; bgColors[10] = white;
   vectors[11] = wsw; names[11] = "wsw.bmp"; colors[11] = blue; bgColors[11] = white;
   vectors[12] = w;   names[12] = "w.bmp";   colors[12] = red;  bgColors[12] = white;
   vectors[13] = wnw; names[13] = "wnw.bmp"; colors[13] = red;  bgColors[13] = white;
   vectors[14] = nw;  names[14] = "nw.bmp";  colors[14] = red;  bgColors[14] = white;
   vectors[15] = nnw; names[15] = "nnw.bmp"; colors[15] = red;  bgColors[15] = white;

   intPair dimensions;
   dimensions.x = SIZE;
   dimensions.y = SIZE;

   Image output = newImage(dimensions);
   char filename[50];

   pixelLine line;

   color col;
   color bgColor;
   
   int i = 0;
   while (i < numToTest) {
      line.a = c;
      line.b = vectors[i];
      col = colors[i];
      bgColor = bgColors[i];
      
      fillImage (output, bgColor);

      drawLine(output, line, col);
      strcpy(filename,OUTPUT_FOLDER);
      strcat(filename, names[i]);
      writeBMP (output, filename);
      i++;
   }

   // drawTriangle:
   pixelTriangle u = {.a = n, .b = e, .c = w};
   pixelTriangle d = {.a = s, .b = e, .c = w};
   pixelTriangle r = {.a = e, .b = n, .c = s};
   pixelTriangle l = {.a = w, .b = n, .c = s};

   pixelTriangle q1 = {.a = c, .b = n, .c = e};
   pixelTriangle q2 = {.a = c, .b = n, .c = w};
   pixelTriangle q3 = {.a = w, .b = c, .c = s};
   pixelTriangle q4 = {.a = s, .b = e, .c = c};

   pixelTriangle wonky = {.a = sw, .b = nnw, .c = e};
   
   
   // test cases:
   numToTest = 9;
   pixelTriangle tris[9] =
   {u,d,r,l,q1,q2,q3,q4,wonky};
   char *triNames[9] =
   {"u.bmp","d.bmp","r.bmp","l.bmp",
    "q1.bmp","q2.bmp","q3.bmp","q4.bmp",
    "wonky.bmp"};

   i = 0;
   while (i < numToTest) {
      fillImage (output, white);

      drawFilledTri(output, tris[i], red);
     // drawTri(output, tris[i], black);

      
      strcpy(filename,OUTPUT_FOLDER);
      strcat(filename, triNames[i]);
      writeBMP (output, filename);
      i++;
   }

   return EXIT_SUCCESS;
}