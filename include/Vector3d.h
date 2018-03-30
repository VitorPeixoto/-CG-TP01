#ifndef VECTOR3D_H
#define VECTOR3D_H

const int X = 0;
const int Y = 1;
const int Z = 2;

class Vector3d
{
    public:
        Vector3d(double _x, double _y, double _z);

        double getX() { return components[X]; }
        void setX(double val) { components[X] = val; }
        double getY() { return components[Y]; }
        void setY(double val) { components[Y] = val; }
        double getZ() { return components[Z]; }
        void setZ(double val) { components[Z] = val; }
        double getNorm();
        double max();

        double& operator[] (int index);
        Vector3d& operator*= (double arg);
        Vector3d& operator-= (Vector3d& arg);
        Vector3d  operator-  ();
        Vector3d& operator+= (Vector3d& arg);
    protected:

    private:
        double components[3];
};

#endif // VECTOR3D_H
