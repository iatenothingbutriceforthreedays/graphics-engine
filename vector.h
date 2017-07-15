// vector

// vector type and functions

// Dependencies:
//   shared

typedef struct _vector {
   // 3D or 2D vector of doubles
   // convention is that a
   // 2D vector has z == 0.
   double x;
   double y;
   double z;
} vector;

// returns a new vector:
vector newVector (double x, double y, double z);

// tests if two vectors are equal
// (or at least, very close - due to 
// floating point precision limitation).
boolean equalVector (vector u, vector v);

// these are pretty self-explanatory:
vector addVectors (vector u, vector v);
vector subtractVectors (vector u, vector v);
vector scaleVector (vector u, double s);
double dotProduct (vector u, vector v);
vector crossProduct (vector u, vector v);
double magnitude (vector u);
double magnitudeSquared (vector u);
double distanceSquared (vector u, vector v);

// just the magnitude of the projection
// (u onto v)
double scalarProjection (vector u, vector v);
// (u onto v)
vector vectorProjection (vector u, vector v);
// (u from v)
vector vectorRejection (vector u, vector v);

// u rotated by theta counter-clockwise around the z-axis
// (right-handed system)
vector rotate2DVector(vector u, double theta);

// convert a 3D vector to a 2D integer pair:
// just ignores the z component
intPair vectorToIntPair(vector u);

// and vice versa:
vector intPairToVector (intPair ip);