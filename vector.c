#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "shared.h"
#include "vector.h"

vector newVector (double x, double y, double z) {
   vector toReturn = {.x = x, .y = y, .z = z};
   return toReturn;
}

boolean equalVector (vector u, vector v) {
   boolean toReturn;
   if (closeEnough(u.x, v.x) &&
       closeEnough(u.y, v.y) &&
       closeEnough(u.z, v.z)) {

      toReturn = TRUE;
   } else {
      toReturn = FALSE;
   }
   return toReturn;
}

vector addVectors (vector u, vector v) {

   vector toReturn;
   toReturn.x = u.x+v.x;
   toReturn.y = u.y+v.y;
   toReturn.z = u.z+v.z;

   return toReturn;
}

vector subtractVectors (vector u, vector v) {
   

   vector toReturn;
   toReturn.x = u.x-v.x;
   toReturn.y = u.y-v.y;
   toReturn.z = u.z-v.z;

   return toReturn;
}

vector scaleVector (vector v, double s) {

   vector toReturn;
   toReturn.x = v.x * s;
   toReturn.y = v.y * s;
   toReturn.z = v.z * s;

   return toReturn;
}

double dotProduct (vector u, vector v) {
   return u.x*v.x + u.y*v.y + u.z*v.z;
}

vector crossProduct (vector u, vector v) {
   vector toReturn;
   toReturn.x = u.y*v.z - u.z*v.y;
   toReturn.y = u.z*v.x - u.x*v.z;
   toReturn.z = u.x*v.y - u.y*v.x;
   return toReturn;
}

double magnitude (vector v) {
   return sqrt(magnitudeSquared(v));
}

double magnitudeSquared (vector v) {
   return (v.x*v.x) + (v.y*v.y)+ (v.z*v.z);
}

double distanceSquared(vector u, vector v) {
   return magnitudeSquared(subtractVectors(u,v));
}

double scalarProjection (vector u, vector v) {
   // = u.v/|v|

   return dotProduct(u, v) / magnitude(v);
}

vector vectorProjection (vector u, vector v) {
   // this is a bit inefficient at the moment since it calculates
   // magnitude (v) twice.

   // = (u.v/|v|) * (v/|v|)

   return scaleVector (v, scalarProjection(u, v)/magnitude(v));
}

vector vectorRejection (vector u, vector v) {
   // = u - projection(u,v)

   return addVectors (u,scaleVector(vectorProjection(u,v),-1));
}

vector rotate2DVector(vector u, double theta) {
   vector toReturn;
   toReturn.x = u.x*cos(theta) - u.y*sin(theta);
   toReturn.y = u.x*sin(theta) + u.y*cos(theta);
   toReturn.z = 0;
   return toReturn;
}

intPair vectorToIntPair (vector u) {
   intPair toReturn = {.x = (int) u.x, .y = (int) u.y};
   return toReturn;
}

vector intPairToVector (intPair ip) {
   vector toReturn = {.x = ip.x, .y = ip.y, .z = 0.0};
   return toReturn;
}
