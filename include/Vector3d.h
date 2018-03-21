#ifndef VECTOR3D_H
#define VECTOR3D_H

#define X 0
#define Y 1
#define Z 2

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

        double& operator[] (int index);
        Vector3d& operator*= (double arg);
    protected:

    private:
        double components[3];
};

#endif // VECTOR3D_H
