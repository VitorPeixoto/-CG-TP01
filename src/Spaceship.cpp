#include "Spaceship.h"

#define X 0
#define Y 1

Spaceship::Spaceship(double _x, double _y, double _width, double _height, double _speed) {
    x = _x;
    y = _y;
    width  = _width;
    height = _height;
    speed  = _speed;
}

void Spaceship::moveSpaceship(Vector3d movement) {
    x += movement[X];
    y += movement[Y];
}
