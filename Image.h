// Image.h
// Image is an ADT representing a rectangular grid
// of coloured pixels

// Dependencies:
//   shared

typedef struct _image *Image;

// create a new Image, given its dimensions:
// note that when the Image is created its
// contents are uninitialised.
Image newImage (intPair dimensions);

void destroyImage (Image img);

// sets the colour of a single pixel:
void setAt(Image img, intPair point, color c);

// gets the colour of a single pixel:
color getAt(Image img, intPair point);

// gets the dimensions of the image:
intPair getDimensions(Image img);