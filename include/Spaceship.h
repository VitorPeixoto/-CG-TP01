#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <vector>
#include "RigidBody.h"
#include "Vector3d.h"

using namespace std;

class Spaceship : public RigidBody {
    public:
        Spaceship(double _x, double _y, double _width, double _height, double _speed);

        double getSpeed() { return speed; }
        void   setSpeed(double val) { speed = val; }
        double getFuel() { return fuel; }
        void   setFuel(double val) { fuel = val; }
        bool   hasFuel() { return fuel >= 0.1; }
        int    getTextureId() { return textureId; }
        int    getFireTextureId() { return fireTextureId; }
        int    getFireTextureIndex() { return fireTextureIndex; }
        int    getMaxFireTextureIndex() { return maxFireTextureIndex; }
        int    getExplosionTextureId() { return explosionTextureId; }
        int    getExplosionTextureIndex() { return explosionTextureIndex; }
        int    getMaxExplosionTextureIndex() { return maxExplosionTextureIndex; }
        double getAngle() { return angle; }
        void   incrementAngle() { angle += rotationSpeed; }
        void   decrementAngle() { angle -= rotationSpeed; }
        bool   isEngineOn() { return engineOn; }
        void   setEngineOn(bool val) { engineOn = val; }
        void   setExploded(bool val) { exploded = val; }
        void   explode() { exploded = true; }
        bool   hasExploded() { return exploded; }

        void decreaseFuel();
        void incrementFireTextureIndex();
        void incrementExplosionTextureIndex();
        void moveSpaceship(Vector3d movement);
        void randomLocation(double maxWidth, double maxHeight);
        void drawSpaceship(bool horizontalLock, double lockedAtH);
        void setTextures(int _textureId, int _fireTextureId, int _maxTextureIndex, int _explosionTextureIndex, int _maxExplosionTextureIndex);
    protected:

    private:
        bool   engineOn, exploded;
        double width;
        double height;
        double angle;
        double speed;
        double fuel = 50;
           int textureId,
               fireTextureId,
               explosionTextureId,
               fireTextureIndex,
               explosionTextureIndex,
               maxFireTextureIndex,
               maxExplosionTextureIndex;

       const double rotationSpeed   = 1.0;
       const    int animationFactor = 2;
       const double fuelConsumptionRate = 0.1;
};

#endif // SPACESHIP_H
