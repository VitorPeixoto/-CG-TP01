#include "Map.h"
#include <stdlib.h>
#include <GL/glew.h>

#include <iostream>
#include <time.h>

using namespace std;

#define X 0
#define Y 1

Map::Map() {

}

void Map::generateRandom(double width, double height) {
    int rectangles = 60;
    minHeight    = -(height/2.5);
    maxHeight    = -(minHeight/1.5);
    double step  = (width)/rectangles;
    this->width  = width;
    this->height = height;
    /* initialize random seed: */
    srand(time(NULL));

    Vector3d bottomRight( width/2, -height, 0.0),
             topRight( width/2, minHeight + (rand() % (int)maxHeight + 1), 0.0);

    points.clear();
    polygons.clear();

    double currentLeft = -(width/2);
    double randomHeight;

    while(currentLeft <= (width/2)) {
        randomHeight = minHeight + (rand() % (int)maxHeight + 1);
        Vector3d v0 = Vector3d(currentLeft,  randomHeight, 0.0);

        points.push_back(v0);
        Vector3d v1 = Vector3d(currentLeft, -height, 0.0);

        points.push_back(v1);
        currentLeft += step;

        Vector3d v2 = Vector3d(currentLeft,  randomHeight, 0.0);

        points.push_back(v2);
        Vector3d v3 = Vector3d(currentLeft, -height, 0.0);

        points.push_back(v3);
        currentLeft += step;
    }
    points.push_back(topRight);
    points.push_back(bottomRight);

    vector<Vector3d> v;
    for(int i = 0; i < points.size()-2; i++) {
        v.push_back(points[i]);
        v.push_back(points[i+1]);
        v.push_back(points[i+2]);
        polygons.push_back(v);
        v.clear();
    }
}

void Map::drawMap() {
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glBegin(GL_TRIANGLE_STRIP);
        for (auto &point : points) {
            glTexCoord2f((point[X]+width/2)/width, ((point[Y]+height)/(height))); glVertex2d(point[X], point[Y]);
        }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    //drawBody();
}

Vector3d Map::getRandomPlane() {
    // Para não vir o V0 aqui
    int random = (rand() % (points.size()-2))+1;

    /**
        Os segmentos planos do mapa são formados pelos vértices múltiplos de 4 e o segundo vértice seguinte
        Ex.: V4 e V6, V8 e V10 ...
    */

    //Através de operação de bits obtem o multiplo de 4 mais próximo abaixo de random
    int primeiroVertice = ((random) & ~0x03);

    double x = (points[primeiroVertice][X] + points[primeiroVertice+2][X])/2;
    double y = points[primeiroVertice][Y];
    return Vector3d(x, y, 0.0);
}
