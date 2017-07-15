#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "shared.h"
#include "vector.h"
#include "geometry.h"
#include "Image.h"
#include "graphics2D.h"

#include "camera.h"

#include "graphics3D.h"

void drawTriangleToCamera
(Image img, triangle tri, camera cam, color c) {

   pixelTriangle toDraw =
      projectTriangleToGrid(tri, cam, getDimensions(img));

   drawTri(img,toDraw,c);
}

void drawFilledTriangleToCamera
(Image img, triangle tri, camera cam, color c) {

   pixelTriangle toDraw =
      projectTriangleToGrid(tri, cam, getDimensions(img));
   // color b = {.red = 0, .blue = 0, .green = 0};
   // drawTri(img,toDraw,b);
   drawFilledTri(img,toDraw,c);
}