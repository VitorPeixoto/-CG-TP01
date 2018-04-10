#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <vector>
#include <RigidBody.h>
#include <Vector3d.h>
#include <Texture.h>

using namespace std;

class Spaceship : public RigidBody {
    public:
        Spaceship(double _x, double _y, double _width, double _height, double _speed);

        double getSpeed() { return speed; }
        void   setSpeed(double val) { speed = val; }
        double getFuel() { return fuel; }
        void   setFuel(double val) { fuel = val; }
        bool   hasFuel() { return fuel >= 0.1; }
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
        void setTextures(Texture* _spaceshipTexture, Texture* _fireTexture, Texture* _explosionTexture);
    protected:

    private:
        bool   engineOn, exploded;
        double width;
        double height;
        double angle;
        double speed;
        double fuel = 50;
        Texture *spaceshipTexture,
                *fireTexture,
                *explosionTexture;

       const double rotationSpeed   = 1.0;
       const    int animationFactor = 2;
       const double fuelConsumptionRate = 0.1;
};

#endif // SPACESHIP_H
