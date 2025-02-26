#ifndef SPLITPOINTCHOICE_H
#define SPLITPOINTCHOICE_H

#include <vector>
#include "math/include/Vector3.h"
#include "math/include/utils.h"


float centroidMedian(Vector3 axis, std::vector<Vector3> &centroids){
      std::vector<float> centroidPositions;
    for(Vector3 centroid : centroids){
      centroidPositions.push_back(dot(axis,centroid));
    }
    std::sort(centroidPositions.begin(), centroidPositions.end());
    return centroidPositions[centroidPositions.size()/2];
}

float centroidMeanAlongAxis(Vector3 axis, std::vector<Vector3> &centroids){
  float sum = 0;
  for(Vector3 centroid : centroids){
      //Since the axis will be a basis vector e.g(0,0,1)
      // it will sum only the needed value, maybe inefficient since 2 unecessary multiplations need to be performed
      sum += dot(axis, centroid);
      }
      return sum / centroids.size();
}







#endif //SPLITPOINTCHOICE_H
