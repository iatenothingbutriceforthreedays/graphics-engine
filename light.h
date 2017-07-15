// light

// light type (concrete)
// simple directionless point light.
// as well as functions for determining illumination

// Dependencies:
//   vector

typedef struct _light {
   // position of light in global space
   vector pos;

   // power
   // units are length^2*intensity
   // (illumination of a pixel has dimensions
   // of intensity).
   double power;
} light;

light newLight (vector pos, double power);

// compute component of illumination due to a given light
// only in greyscale at the moment.
double faceIllumination (triangle face, light l);