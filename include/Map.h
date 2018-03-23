#ifndef MAP_H
#define MAP_H

#include <vector>
#include <Vector3d.h>

using namespace std;

class Map {
    public:
        void generateRandom(double width, double height);
        void drawMap();
    protected:

    private:
        vector<Vector3d> points;
};

#endif // MAP_H
