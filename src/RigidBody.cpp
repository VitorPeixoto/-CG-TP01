#include "RigidBody.h"
#include <iostream>
#include <GL/glew.h>

using namespace std;
RigidBody::RigidBody() {

}

RigidBody::RigidBody(vector<vector<Vector3d> >_polygons, double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
    polygons = _polygons;
}

RigidBody::RigidBody(double _x, double _y, double _z, double _width, double _height) {
    x = _x;
    y = _y;
    z = _z;

    vector<Vector3d> v;
    v.push_back(*new Vector3d(-_width/2, -_height/2, 0.0));
    v.push_back(*new Vector3d( _width/2, -_height/2, 0.0));
    v.push_back(*new Vector3d( _width/2,  _height/2, 0.0));
    v.push_back(*new Vector3d(-_width/2,  _height/2, 0.0));

    vector<vector<Vector3d> > _polygons;
    _polygons.push_back(v);

    polygons = _polygons;
}
void RigidBody::translate(Vector3d translation) {
    x += translation[X];
    y += translation[Y];
    z += translation[Z];
}

double RigidBody::getDotProduct(Vector3d vertex, Vector3d axis, double x, double y, double z) {
    return ((vertex[X]+x) * axis[X]) + ((vertex[Y]+y) * axis[Y]) + ((vertex[Z]+z) * vertex[Z]);
}

Projection RigidBody::getProjection(vector<Vector3d> vertices, Vector3d axis, double x, double y, double z) {
    double minValue = getDotProduct(vertices[0], axis, x, y, z);
    double maxValue = minValue;

    for(int i = 1; i < vertices.size(); i++) {
        double aux = getDotProduct(vertices[i], axis, x, y, z);
        if(aux < minValue) minValue = aux;
        else if(aux > maxValue) maxValue = aux;
    }
    return Projection(minValue, maxValue);
}

Vector3d RigidBody::getNormal(Vector3d vertex1, Vector3d vertex2) {
    return Vector3d(vertex1[Y] - vertex2[Y], -(vertex1[X] - vertex2[X]), 0.0);
}

bool RigidBody::collidesWith(vector<vector<Vector3d> > otherPolygons, double otherX, double otherY, double otherZ) {
    if(polygons.size() == 0) return false;

    for(auto& otherPolygon: otherPolygons) {
        vector<Vector3d> otherAxes;
        for(int i = 0; i < otherPolygon.size(); i++) {
            // Eixos normais das arestas do outro poligono
            otherAxes.push_back(getNormal(otherPolygon[i], otherPolygon[ (i+1) == otherPolygon.size() ? 0 : (i+1)]));
        }

        bool nextOtherPolygon = false;
        for(auto& myPolygon: polygons) {
            vector<Vector3d> myAxes;
            for(int i = 0; i < myPolygon.size(); i++) {
                // Eixos normais das arestas do outro poligono
                myAxes.push_back(getNormal(myPolygon[i], myPolygon[ (i+1) == myPolygon.size() ? 0 : (i+1)]));
            }

            bool nextMyPolygon = false;
            for(int j = 0; j < myAxes.size(); j++) {
                Projection p1 = getProjection(otherPolygon, myAxes[j], otherX, otherY, otherZ);
                Projection p2 = getProjection(myPolygon, myAxes[j], x, y, z);

                if(!p1.overlaps(p2)) {
                    nextMyPolygon = true;
                    break;
                }
            }
            if(nextMyPolygon) continue;

            nextMyPolygon = false;
            for(int j = 0; j < otherAxes.size(); j++) {
                Projection p1 = getProjection(otherPolygon, otherAxes[j], otherX, otherY, otherZ);
                Projection p2 = getProjection(myPolygon, otherAxes[j], x, y, z);

                if(!p1.overlaps(p2)) {
                    nextMyPolygon = true;
                    break;
                }
            }
            if(nextMyPolygon) continue;
            return true;
        }
    }
    return false;
}

void RigidBody::drawBody() {
    glColor4f(1.0, 0.0, 0.0, 0.5);
    glBegin(GL_TRIANGLE_STRIP);
        for(auto& myPolygon: polygons) {
            for(auto& vertex: myPolygon) {
                glVertex2d(vertex[X], vertex[Y]);
            }
        }
    glEnd();
}
