#include <stdio.h>
#include <assert.h>

#include "shared.h"

#include "Image.h"

#include "BMPFunctions.h"

static void writeHeader (FILE *file, intPair dimensions);
static void writeBGRTriplet (color bgr, FILE *outputFile);

void writeBMP (Image img, char *filename) {
   // check that the types have the size i'm relying on here
   assert (sizeof(bits8)  == 1);
   assert (sizeof(bits16) == 2);
   assert (sizeof(bits32) == 4);

   intPair dimensions = getDimensions(img);

   int numPixels = (dimensions.x * dimensions.y);
   assert (numPixels%4 == 0);
   // currently can't deal with area not divisible by four.
   
   FILE *outputFile;

   outputFile = fopen(filename, "wb");
   assert ((outputFile!=NULL) && "Cannot open file");
   
   writeHeader(outputFile, dimensions);

   intPair pen;
   pen.y = 0;
   // this refers to the
   // position of the pixel currently being written

   color toWrite;

   while (pen.y < dimensions.y) {
      // writes in the order given by the BMP spec
      pen.x = 0;
      while (pen.x < dimensions.x) {
         toWrite = getAt(img, pen);
         writeBGRTriplet (toWrite, outputFile);
         pen.x++;
      }
      pen.y++;
   }
   fclose(outputFile);
}

static void writeHeader (FILE *file, intPair dimensions) {
   assert(sizeof (bits8) == 1);
   assert(sizeof (bits16) == 2);
   assert(sizeof (bits32) == 4);
 
   bits16 magicNumber = MAGIC_NUMBER;
   fwrite (&magicNumber, sizeof magicNumber, 1, file);
 
   bits32 fileSize =
   OFFSET + (dimensions.x * dimensions.y * BYTES_PER_PIXEL);

   fwrite (&fileSize, sizeof fileSize, 1, file);
 
   bits32 reserved = 0;
   fwrite (&reserved, sizeof reserved, 1, file);
 
   bits32 offset = OFFSET;
   fwrite (&offset, sizeof offset, 1, file);
 
   bits32 dibHeaderSize = DIB_HEADER_SIZE;
   fwrite (&dibHeaderSize, sizeof dibHeaderSize, 1, file);
 
   bits32 width = dimensions.x;
   fwrite (&width, sizeof width, 1, file);
 
   bits32 height = dimensions.y;
   fwrite (&height, sizeof height, 1, file);
 
   bits16 planes = NUMBER_PLANES;
   fwrite (&planes, sizeof planes, 1, file);
 
   bits16 bitsPerPixel = BITS_PER_PIXEL;
   fwrite (&bitsPerPixel, sizeof bitsPerPixel, 1, file);
 
   bits32 compression = NO_COMPRESSION;
   fwrite (&compression, sizeof compression, 1, file);
 
   bits32 imageSize = (height * width * BYTES_PER_PIXEL);
   fwrite (&imageSize, sizeof imageSize, 1, file);
 
   bits32 hResolution = PIX_PER_METRE;
   fwrite (&hResolution, sizeof hResolution, 1, file);
 
   bits32 vResolution = PIX_PER_METRE;
   fwrite (&vResolution, sizeof vResolution, 1, file);
 
   bits32 numColors = NUM_COLORS;
   fwrite (&numColors, sizeof numColors, 1, file);
 
   bits32 importantColors = NUM_COLORS;
   fwrite (&importantColors, sizeof importantColors, 1, file);
}

static void writeBGRTriplet (color bgr, FILE *outputFile) {
   // writes a BGR triplet (of unsigned chars)
   // to BMP outputFile.

   fwrite (&bgr.blue, sizeof bgr.blue, 1, outputFile);
   fwrite (&bgr.green, sizeof bgr.green, 1, outputFile);
   fwrite (&bgr.red, sizeof bgr.red, 1, outputFile);
}