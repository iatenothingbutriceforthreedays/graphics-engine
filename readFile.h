// readFile

// functions for reading mesh data
// from files. see 'formats.txt' for info
// on custom file formats.

// Dependencies:
//   shared
//   vector
//   geometry
//   Mesh
//   light
//   object
//   camera
//   Scene

// max. length of lines
#define LINE_WIDTH 100

// path delimiter: this is for Mac OS X (and Unix I think).
// changing this might work for other systems, or it might not.
#define PATH_DELIMITER '/'

// characters which determine what each line describes
#define VERTEX_CHAR 'v'
#define FACE_CHAR 'f'
#define COLOUR_CHAR 'c'

#define OBJECT_CHAR 'o'
#define CAMERA_CHAR 'c'
#define LIGHT_CHAR 'l'

// read a Mesh from a .msh file.
Mesh getMeshFromMSHFile(char *filename);

// read a Scene from a .scn file.
Scene getSceneFromSCNFile(char *filename);