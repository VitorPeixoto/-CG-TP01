#include "../include/Spaceship.h"
#include <GL/freeglut.h>
#define X 0
#define Y 1

#define fire_x 5
#define fire_y0 -10
#define fire_y1 -25

Spaceship::Spaceship(double _x, double _y, double _width, double _height, double _speed) {
    x = _x;
    y = _y;
    width  = _width;
    height = _height;
    speed  = _speed;
    angle  = 90; //Rotaciona o foguete para cima
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

void Spaceship::drawSpaceship(void) {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslated(x, y, 0.0);
        int currentIndex = fireTextureIndex;
        int steps        = maxFireTextureIndex+1;

        glRotated(angle-90, 0.0, 0.0, 1.0);

        if(engineOn) {
            glBindTexture(GL_TEXTURE_2D, fireTextureId);
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f( currentIndex   *(1.0/steps), 0); glVertex2d(-fire_x, fire_y0);
                glTexCoord2f((currentIndex+1)*(1.0/steps), 0); glVertex2d( fire_x, fire_y0);
                glTexCoord2f((currentIndex+1)*(1.0/steps), 1); glVertex2d( fire_x, fire_y1);
                glTexCoord2f( currentIndex   *(1.0/steps), 1); glVertex2d(-fire_x, fire_y1);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D, textureId);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex2d(-width/2,  height/2);
            glTexCoord2f(1, 0); glVertex2d( width/2,  height/2);
            glTexCoord2f(1, 1); glVertex2d( width/2, -height/2);
            glTexCoord2f(0, 1); glVertex2d(-width/2, -height/2);
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
