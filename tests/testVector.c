// testVector.c
// tests for vector functions.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "shared.h"
#include "vector.h"

void testVectorFunctions();

void testAddVectors(vector a, vector b, vector expected);
void testScaleVector(vector a, double s, vector expected);
void testDotProduct(vector a, vector b, double expected);
void testCrossProduct (vector a, vector b, vector expected);
void testMagnitude(vector a, double expected);
void testMagnitudeSquared(vector a, double expected);
void testScalarProjection (vector a, vector b, double expected);
void testVectorProjection (vector a, vector b, vector expected);
void testVectorRejection (vector a, vector b, vector expected);
void testRotate2DVector (vector a, double theta, vector expected);

int main (int argc, char *argv[]) {
   testVectorFunctions();
   return EXIT_SUCCESS;
}

// vector.c tests.
void testVectorFunctions() {
   printf("Testing functions from vector.c\n");
   printf("Testing addVectors\n");
   testAddVectors(newVector(0.0, 0.0, 0.0),
                 newVector(0.0, 0.0, 0.0),
                 newVector(0.0, 0.0, 0.0));

   testAddVectors(newVector(1.0, -0.5, 320.0),
                 newVector(0.0, 0.0, 0.0),
                 newVector(1.0, -0.5, 320.0));

   testAddVectors(newVector(1.0, -0.000002, 100.0),
                 newVector(-0.1, 0.000031, 1.23),
                 newVector(0.9, 0.000029, 101.23));

   printf("Testing scaleVector\n");
   testScaleVector(newVector(1.0,0.0,0.0),
                                    10.0,
                   newVector(10.0,0.0,0.0));

   testScaleVector(newVector(1.0,3.0,-1.0),
                                     -0.5,
                   newVector(-0.5,-1.5,0.5));

   testScaleVector(newVector(1.0,4.0,-4.0),
                                      0.0,
                   newVector(0.0,0.0,0.0));

   printf("Testing dotProduct\n");
   testDotProduct(newVector(1.0,0.0,0.0),
                  newVector(0.0,1.0,-1.0),
                                     0.0);

   testDotProduct(newVector(1.0,2.0,-3.0),
                  newVector(5.0,-4.0,3.0),
                                   -12.0);

   testDotProduct(newVector(0.5,0.1,0.0),
                  newVector(0.0,2.0,-1.0),
                                     0.2);
   printf("Testing magnitude\n");
   testMagnitude(newVector(1.0,0.0,0.0),
                                   1.0);

   testMagnitude(newVector(2.0,3.0,6.0),
                                   7.0);

   testMagnitude(newVector(0.0,0.0,0.0),
                                   0.0);

   printf("Testing magnitude squared\n");
   testMagnitudeSquared(newVector(1.0,0.0,0.0),
                                   1.0);

   testMagnitudeSquared(newVector(2.0,3.0,6.0),
                                   49.0);

   testMagnitudeSquared(newVector(0.0,0.0,0.0),
                                   0.0);

   printf("Testing scalarProjection\n");
   testScalarProjection(newVector(0.5,0.0,0.0),
                        newVector(-3.0,0.0,0.0),
                                          -0.5);

   testScalarProjection(newVector(10.0,0.0,0.0),
                        newVector(0.0,1.0,1.0),
                                          0.0);

   testScalarProjection(newVector(1.0,1.0,0.0),
                        newVector(1.0,0.0,0.0),
                                          1.0);

   printf("Testing crossProduct\n");
   testCrossProduct(newVector(1.0,2.0,0.0),
                    newVector(2.0,4.0,0.0),
                    newVector(0.0,0.0,0.0));

   testCrossProduct(newVector(0.2, 0.0, 0.0),
                    newVector(0.0,-2.0, 0.0),
                    newVector(0.0, 0.0,-0.4));

   testCrossProduct(newVector(1.0,-2.0, 3.0),
                    newVector(4.0, 5.0,  6.0),
                    newVector(-27.0, 6.0, 13.0));

   printf("Testing vectorProjection\n");

   testVectorProjection(newVector(1.0, 1.0, 0.0),
                        newVector(0.0, 0.2, 0.0),
                        newVector(0.0, 1.0, 0.0));

   testVectorProjection(newVector(1.0, 0.0, -2.0),
                        newVector(2.0, 0.0, -4.0),
                        newVector(1.0, 0.0, -2.0));

   testVectorProjection(newVector(-3.0, 1.0, 5.0),
                        newVector( 2.5, -1.0, 0.3),
                        newVector(-875/367.0, 350/367.0, -105/367.0));

   printf("Testing vectorRejection\n");

   testVectorRejection(newVector(1.0, 1.0, 0.0),
                       newVector(0.0, 0.2, 0.0),
                       newVector(1.0, 0.0, 0.0));

   testVectorRejection(newVector(1.0, 0.0, -2.0),
                       newVector(2.0, 0.0, -4.0),
                       newVector(0.0, 0.0, 0.0));

   printf("Testing rotate2DVector\n");

   testRotate2DVector(newVector(1.0, 0.0, 0.0),
                      M_PI/2,
                      newVector(0.0, 1.0, 0.0));

   testRotate2DVector(newVector(-2.0, -1.0, 0.0),
                      -M_PI/2,
                      newVector(-1.0, 2.0, 0.0));

   testRotate2DVector(newVector(3.0, 2.0, 0.0),
                      -M_PI,
                      newVector(-3.0, -2.0, 0.0));

   printf("vector.c tests passed.\n");
}

