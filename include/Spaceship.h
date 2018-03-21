#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Vector3d.h"

class Spaceship
{
    public:
        Spaceship(double _x, double _y, double _width, double _height, double _speed);

        double getX() { return x; }
        void   setX(double val) { x = val; }
        double getY() { return y; }
        void   setY(double val) { y = val; }
        double getWidth() { return width; }
        void   setWidth(double val) { width = val; }
        double getHeight() { return height; }
        void   setHeight(double val) { speed = val; }
        double getSpeed() { return speed; }
        void   setSpeed(double val) { speed = val; }

        void   moveSpaceship(Vector3d movement);
    protected:

    private:
        double x;
        double y;
        double width;
        double height;
        double speed;
};

#endif // SPACESHIP_H
