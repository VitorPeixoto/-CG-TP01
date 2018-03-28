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
        int    getFireTextureIndex() { return fireTextureIndex; }
        int    getMaxFireTextureIndex() { return maxFireTextureIndex; }
        double getAngle() { return angle; }
        void   incrementAngle() { angle += rotationSpeed; }
        void   decrementAngle() { angle -= rotationSpeed; }
        bool   isEngineOn() { return engineOn; }
        void   setEngineOn(bool val) { engineOn = val; }

        int  incrementTextureId();
        void moveSpaceship(Vector3d movement);
        void drawSpaceship(void);
        void setTextures(int _textureId, int _fireTextureId, int _maxTextureIndex);
        vector<Vector3d> getVertices();
    protected:

    private:
        bool   engineOn;
        double x;
        double y;
        double width;
        double height;
        double angle;
        double speed;
           int textureId,
               fireTextureId,
               fireTextureIndex,
               maxFireTextureIndex;

       const double rotationSpeed   = 1.0f;
       const    int animationFactor = 2;
};

#endif // SPACESHIP_H
