#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"
#include "Mesh.h"

#include "camera.h"
#include "light.h"
#include "object.h"
#include "Image.h"
#include "Scene.h"

#include "readFile.h"

static unsigned int howManyLinesStartWith (FILE *input, char toFind);

Mesh getMeshFromMSHFile(char *filename) {
   FILE *input = fopen(filename, "r");
   if (input == NULL) {
      printf("Couldn't open %s\n", filename);
   }
   assert(input != NULL);

   // first count how many vertices, faces
   unsigned int numVertices =
      howManyLinesStartWith (input, VERTEX_CHAR);
   unsigned int numFaces = howManyLinesStartWith (input, FACE_CHAR);
   
   int result;
   char *fgetsResult;

   vector vertices[numVertices];
   intTriple faces[numFaces];

   unsigned int vertexIndex = 0;
   unsigned int faceIndex = 0;

   char firstChar;

   boolean reading = TRUE;

   // read:
   char latestString[LINE_WIDTH];
   while (reading) {
      fgetsResult = fgets(latestString, LINE_WIDTH, input);
      assert (fgetsResult != NULL);
      // puts next string into latestString, asserts no errors.
      if (latestString[0] == VERTEX_CHAR) {
         // if the line starts with 'v'
         result = sscanf(latestString, "v %lf %lf %lf",
                 &vertices[vertexIndex].x,
                 &vertices[vertexIndex].y,
                 &vertices[vertexIndex].z);
         assert (result == 3);
         // assert that correct number of arguments were read.
         vertexIndex++;
      } else if (latestString[0] == FACE_CHAR) {
         // if the line starts with 'f'
         result = sscanf(latestString, "f %d %d %d",
                 &faces[faceIndex].a,
                 &faces[faceIndex].b,
                 &faces[faceIndex].c);
         assert (result == 3);
         // assert that correct number of arguments were read.

         // .obj numbering starts from 1 while
         // we want to start from zero, so fix that:
         faces[faceIndex].a--;
         faces[faceIndex].b--;
         faces[faceIndex].c--;

         faceIndex++;
      }

      // check if we're about to hit EOF after the next character

      firstChar = fgetc(input);
      if (feof(input)) {
         reading = FALSE;
      }
      ungetc (firstChar, input);
   }
   assert(vertexIndex == numVertices);
   assert(faceIndex == numFaces);
   Mesh toReturn = newMesh (vertices, numVertices, faces, numFaces);

   fclose(input);
   return toReturn;
}

Scene getSceneFromSCNFile(char *filename) {
   FILE *input = fopen(filename, "r");
   if (input == NULL) {
      printf("Couldn't open %s\n", filename);
   }
   assert(input != NULL);

   // first count how many objects, lights
   unsigned int numObjects = howManyLinesStartWith (input, OBJECT_CHAR);
   unsigned int numLights = howManyLinesStartWith (input, LIGHT_CHAR);

   // must be exactly one camera.
   assert (howManyLinesStartWith (input, CAMERA_CHAR) == 1);

   int result;
   char *fgetsResult;

   // temp container for filename strings
   char meshFile[LINE_WIDTH];

   int pathToFolderLength = strlen(filename) - strlen(strrchr(filename,PATH_DELIMITER)) + 1;

   char pathToFolder[pathToFolderLength + 1];
   strncpy(pathToFolder,filename,pathToFolderLength);
   pathToFolder[pathToFolderLength] = '\0';

   char pathToMeshFile[LINE_WIDTH + pathToFolderLength];

   light lights[numLights];
   object objects[numObjects];
   camera theCamera;

   unsigned int objectIndex = 0;
   unsigned int lightIndex = 0;

   char firstChar;

   boolean reading = TRUE;

   // read:
   char latestString[LINE_WIDTH];
   while (reading) {
      fgetsResult = fgets(latestString, LINE_WIDTH, input);
      assert (fgetsResult != NULL);
      // puts next string into latestString, asserts no errors.
      if (latestString[0] == CAMERA_CHAR) {
          result = sscanf(latestString,
             "c %lf %lf %lf"
               "%lf %lf %lf"
               "%lf %lf",
             &theCamera.pos.x,
             &theCamera.pos.y,
             &theCamera.pos.z,
             &theCamera.normal.x,
             &theCamera.normal.y,
             &theCamera.normal.z,
             &theCamera.angle,
             &theCamera.scale);
          assert(result == 8);
      } else if (latestString[0] == LIGHT_CHAR) {
         result = sscanf(latestString, "l %lf %lf %lf %lf",
                 &lights[lightIndex].pos.x,
                 &lights[lightIndex].pos.y,
                 &lights[lightIndex].pos.z,
                 &lights[lightIndex].power);
         assert (result == 4);
         lightIndex++;
      } else if (latestString[0] == OBJECT_CHAR) {
         result = sscanf(latestString, "o %s %hhu %hhu %hhu",
                 meshFile,
                 &objects[objectIndex].diffuseColor.red,
                 &objects[objectIndex].diffuseColor.green,
                 &objects[objectIndex].diffuseColor.blue);
         strcpy(pathToMeshFile, pathToFolder);
         strcat(pathToMeshFile, meshFile);

         objects[objectIndex].mesh = getMeshFromMSHFile(pathToMeshFile);
         assert (result == 4);
         objectIndex++;
      }

      // check if we're about to hit EOF after the next character

      firstChar = fgetc(input);
      if (feof(input)) {
         reading = FALSE;
      }
      ungetc (firstChar, input);
   }
   assert(objectIndex == numObjects);
   assert(lightIndex == numLights);
   Scene toReturn =
      newScene (theCamera, objects, numObjects, lights, numLights);
   fclose(input);
   return toReturn;
   
}

static unsigned int howManyLinesStartWith (FILE *input, char toFind) {
   unsigned int count = 0;

   int currentChar = NEWLINE_CHAR;
   while (currentChar != EOF) {
      if (currentChar == NEWLINE_CHAR) {
         currentChar = fgetc(input);
         if (currentChar == toFind) {
            assert(count < INT_MAX);
            count++;
         }
      } else {
         currentChar = fgetc(input);
      }
   }
   rewind(input); // puts stream pointer back to start.
   return count;
}

