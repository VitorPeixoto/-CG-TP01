#include "../include/Vector3d.h"

#define X 0
#define Y 1
#define Z 2

Vector3d::Vector3d(double _x, double _y, double _z) {
    components[X] = _x;
    components[Y] = _y;
    components[Z] = _z;
}

double& Vector3d::operator[] (int index) {
   if(index >= 0 && index < 3)
      return components[index];
}

Vector3d& Vector3d::operator*= (double arg) {
    this->components[X] *= arg;
    this->components[Y] *= arg;
    this->components[Z] *= arg;

    return *this;
}

Vector3d& Vector3d::operator-= (Vector3d& arg) {
    this->components[X] -= arg.getX();
    this->components[Y] -= arg.getY();
    this->components[Z] -= arg.getZ();

    return *this;
}

Vector3d& Vector3d::operator+= (Vector3d& arg) {
    this->components[X] += arg.getX();
    this->components[Y] += arg.getY();
    this->components[Z] += arg.getZ();

    return *this;
}

