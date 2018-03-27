#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <vector>
#include "Vector3d.h"

using namespace std;

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
        int    getTextureId() { return textureId; }
        int    getFireTextureId() { return fireTextureId; }
        int    getFireTextureIndex() { return (fireTextureIndex/animationFactor); }
        int    getMaxFireTextureIndex() { return maxFireTextureIndex; }

        int  incrementTextureId();
        void moveSpaceship(Vector3d movement);
        void setTextures(int _textureId, int _fireTextureId, int _maxTextureIndex);
        vector<Vector3d> getVertices();
    protected:

    private:
        double x;
        double y;
        double width;
        double height;
        double speed;
           int textureId,
               fireTextureId,
               fireTextureIndex,
               maxFireTextureIndex;

       const int animationFactor = 2;
};

#endif // SPACESHIP_H
