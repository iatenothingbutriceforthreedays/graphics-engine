// geometry

// geometric types
// in pixel (2D grid) space and 3D 'real' space
// as well as some geometric functions

// Dependencies:
//   shared
//   vector

typedef struct _edge {
   // edge from a to b
   // in 'real' space
   vector a;
   vector b;
} edge;

typedef struct _triangle {
   // 3D triangle
   // i.e. three points
   // in 'real' space
   
   vector a;
   vector b;
   vector c;
} triangle;

typedef struct _pixelLine {
   // for 2D lines in screen space
   // from a to b.
   intPair a;
   intPair b;
} pixelLine;

typedef struct _pixelTriangle {
   // integer triangle
   // i.e. three points in screen space
   
   intPair a;
   intPair b;
   intPair c;
} pixelTriangle;

// constructors
edge newEdge (vector a, vector b);
triangle newTriangle (vector a, vector b, vector c);
pixelTriangle newPixelTriangle (intPair a, intPair b, intPair c);

// centroid of triangle:
vector centroid (triangle tri);

// normal of triangle
// (not unit!!!)
vector faceNormal (triangle tri);

// check if point lies within dimensions
boolean isPointWithin(intPair point, intPair dimensions);

// check if any point on triangle lies within dimensions.
boolean isTriangleWithin(pixelTriangle tri, intPair dimensions);


// triangle functions:
// determine whether or not point p is in triangle tri
// edge points should count as OUT.
boolean pointInTriangle(intPair p, pixelTriangle tri);

// determine whether p1 and p2 lie on the same side of line
// USE 2D vectors (i.e. .z = 0).
boolean sameSideOfLine(vector p1, vector p2, edge line);