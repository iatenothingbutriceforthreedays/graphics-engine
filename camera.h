// camera

// functions involving a camera object –
// transformations from 3D space
// to a 2D viewer

// (currently only orthographic projection).

// Dependencies:
//   shared
//   vector
//   geometry

// concrete camera type:
typedef struct _camera {
   // a (square) (orthographic) camera
   // (for now)
   // the view is defined by:

   // position of the camera
   // (bottom-right of screen)
   vector pos;

   // normal vector:
   // (forwards)
   vector normal;

   // and angle of rotation around that axis,
   // in radians
   // (this is called axis-angle representation)
   double angle;
 
   // and scale (in spatial units)
   // sort of like the opposite of zoom.
   // this determines how much of the scene
   // can be seen from the camera.
   // corresponds to the length of the camera's
   // longest side (this depends on image dimensions)
   double scale;

} camera;

// creates a new camera:
camera newCamera (vector pos, vector normal, double angle, double size);

// orthographic projection of v onto the camera.
// v is NOT scaled in this function!
vector orthoProjection (vector v, camera cam);

// this projects the point in 3D space
// onto a pixel grid
intPair projectPointToGrid
(vector point, camera cam, intPair dimensions);

// same thing but for a triangle
pixelTriangle projectTriangleToGrid
(triangle tri, camera cam, intPair dimensions);