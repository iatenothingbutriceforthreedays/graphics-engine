// testReadFile.c
// tests the file reading functions.
// uses testObj.obj for input
// compile along with:
// readFile.c
// vector.c
// shared.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"

#include "Mesh.h"

#include "light.h"
#include "object.h"
#include "Image.h"
#include "camera.h"
#include "Scene.h"

#include "readFile.h"

#define INPUT_MESH "input/testObj.msh"
 
int main (int argc, char *argv[]) {
   printf("Testing readFile.c\n");
   printf("Testing getMeshFromMSHFile\n");
   Mesh m = getMeshFromMSHFile(INPUT_MESH);
   assert(getNumVertices(m) == 4);
   assert(getNumFaces(m) == 3);
   assert(equalVector(getVertex(m, 0), newVector(0.0,0.0,0.0)));
   assert(equalVector(getVertex(m, 3), newVector(0.0,0.0,1.0)));
   printf("Passed.\n");
   return EXIT_SUCCESS;
}