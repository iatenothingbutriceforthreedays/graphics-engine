// Mesh.h
// Mesh is an ADT representing a bunch of
// triangular faces in 3D space

// Dependencies:
//   shared
//   vector
//   geometry

// currently there's no way of modifying the mesh
// once it's been created.
// I think this is probably fine.

typedef struct _mesh *Mesh;

// create a new Mesh:
Mesh newMesh (vector vertices[], unsigned int numVertices,
              intTriple faceIndices[], unsigned int numFaces);

// gets the face at a given index.
triangle getFace(Mesh m, unsigned int index);

// gets the vertex at a given index.
vector getVertex(Mesh m, unsigned int index);

// sorts faces according to distance from a point.
void sortByDistanceFrom (Mesh m, vector point);

int getNumVertices(Mesh m);

int getNumFaces(Mesh m);

void destroyMesh(Mesh m);