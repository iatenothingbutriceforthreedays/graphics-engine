//graphics3D

// functions involving drawing 3D data
// to a 2D surface

// Dependencies:
//   shared
//   vector
//   geometry
//   camera
//   Image
//   BMPFunctions
//   graphics2D

// projects (orthographically) a 3D edge onto the camera,
// and draws the result to the given Image.
// this is where camera scale factor is taken into account.
void drawEdgeToCamera (Image img, edge line, camera cam, color c);

// same as above but for a triangle.
void drawTriangleToCamera
(Image img, triangle tri, camera cam, color c);

// filled triangle:
void drawFilledTriangleToCamera 
(Image img, triangle tri, camera cam, color c);