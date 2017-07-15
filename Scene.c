// implementation of Scene ADT

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "shared.h"

#include "vector.h"
#include "geometry.h"

#include "camera.h"
#include "Mesh.h"

#include "object.h"

#include "Image.h"
#include "light.h"

#include "graphics3D.h"

#include "Scene.h"

typedef struct _coloredFace {
   color diffuseColor;
   triangle face;
} coloredFace;

typedef struct _scene {
   light *lights;
   unsigned int numLights;
   camera theCamera;
   object *objects;
   unsigned int numObjects;
   coloredFace *faces;
   unsigned int numFaces;
   boolean areFacesSorted;
} scene;

static color computeFaceIllumination (Scene scn, triangle face, color diffuse);
static void precomputeDistances
(Scene scn, vector point, double *distances);
static void renderObject(Scene scn, Image img, unsigned int index);
static void sortFaces(Scene scn);

Scene newScene (camera cam,
                object objects[], unsigned int numObjects,
                light lights[], unsigned int numLights) {
   printf("newScene\n");
   Scene thisScene = malloc(sizeof(scene));
   thisScene->theCamera = cam;

   thisScene->numLights = numLights;
   thisScene->lights = malloc(numLights*sizeof(light));
   memcpy (thisScene->lights, lights, (numLights * sizeof(light)));

   thisScene->numObjects = numObjects;
   thisScene->objects = malloc(numObjects*sizeof(object));
   memcpy (thisScene->objects, objects, (numObjects * sizeof(object)));

   // copy all faces into thisScene->faces
   int i = 0;
   thisScene->numFaces = 0;
   while (i < thisScene->numObjects) {
      thisScene->numFaces += getNumFaces(thisScene->objects[i].mesh);
      i++;
   }
   printf("numFaces = %d\n",thisScene->numFaces);
   thisScene->faces = malloc(thisScene->numFaces*sizeof(coloredFace));


   printf("newScene 2\n");

   i = 0;
   int j;
   int k = 0;
   while (i < thisScene->numObjects) {
      j = 0;
      while (j < getNumFaces(thisScene->objects[i].mesh)) {
         thisScene->faces[k].face = getFace(thisScene->objects[i].mesh, j);
         thisScene->faces[k].diffuseColor = thisScene->objects[i].diffuseColor;
         j++;
         k++;
      }
      i++;
   }

   thisScene->areFacesSorted = FALSE;

   printf("newScene end\n");
   return thisScene;
}

void destroyScene (Scene scn) {
   free(scn->lights);
   free(scn);
}

void renderSceneToImage(Scene scn, Image img) {
   // if faces are not sorted, sort them:
  printf("renderScene\n");
   // then sort faces in order
   if (!scn->areFacesSorted) {
      sortFaces(scn);
   }

   printf("renderScene 2\n");
   color drawColor;
   int i = 0;
   while (i < scn->numFaces) {
      drawColor = computeFaceIllumination(
                     scn,
                     scn->faces[i].face,
                     scn->faces[i].diffuseColor);
      printf("draw tri %d\n", i);
      drawFilledTriangleToCamera(
         img, scn->faces[i].face, scn->theCamera, drawColor);
      i++;
   }
}

static void sortFaces(Scene scn) {
   // currently bubble sort
   // replace if necessary later.

   // sort by distance squared
   // equivalent but faster.

   // precompute distances:
   double distances[scn->numFaces];
   precomputeDistances(scn, scn->theCamera.pos, distances);

   coloredFace tempFace;
   double tempDistance;

   boolean finished = FALSE;
   int i;
   
   while (!finished) {
      finished = TRUE; // until proven FALSE
      i = 1; // start at second face
      while (i < scn->numFaces) {
         if (distances[i] > distances[i - 1]) {
            // if two faces aren't in the right order
            // then swap those two faces:
            tempFace = scn->faces[i];
            scn->faces[i] = scn->faces[i-1];
            scn->faces[i-1] = tempFace;

            // and swap the distance values
            swapDouble (&distances[i], &distances[i-1]);

            // and remember:
            finished = FALSE;
         }
         i++;
      }
   }
   scn->areFacesSorted = TRUE;
}

static void precomputeDistances
(Scene scn, vector point, double *distances) {
   // assume distances is already initialised
   // and enough memory allocated.
   int i = 0;
   while (i < scn->numFaces) {
      distances[i] =
         distanceSquared(
            point,
            centroid(scn->faces[i].face)
         );
      i++;
   }
}

static color computeFaceIllumination (Scene scn, triangle face, color diffuse) {
   // for now assume diffusivity constant = 1
   // illumination is sum of individual illuminations
   // for each light.

   double illumination = 0;
   
   // iterate over lights:
   int i = 0;
   while (i < scn->numLights) {
      illumination += faceIllumination (face, scn->lights[i]);
      i++;
   }

   if (illumination > 1.0) {
      illumination = 1.0;
   }

   diffuse.red *= illumination;
   diffuse.green *= illumination;
   diffuse.blue *= illumination;

   return diffuse;
}