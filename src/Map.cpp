#include "Map.h"
#include <stdlib.h>
#include <GL/glew.h>

#include <iostream>
using namespace std;

#define X 0
#define Y 1

void Map::generateRandom(double width, double height) {
    Vector3d bottomLeft(-width/2, -height/2, 0.0),
             bottomRight(width/2, -height/2, 0.0);

    int heightLimit = height/5;

    cout << width << "  " << height << endl;

    Vector3d topLeft(-width/2, -(rand() % heightLimit + 1), 0.0),
             topRight(width/2, -(rand() % heightLimit + 1), 0.0);

     points.push_back(bottomLeft);
     points.push_back(bottomRight);
     points.push_back(topRight);
     points.push_back(topLeft);
}

void Map::drawMap() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
        for (auto &point : points) {
            glVertex2d(point[X], point[Y]);
        }
    glEnd();
}
