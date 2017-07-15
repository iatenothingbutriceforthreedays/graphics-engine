// graphics2D

// basic 2D drawing operations

// Dependencies:
//    shared
//    Image
//    BMPFunctions

// fill an Image with a solid colour
void fillImage (Image img, color c);

// draws a line segment to an Image.
void drawLine(Image img, pixelLine line, color c);

// draw a triangle to an Image.
void drawTri(Image img, pixelTriangle tri, color c);

// filled triangle
void drawFilledTri(Image img, pixelTriangle tri, color c);