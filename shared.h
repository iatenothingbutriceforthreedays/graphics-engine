#define TRUE 1
#define FALSE 0

#define NEWLINE_CHAR '\n'

#define THRESHOLD 0.00000001 // for closeEnough

typedef unsigned char  bits8;
typedef unsigned short bits16;
typedef unsigned int   bits32;

typedef unsigned char boolean;

typedef struct _color {
   // RGB, 256 bits each
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} color;

typedef struct _intPair {
   // pretty much a 2D vector, but this is for
   // pixel rather than spatial coordinates
   int x;
   int y;
} intPair;

typedef struct _intTriple {
   // used for representing a triangle
   // by indices (see Mesh.h for explanation).
   int a;
   int b;
   int c;
} intTriple;

// constructors:
intTriple newIntTriple(int a, int b, int c);
intPair newIntPair (int x, int y);

void swapInt(int *first, int *second);
void swapDouble(double *first, double *second);

// compares two doubles to see if they are
// within THRESHOLD of each other (see #define)
boolean closeEnough (double a, double b);

// test equality of two intPairs
boolean equalIntPair (intPair a, intPair b);

// max and min functions
int maxInt (int a, int b);
int minInt (int a, int b);