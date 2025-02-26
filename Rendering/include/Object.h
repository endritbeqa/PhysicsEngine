#ifndef OBJECT_H
#define OBJECT_H

#include "Physics/include/collisions/BoundingVolumes/AABB.h"
#include "Rendering/include/Geometries.h"
#include "Rendering/include/Wireframe.h"


class IRenderable{
  public:

    Mesh mesh;
    AABB aabb;
    Wireframe wireframe;

    Object(Mesh m){
      this->mesh = m;
      aabb = AABB();
      aabb.buildAABB(mesh);
      Vector3 halfSizes = Vector3(aabb.halfSizeX, aabb.halfSizeY, aabb.halfSizeZ);
      wireframe = AABBWireframe(aabb.center, halfSizes);

    };
    ~Object();


    void draw(){
      mesh.draw();
    }

};







#endif //OBJECT_H
