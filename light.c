#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "shared.h"

#include "vector.h"
#include "geometry.h"

#include "light.h"

light newLight (vector pos, double power) {
   light toReturn = {.pos = pos, .power = power};
   return toReturn;
}

double faceIllumination (triangle f, light l) {
   vector centre = centroid(f);
   vector relative = subtractVectors(l.pos, centre);
   vector norm = faceNormal(f);
   double cosTheta = 
   fabs(dotProduct(norm,relative)
        /(magnitude(relative)*magnitude(norm))
   );

   // printf("%lf\n", cosTheta);

   double i = l.power*cosTheta/distanceSquared(l.pos,centre);
   // printf("%lf\n", i);
   return i;
}