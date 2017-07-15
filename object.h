// object.h
// object is an concrete type representing
// the components that make up an object
// currently just a Mesh and a color.

// Dependencies:
//   shared
//   vector
//   geometry
//   mesh

typedef struct _object {
   Mesh mesh;
   color diffuseColor;
} object;