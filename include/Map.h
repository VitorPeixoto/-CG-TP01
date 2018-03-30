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

        int getTexture() { return textureId; }
        void setTexture(int val) { textureId = val; }
    protected:

    private:
        vector<Vector3d> points;
        int textureId;
        double minHeight, maxHeight, width, height;
};

#endif // MAP_H
