#include "../include/Spaceship.h"

#define X 0
#define Y 1

Spaceship::Spaceship(double _x, double _y, double _width, double _height, double _speed) {
    x = _x;
    y = _y;
    width  = _width;
    height = _height;
    speed  = _speed;
}

void Spaceship::moveSpaceship(Vector3d movement) {
    x += movement[X];
    y += movement[Y];
}

int Spaceship::incrementTextureId() {
    if(fireTextureIndex < (maxFireTextureIndex*animationFactor)) fireTextureIndex++;
    else fireTextureIndex = 0;
}

void Spaceship::setTextures(int _textureId, int _fireTextureId, int _maxFireTextureIndex) {
    textureId = _textureId;
    fireTextureId = _fireTextureId;
    fireTextureIndex = 0;
    maxFireTextureIndex = _maxFireTextureIndex;
}

vector<Vector3d> Spaceship::getVertices() {
    vector<Vector3d> v;
    v.push_back(*new Vector3d(x - width/2, y - height/2, 0.0));
    v.push_back(*new Vector3d(x + width/2, y - height/2, 0.0));
    v.push_back(*new Vector3d(x + width/2, y + height/2, 0.0));
    v.push_back(*new Vector3d(x - width/2, y + height/2, 0.0));
    return v;
}
