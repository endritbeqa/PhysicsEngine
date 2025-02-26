#ifndef PHYSICSENGINE_OBB_H
#define PHYSICSENGINE_OBB_H

#include "math/include/Vector3.h"
#include "math/include/Matrix3.h"
#include "Rendering/include/Geometries.h"


//TODO localCoord should be guaranteed to be orthogonal unit vectors.
class OBB{
public:
    Vector3 center;
    Matrix3 localCoord;
    Vector3 halfSizes;

    OBB(Vector3 center, Matrix3 &localCoord, Vector3 halfSizes);

    bool intersects(OBB &other);

    //TODO implement this using convex hull covariance and using PCA Real-Time Collision Detection Book pg.108
    //or Mirtich96a algorithm
    void calculateTightOBB(Mesh &mesh);


};


#endif //PHYSICSENGINE_OBB_H
