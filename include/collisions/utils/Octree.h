#ifndef PHYSICSENGINE_OCTREE_H
#define PHYSICSENGINE_OCTREE_H

#include <vector>
#include <array>
#include <memory>
#include "AABB.h"

class Octree {
public:

    Octree(AABB& bBox, size_t capacity): boundary(bBox), capacity(capacity){}

    AABB boundary;
    std::vector<Point3> points;
    std::array<std::unique_ptr<Octree>, 8> children;
    bool isDivided;
    size_t capacity;



    void divide(){
        double quarterSize = boundary.halfSize/2.0;
        for (int i=0; i<8; i++){
            int x = (i%2) ? quarterSize : -quarterSize;
            int y = (i/2)%2 ? quarterSize : -quarterSize;
            int z = (i/4)%2 ? quarterSize : -quarterSize;
            Point3 center(boundary.center.x + x,
                          boundary.center.y + y,
                          boundary.center.z + z);
            AABB bBox(center, quarterSize);
            children[i] = std::make_unique<Octree>(Octree(bBox, capacity));
        }
        isDivided = true;
    }

    bool insert(const Point3& point){
        if (!boundary.contains(point)){
            return false;
        }

        if (points.size() < capacity){
            points.push_back(point);
            return true;
        }

        if(!isDivided){
            divide();
        }

        for (std::unique_ptr<Octree>& child: children){
            if(child->insert(point)){
                return true;
            }
        }
        return false;
    }

    void query(AABB& range, std::vector<Point3>& found){
        std::vector<Point3> result();
        if(!boundary.intersects(range)){
            return ;
        }

        for(const auto& point: points){
            if (range.contains(point)){
                found.push_back(point);
            }
        }

        if(isDivided){
            for(std::unique_ptr<Octree>& child:children){
                child->query(range, found);
            }
        }

    }


};


#endif //PHYSICSENGINE_OCTREE_H
