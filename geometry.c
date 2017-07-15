#include "shared.h"
#include "vector.h"

#include "geometry.h"

edge newEdge (vector a, vector b) {
   edge toReturn = {.a = a, .b = b};
   return toReturn;
}
triangle newTriangle (vector a, vector b, vector c) {
   triangle toReturn = {.a = a, .b = b, .c = c};
   return toReturn;
}

pixelTriangle newPixelTriangle (intPair a, intPair b, intPair c) {
   pixelTriangle toReturn = {.a = a, .b = b, .c = c};
   return toReturn;
}

vector centroid (triangle tri) {
   vector toReturn;
   toReturn.x = (tri.a.x + tri.b.x + tri.c.x)/3.0;
   toReturn.y = (tri.a.y + tri.b.y + tri.c.y)/3.0;
   toReturn.z = (tri.a.z + tri.b.z + tri.c.z)/3.0;
   return toReturn;   
}

vector faceNormal (triangle tri) {
   return crossProduct(subtractVectors(tri.a, tri.b),
                       subtractVectors(tri.a, tri.c));
}

boolean isTriangleWithin(pixelTriangle tri, intPair dimensions) {
   boolean toReturn = FALSE;
   if (isPointWithin(tri.a, dimensions)
    || isPointWithin(tri.b, dimensions)
    || isPointWithin(tri.c, dimensions)) {
      toReturn = TRUE;
   }
   return toReturn;
}

boolean isPointWithin(intPair point, intPair dimensions) {
   boolean toReturn = FALSE;
   if ((0 <= point.x && point.x < dimensions.x)
    && (0 <= point.y && point.y < dimensions.y)) {
      toReturn = TRUE;
   }
   return toReturn;
}

boolean sameSideOfLine(vector p1, vector p2, edge line) {
   boolean toReturn;
   // lineDirection = line.b - line.a
   vector lineDirection = subtractVectors(line.b,line.a);

   // p1Rel = p1 - line.a
   vector p1Rel = subtractVectors(p1, line.a);
   vector p2Rel = subtractVectors(p2, line.a);

   vector cp1 = crossProduct(lineDirection, p1Rel);
   vector cp2 = crossProduct(lineDirection, p2Rel);

   if (dotProduct(cp1, cp2) > 0) {
      toReturn = TRUE;
   } else {
      toReturn = FALSE;
   }
   return toReturn;
}

boolean pointInTriangle(intPair p, pixelTriangle tri) {
   boolean toReturn;

   // convert pixel co-ordinates to 2D vectors
   // so we can use them with sameSideOfLine
   triangle dTri = {
      .a = intPairToVector(tri.a),
      .b = intPairToVector(tri.b),
      .c = intPairToVector(tri.c)
   };

   vector v = intPairToVector(p);
   if
      (sameSideOfLine(v,dTri.a, newEdge (dTri.b,dTri.c)) &&
       sameSideOfLine(v,dTri.b, newEdge (dTri.a,dTri.c)) &&
       sameSideOfLine(v,dTri.c, newEdge (dTri.a,dTri.b))) {
      toReturn = TRUE;
   } else {
      toReturn = FALSE;
   }
   return toReturn;
}