#include "Map.h"
#include <stdlib.h>
#include <GL/glew.h>

#include <iostream>
#include <time.h>

using namespace std;

#define X 0
#define Y 1

void Map::generateRandom(double width, double height) {
    int rectangles = 20;
    minHeight    = -(height/4);
    maxHeight    = -(minHeight/2);
    double step  = (width)/rectangles;
    this->width  = width;
    this->height = height;
    /* initialize random seed: */
    srand(time(NULL));

    Vector3d  bottomLeft(-width/2,        -height, 0.0),
             bottomRight( width/2 + step, -height, 0.0),
                 topLeft(-width/2,        minHeight + (rand() % (int)maxHeight + 1), 0.0),
                topRight( width/2 + step, minHeight + (rand() % (int)maxHeight + 1), 0.0);

    points.clear();

    double currentLeft = -(width/2);
    double randomHeight;

    while(currentLeft < width) {
        randomHeight = minHeight + (rand() % (int)maxHeight + 1);
        points.push_back(*new Vector3d(currentLeft,  randomHeight, 0.0));
        points.push_back(*new Vector3d(currentLeft, -height, 0.0));
        currentLeft += step;

        points.push_back(*new Vector3d(currentLeft,  randomHeight, 0.0));
        points.push_back(*new Vector3d(currentLeft, -height, 0.0));
        currentLeft += step;
    }
}

double Map::getDotProduct(Vector3d vertex, Vector3d axis) {
    return (vertex[X] * axis[X]) + (vertex[Y] * axis[Y]) + (vertex[Z] * vertex[Z]);
}

Projection Map::getProjection(vector<Vector3d> vertices, Vector3d axis) {
    double minValue = getDotProduct(vertices[0], axis);
    double maxValue = minValue;

    for(int i = 1; i < vertices.size(); i++) {
        double aux = getDotProduct(vertices[i], axis);
        if(aux < minValue) minValue = aux;
        else if(aux > maxValue) maxValue = aux;
    }
    return Projection(minValue, maxValue);
}

Vector3d Map::getNormal(Vector3d vertex1, Vector3d vertex2) {
    return Vector3d(vertex1[Y] - vertex2[Y], -(vertex1[X] - vertex2[X]), 0.0);
}


void Map::drawMap() {
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_TRIANGLE_STRIP);
        for (auto &point : points) {
            glTexCoord2f((point[X]+width/2)/width, (point[Y]+height/2)/(maxHeight+height/2)); glVertex2d(point[X], point[Y]);
        }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

bool Map::collidesWith(vector<Vector3d> vertices) {
    if(points.size() == 0) return false;

    // Eixos normais das faces do retangulo do foguete
    vector<Vector3d> verticesAxes;
    verticesAxes.push_back(getNormal(vertices[0], vertices[1]));
    verticesAxes.push_back(getNormal(vertices[1], vertices[2]));
    verticesAxes.push_back(getNormal(vertices[2], vertices[3]));
    verticesAxes.push_back(getNormal(vertices[3], vertices[0]));

    for(int i = 0; i < points.size()-3; i++) {
        // Eixos normais dos triangulos do mapa
        vector<Vector3d> triangleAxes;
        triangleAxes.push_back(getNormal(points[i], points[i+1]));
        triangleAxes.push_back(getNormal(points[i+1], points[i+2]));
        triangleAxes.push_back(getNormal(points[i+2], points[i]));

        vector<Vector3d> v;
        v.push_back(points[i]);
        v.push_back(points[i+1]);
        v.push_back(points[i+2]);

        bool con = false;
        for(int j = 0; j < triangleAxes.size(); j++) {
            Projection p1 = getProjection(vertices, triangleAxes[j]);
            Projection p2 = getProjection(v, triangleAxes[j]);

            if(!p1.overlaps(p2)) {
                con = true;
                break;
            }
        }
        if(con) continue;

        con = false;
        for(int j = 0; j < verticesAxes.size(); j++) {
            Projection p1 = getProjection(vertices, verticesAxes[j]);
            Projection p2 = getProjection(v, verticesAxes[j]);

            if(!p1.overlaps(p2)) {
                con = true;
                break;
            }
        }
        if(con) continue;
        return true;
    }

    return false;
}
