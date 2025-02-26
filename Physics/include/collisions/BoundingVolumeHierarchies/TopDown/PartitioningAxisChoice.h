#ifndef PARTITIONINGAXISCHOICE_H
#define PARTITIONINGAXISCHOICE_H

#include "math/include/Vector3.h"
#include "Physics/include/collisions/BoundingVolumes/AABB.h"


class AxisSelector{
  public:
    AxisSelector(){}
    ~AxisSelector(){}

    virtual Vector3 selectAxis(AABB parentBv);


};


class RoundRobin: public AxisSelector{
  public:
    unsigned int axisIndex;

    RoundRobin();
    ~RoundRobin();

    Vector3 selectAxis(AABB parentBV){
      switch (axisIndex){
        case 0: axisIndex+=1; axisIndex%=3; return Vector3(1,0,0);
        case 1: axisIndex+=1; axisIndex%=3; return Vector3(0,1,0);
        case 2: axisIndex+=1; axisIndex%=3; return Vector3(0,0,1);
      }
      throw std::invalid_argument("Round Robin Axis Selection: Invalid axisIndex");
    }
};

class LongestAxis : public AxisSelector{
public:

  Vector3 selectAxis(AABB parentBV){
    if(parentBV.halfSizes[0]>=parentBV.halfSizes[1] && parentBV.halfSizes[0]>=parentBV.halfSizes[2]) return Vector3(1,0,0);
    if(parentBV.halfSizes[1]>=parentBV.halfSizes[0] && parentBV.halfSizes[1]>=parentBV.halfSizes[2]) return Vector3(0,1,0);
    return Vector3(0,0,1);
  }
};

#endif //PARTITIONINGAXISCHOICE_H