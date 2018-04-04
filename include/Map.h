#ifndef MAP_H
#define MAP_H

#include <vector>
#include <Projection.h>
#include <Vector3d.h>
#include "RigidBody.h"

using namespace std;

class Map : public RigidBody {
    public:
        Map();
        void generateRandom(double width, double height);
        void drawMap();
        Vector3d getRandomPlane();

        int  getTexture() { return textureId; }
        void setTexture(int val) { textureId = val; }
        double getWidth() { return width; }
        double getHeight() { return height; }
        double getLeft() { return -(width/2); }
        double getRight() { return (width/2); }
        double getTop() { return (height); }
        double getBottom() { return -(height); }
        bool   isOutOfBounds(double x, double y);
    protected:

    private:
        vector<Vector3d> points;
        int textureId;
        double width, height;
};

#endif // MAP_H
