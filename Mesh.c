// implementation of Mesh ADT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"

#include "Mesh.h"

// for qsort comparison:
#define LESS -1
#define EQUAL 0
#define GREATER 1

static void precomputeDistances
(Mesh m, vector point, double *distances);

typedef struct _mesh {
   // array of vertices in 3D space
   vector *vertices;
   unsigned int numVertices;

   // array of triples of indices to 'vertices'
   // each triple defines a triangular face
   intTriple *faceIndices;
   unsigned int numFaces;
} mesh;

Mesh newMesh (vector vertices[], unsigned int numVertices,
              intTriple faceIndices[], unsigned int numFaces) {
   Mesh thisMesh = malloc(sizeof(mesh));
   thisMesh->vertices = malloc (numVertices * sizeof(vector));
   memcpy (thisMesh->vertices, vertices, (numVertices * sizeof(vector)));
   thisMesh->faceIndices = malloc (numFaces * sizeof(intTriple));
   memcpy (thisMesh->faceIndices, faceIndices, (numFaces * sizeof(intTriple)));

   thisMesh->numVertices = numVertices;
   thisMesh->numFaces = numFaces;

   return thisMesh;
}

void destroyMesh (Mesh m) {
   free (m->vertices);
   free (m->faceIndices);
   free (m);
}

triangle getFace(Mesh m, unsigned int index) {
   assert (0 <= index && index < m->numFaces);
   triangle toReturn;
   intTriple indices = m->faceIndices[index];
   toReturn.a = getVertex(m, indices.a);
   toReturn.b = getVertex(m, indices.b);
   toReturn.c = getVertex(m, indices.c);
   return toReturn;
}

vector getVertex(Mesh m, unsigned int index) {
   assert (0 <= index && index < m->numVertices);
   return m->vertices[index];
}

int getNumVertices(Mesh m) {
   return m->numVertices;
}

int getNumFaces(Mesh m) {
   return m->numFaces;
}

void sortByDistanceFrom (Mesh m, vector point)  {
   // currently bubble sort
   // replace if necessary later.

   // sort by distance squared
   // equivalent but faster.

   // qsort(m->faceIndices, m->numFaces, sizeof(intTriple), 

   // precompute distances:
   double distances[m->numFaces];
   precomputeDistances(m, point, distances);


   intTriple tempFace;
   double tempDistance;

   boolean finished = FALSE;
   int i;
   
   while (!finished) {
      finished = TRUE; // until proven FALSE
      i = 1; // start at second face
      while (i < m->numFaces) {
         if (distances[i] > distances[i - 1]) {
            // if two faces aren't in the right order
            // then swap those two faces:
            tempFace = m->faceIndices[i];
            m->faceIndices[i] = m->faceIndices[i-1];
            m->faceIndices[i-1] = tempFace;

            // and swap the distance values
            swapDouble (&distances[i], &distances[i-1]);
            

            // and remember:
            finished = FALSE;
         }
         i++;
      }
   }
}

static void precomputeDistances
(Mesh m, vector point, double *distances) {
   // assume distances is already initialised and allocated enough memory
   int i = 0;
   while (i < m->numFaces) {
      distances[i] =
         distanceSquared(point, centroid(getFace(m, i)));
      i++;
   }
}
