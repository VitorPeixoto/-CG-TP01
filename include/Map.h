#ifndef MAP_H
#define MAP_H

#include <vector>
#include <Projection.h>
#include <Vector3d.h>

using namespace std;

class Map {
    public:
        void generateRandom(double width, double height);
        void drawMap();
        Projection getProjection(vector<Vector3d> vertices, Vector3d axis);
        double getDotProduct(Vector3d vertex, Vector3d axis);
        Vector3d getNormal(Vector3d vertex1, Vector3d vertex2);
        bool collidesWith(vector<Vector3d> vertices);
    protected:

    private:
        vector<Vector3d> points;
};

#endif // MAP_H