void testAddVectors(vector a, vector b, vector expected) {
   printf("Testing (%.3f, %.3f, %.3f) + (%.3f, %.3f, %.3f) == (%.3f, %.3f, %.3f)\n",
   a.x,a.y,a.z, b.x,b.y,b.z, expected.x,expected.y,expected.z);
   assert (equalVector(addVectors(a,b), expected));
}

void testScaleVector(vector a, double s, vector expected) {
   printf("Testing (%.3f, %.3f, %.3f) * %.3f == (%.3f, %.3f, %.3f)\n",
   a.x,a.y,a.z, s, expected.x,expected.y,expected.z);
   assert (equalVector(scaleVector(a,s), expected));
}

void testDotProduct(vector a, vector b, double expected) {
   printf("Testing (%.3f, %.3f, %.3f) + (%.3f, %.3f, %.3f) == %.3f\n",
   a.x,a.y,a.z, b.x,b.y,b.z, expected);
   assert (closeEnough(dotProduct(a,b), expected));
}

void testCrossProduct(vector a, vector b, vector expected) {
   printf("Testing (%.3f, %.3f, %.3f) x (%.3f, %.3f, %.3f) == (%.3f, %.3f, %.3f)\n",
   a.x,a.y,a.z, b.x,b.y,b.z, expected.x,expected.y,expected.z);
   assert (equalVector(crossProduct(a,b), expected));
}

void testMagnitude(vector a, double expected) {
   printf("Testing |(%.3f, %.3f, %.3f)| == %.3f\n",
   a.x,a.y,a.z, expected);
   assert (closeEnough(magnitude(a), expected));
}
void testMagnitudeSquared(vector a, double expected) {
   printf("Testing |(%.3f, %.3f, %.3f)|^2 == %.3f\n",
   a.x,a.y,a.z, expected);
   assert (closeEnough(magnitudeSquared(a), expected));
}

void testScalarProjection (vector a, vector b, double expected) {
   printf("Testing |projection of (%.3f, %.3f, %.3f) onto (%.3f, %.3f, %.3f)| == %.3f\n",
   a.x,a.y,a.z, b.x,b.y,b.z, expected);
   assert (closeEnough(scalarProjection (a, b), expected));
}

void testVectorProjection (vector a, vector b, vector expected) {
   printf("Testing projection of (%.3f, %.3f, %.3f) onto (%.3f, %.3f, %.3f)"
          " == (%.3f, %.3f, %.3f)\n",
   a.x,a.y,a.z, b.x,b.y,b.z, expected.x,expected.y,expected.z);

   assert (equalVector(vectorProjection (a, b), expected));
}

void testVectorRejection (vector a, vector b, vector expected) {
   printf("Testing rejection of (%.3f, %.3f, %.3f) from (%.3f, %.3f, %.3f)"
          " == (%.3f, %.3f, %.3f)\n",
   a.x,a.y,a.z, b.x,b.y,b.z, expected.x,expected.y,expected.z);

   assert (equalVector(vectorRejection (a, b), expected));
}

void testRotate2DVector (vector a, double theta, vector expected) {
   printf("Testing rotation of (%.3f, %.3f, %.3f) by angle %.3f around z-axis"
          " == (%.3f, %.3f, %.3f)\n",
   a.x,a.y,a.z, theta, expected.x,expected.y,expected.z);

   assert (equalVector(rotate2DVector (a, theta), expected));   
}