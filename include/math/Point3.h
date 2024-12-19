#ifndef PHYSICSENGINE_POINT3_H
#define PHYSICSENGINE_POINT3_H


class Point3{
public:
    double x, y, z;
    Point3(): x(0.0f), y(0.0f), z(0.0f) {}
    Point3(double x, double y, double z): x(x), y(y), z(z) {}
};

#endif //PHYSICSENGINE_POINT3_H
