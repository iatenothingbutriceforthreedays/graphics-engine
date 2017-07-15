// example.c
// uses the libraries to actually do something

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"

#include "Image.h"
#include "Mesh.h"

#include "object.h"

#include "BMPFunctions.h"
#include "graphics2D.h"

#include "camera.h"
#include "graphics3D.h"

#include "light.h"

#include "Scene.h"

#include "readFile.h"

#define OUTPUT_FILE "output/teapot.bmp"
#define INPUT_FILE "input/teapot/teapot.scn"
 
int main (int argc, char *argv[]) {

   intPair dimensions;
   dimensions.x = 800;
   dimensions.y = 800;
   
   Image outputImage = newImage(dimensions);

   color white = {.red = 255, .blue = 255, .green = 255};

   fillImage (outputImage, white);

   printf("Loading scene from %s...\n",INPUT_FILE);
   Scene scene = getSceneFromSCNFile (INPUT_FILE);

   printf("Rendering scene...\n");
   renderSceneToImage(scene, outputImage);

   destroyScene(scene);

   printf("Writing to %s...\n",OUTPUT_FILE);
   writeBMP (outputImage, OUTPUT_FILE);
   printf("Done.\n");

   return EXIT_SUCCESS;
}