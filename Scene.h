// Scene

// ADT for representing a scene
// including a mesh along with
// a camera and some lights.

// Dependencies:
//   shared
//   vector
//   geometry
//   Mesh
//   object
//   camera
//   Image
//   light

typedef struct _scene *Scene;


// create a new scene
// NOTE. Meshes belonging to objects in 'objects
// are only stored by reference.
// The pointers are copied out of the 'meshes' array
// but the Meshes themselves are not copide.
Scene newScene (camera cam,
                object objects[], unsigned int numObjects,
                light lights[], unsigned int numLights);

void destroyScene (Scene scn);

// render a scene to an Image
void renderSceneToImage(Scene scn, Image img);