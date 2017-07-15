#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"

#include "camera.h"

camera newCamera (vector pos, vector normal, double angle, double scale) {
   camera toReturn = {.pos = pos, .normal = normal, .angle = angle, .scale = scale};
   return toReturn;
}

vector orthoProjection (vector v, camera cam) {
   // returns a 2D vector (i.e. z == 0) obtained by taking
   // a point v, and projecting it onto
   // the camera's up and right vectors.
   // (google orthographic projection for detailed explanation)

   // global 'up' is (0,1,0).
   // if the camera is pointing 'up'
   // it's local 'up' will be (0,0,1)

   vector toReturn;   

   vector vRel = addVectors(v, scaleVector(cam.pos, -1)); // v relative to camera

   // set the up and right vectors of the camera
   // if we pretend it is not rotated around its axis

   vector up;
   if (equalVector(crossProduct(newVector(0,1,0), cam.normal), newVector(0.0,0.0,0.0))) {
      // perpendicular
      // this means rejection is null.
      // so we just set 'up' to z-basis
      // this is a bit hacky but I don't know what else to do
      up = newVector(0,0,1);
   } else {
      up = vectorRejection(newVector(0,1,0), cam.normal);
   } 
   vector right = crossProduct(cam.normal,up);

   toReturn.x = scalarProjection(vRel,right);
   toReturn.y = scalarProjection(vRel,up);
   toReturn.z = 0;


   // now transform points according to
   // camera's rotation about axis
   // note: this might not be an efficient way of doing it
   // but at least the maths is possible

   toReturn = rotate2DVector (toReturn, cam.angle);

   return toReturn;
}

intPair projectPointToGrid
(vector point, camera cam, intPair dimensions) {

   point = orthoProjection (point, cam);

   // scale point to max of dimensions.x and dimensions.y
   point = scaleVector (point,
                        maxInt(dimensions.x,dimensions.y)/cam.scale);

   // shift to centre of camera:
   point =
      addVectors(point, newVector(dimensions.x/2, dimensions.y/2, 0));
   
   return vectorToIntPair(point);
}

pixelTriangle projectTriangleToGrid
(triangle tri, camera cam, intPair dimensions) {

   pixelTriangle toReturn = {
      .a = projectPointToGrid (tri.a, cam, dimensions),
      .b = projectPointToGrid (tri.b, cam, dimensions),
      .c = projectPointToGrid (tri.c, cam, dimensions)
   };
   return toReturn;
}