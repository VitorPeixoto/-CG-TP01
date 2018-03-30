#ifndef LANDINGSITE_H
#define LANDINGSITE_H

#include <vector>
#include "Vector3d.h"
#include "RigidBody.h"
using namespace std;

class LandingSite : public RigidBody {
    public:
        LandingSite(double _x, double _y, double _width, double _height);

        double getWidth() { return width; }
        void   setWidth(double val) { width = val; }
        double getHeight() { return height; }
        void   setHeight(double val) { height = val; }

        int getTexture() { return textureId; }
        void setTexture(int val) { textureId = val; }

        void drawSite();
    protected:

    private:
        double width;
        double height;
        double r;
        double g;
        double b;
        int textureId;
};

#endif // LANDINGSITE_H
