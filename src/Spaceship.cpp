#include "../include/Spaceship.h"
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

#define X 0
#define Y 1

#define fire_x 5
#define fire_y0 -10
#define fire_y1 -25

const int spaceshipPositioningMargin = 100;

Spaceship::Spaceship(double _x, double _y, double _width, double _height, double _speed) : RigidBody(_x, _y, 0.0, _width, _height) {
    width  = _width;
    height = _height;
    speed  = _speed;
    angle  = 90; //Rotaciona o foguete para cima
}

void Spaceship::incrementFireTextureIndex() {
    if(fireTextureIndex < (maxFireTextureIndex*animationFactor)) fireTextureIndex++;
    else fireTextureIndex = 0;
}

void Spaceship::incrementExplosionTextureIndex() {
    if(!exploded) return;
    if(explosionTextureIndex < (maxExplosionTextureIndex*animationFactor*5)) explosionTextureIndex++;
    else explosionTextureIndex = 0;
}

void Spaceship::setTextures(int _textureId, int _fireTextureId, int _maxFireTextureIndex, int _explosionTextureId, int _maxExplosionTextureIndex) {
    textureId          = _textureId;
    fireTextureId      = _fireTextureId;
    explosionTextureId = _explosionTextureId;

    fireTextureIndex      = 0;
    explosionTextureIndex = 0;

    maxFireTextureIndex      = _maxFireTextureIndex;
    maxExplosionTextureIndex = _maxExplosionTextureIndex;
}

/**
 * Posiciona a nave em um local aleatorio dentro dos limites passados
 **/
void Spaceship::randomLocation(double maxWidth, double maxHeight) {
    int minHeight = maxHeight/4;
    x = ((rand() % (int)(maxWidth-(spaceshipPositioningMargin*2))) + spaceshipPositioningMargin)-(maxWidth/2);
    y = minHeight + (rand() % (int)minHeight-spaceshipPositioningMargin);
    angle = 90;
    fuel  = 50;
}

void Spaceship::decreaseFuel() {
    fuel -= fuelConsumptionRate;
    if(fuel <= 0.1) {
        engineOn = false;
        fuel = 0.0;
    }
}

void Spaceship::drawSpaceship(bool horizontalLock, double lockedAtH) {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        if(horizontalLock) glTranslated(-lockedAtH + x, 0.0, 0.0);
        int currentIndex = (fireTextureIndex/animationFactor);
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

        currentIndex = (explosionTextureIndex/(animationFactor*5));
        steps        = maxExplosionTextureIndex+1;
        if(exploded) {
            glBindTexture(GL_TEXTURE_2D, explosionTextureId);
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f( currentIndex   *(1.0/steps), 0); glVertex2d(-height/2, height/2);
                glTexCoord2f((currentIndex+1)*(1.0/steps), 0); glVertex2d( height/2, height/2);
                glTexCoord2f((currentIndex+1)*(1.0/steps), 1); glVertex2d( height/2, -height/2);
                glTexCoord2f( currentIndex   *(1.0/steps), 1); glVertex2d(-height/2, -height/2);
            glEnd();
        }
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}
