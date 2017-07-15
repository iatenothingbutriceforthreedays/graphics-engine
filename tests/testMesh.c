// testMesh.c
// tests the Mesh ADT
// compile along with
// Mesh.c
// shared.c
// vector.c

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"

#include "Mesh.h"

int main (int argc, char *argv[]) {

   printf("Testing Mesh ADT\n");

   vector vertices[] = {newVector(1.0,0.0,0.0)};
   intTriple faceIndices[] = {};
   Mesh testMesh = newMesh(vertices, 1, faceIndices, 0);
   assert(getNumVertices(testMesh) == 1);
   assert(getNumFaces(testMesh) == 0);

   assert(equalVector(getVertex(testMesh,0), newVector(1.0,0.0,0.0)));

   destroyMesh (testMesh);

   vector vertices2[] = {newVector(1.0,0.0,0.0),newVector(0.0,1.0,0.0),
                         newVector(0.0,0.0,1.0),newVector(2.0,0.0,0.0),
                         newVector(0.0,2.0,0.0),newVector(0.0,0.0,2.0)};

   intTriple faceIndices2[] = {newIntTriple(0,1,2), newIntTriple(3,4,5)};   
   Mesh testMesh2 = newMesh(vertices2, 6, faceIndices2, 2);
   
   assert(getNumVertices(testMesh2) == 6);
   assert(getNumFaces(testMesh2) == 2);

   assert(equalVector(getVertex(testMesh2,3), newVector(2.0,0.0,0.0)));

   triangle face = getFace(testMesh2,0);
   assert(equalVector(face.a, newVector(1.0,0.0,0.0)));
   assert(equalVector(face.b, newVector(0.0,1.0,0.0)));
   assert(equalVector(face.c, newVector(0.0,0.0,1.0)));

   // test sortByDistanceFrom
   sortByDistanceFrom(testMesh2, newVector(0.0,0.0,0.0));

   // faces should have swapped around.
   face = getFace(testMesh2,0); // should be furthest face
   assert(equalVector(face.a, newVector(2.0,0.0,0.0)));
   assert(equalVector(face.b, newVector(0.0,2.0,0.0)));
   assert(equalVector(face.c, newVector(0.0,0.0,2.0)));

   destroyMesh(testMesh2);

   printf("Mesh ADT tests passed\n");

   return EXIT_SUCCESS;
}