#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector3d.h"
#include "Projection.h"
#include <vector>
using namespace std;

class RigidBody {
    public:
        RigidBody(vector<vector<Vector3d> >_polygons, double _x, double _y, double _z);
        RigidBody(double _x, double _y, double _z, double _width, double _height);
        RigidBody();

        vector<vector<Vector3d> > getPolygons() { return polygons; }
        double getX() { return x; }
        void setX(double val) { x = val; }
        double getY() { return y; }
        void setY(double val) { y = val; }
        double getZ() { return z; }
        void setZ(double val) { z = val; }

        void translate(Vector3d translation);
        bool collidesWith(vector<vector<Vector3d> > otherPolygons, double otherX, double otherY, double otherZ);
        void drawBody();
    protected:
        // Lista de poligonos convexos que formam o corpo
        vector<vector<Vector3d> > polygons;
        double x, y, z;
    private:
        Vector3d getNormal(Vector3d vertex1, Vector3d vertex2);
        Projection getProjection(vector<Vector3d> vertices, Vector3d axis, double x, double y, double z);
        double getDotProduct(Vector3d vertex, Vector3d axis, double x, double y, double z);
};

#endif // RIGIDBODY_H
