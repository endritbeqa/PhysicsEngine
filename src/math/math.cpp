//this file contains implementations of header file functions that cause multiple definitions
//TODO refactor coe so that this file is not necessary if possible

#include "include/math/Point3.h"
#include "include/math/Vector3.h"


Point3::Point3(Vector3&& v):x(v.x), y(v.y), z(v.z){}



