// BMPFunctions

// functions for writing image data to bmp files
// some internal code (writeHeader) by Richard Buckland

// Dependencies:
//   shared
//   Image

#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL (BYTES_PER_PIXEL*8)
#define NUMBER_PLANES 1
#define PIX_PER_METRE 2835
#define MAGIC_NUMBER 0x4d42
#define NO_COMPRESSION 0
#define OFFSET 54
#define DIB_HEADER_SIZE 40
#define NUM_COLORS 0

// writes an Image to a given BMP file
void writeBMP (Image img, char *filename);