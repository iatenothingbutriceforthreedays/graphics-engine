// testCamera.c

// tests for the camera library.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <math.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"
#include "Image.h"
#include "camera.h"

void testCameraFunctions();

void testOrthoProjection(camera cam, vector u, vector expected);

int main (int argc, char *argv[]) {
   testCameraFunctions();
   return EXIT_SUCCESS;
}

// camera.c tests
void testCameraFunctions() {
   printf("Testing functions from camera.c\n");
   printf("Testing orthoProjection\n");

   // these are pretty trivial cases,
   // because it's just too hard to figure it out
   // for harder ones. but better than nothing.
   
   testOrthoProjection(newCamera(
                          newVector(0.0,0.0,0.0),
                          newVector(0.0,0.0,-1.0),
                          0.0, 1.0),
                       newVector(3.0,-0.5,0.2),
                       newVector(3.0,-0.5,0.0));

   testOrthoProjection(newCamera(
                          newVector(0.0,0.0,0.0),
                          newVector(0.0,0.0,1.0),
                          0.0, 1.0),
                       newVector(3.0,-0.5,0.2),
                       newVector(-3.0,-0.5,0.0));

   testOrthoProjection(newCamera(
                          newVector(1.0,-1.0,-21.242),
                          newVector(0.0,0.0,-1.0),
                          0.0, 1.0),
                       newVector(3.0,-0.5,0.2),
                       newVector(2.0, 0.5,0.0));

   testOrthoProjection(newCamera(
                          newVector(0.0,0.0,0.0),
                          newVector(0.0,0.0,-1.0),
                          M_PI/2, 1.0),
                       newVector(3.0,-0.5,0.2),
                       newVector(0.5, 3.0,0.0));

   printf("camera.c tests passed.\n");
}

void testOrthoProjection(camera cam, vector u, vector expected) {
   printf("Testing that ortho projection of point (%.3f, %.3f, %.3f)\n"
          "onto camera at point (%.3f, %.3f, %.3f)\n"
          "facing in direction (%.3f, %.3f, %.3f)\n"
          "and rotated by angle %.3f\n"
          "is equal to (%.3f, %.3f, %.3f)\n",
          u.x,u.y,u.z, cam.pos.x,cam.pos.y,cam.pos.z,
          cam.normal.x,cam.normal.y,cam.normal.z,
          cam.angle, expected.x,expected.y,expected.z);

   assert(equalVector(orthoProjection(u,cam),expected));
}