#include "LandingSite.h"
#include <GL/glew.h>

LandingSite::LandingSite(double _x, double _y, double _width, double _height) : RigidBody(_x, _y, 0.0, _width, _height) {
    width  = _width;
    height = _height;
    r = 1.0;
    g = 0.0;
    b = 0.0;
}

void LandingSite::drawSite() {
    glColor3f(r, g, b);
    if(r >= 1.0 && g <= 0.0 && b <= 1.0) b += 0.02;
    if(r >= 0.0 && g <= 0.0 && b >= 1.0) r -= 0.02;
    if(r <= 0.0 && g <= 1.0 && b >= 1.0) g += 0.02;
    if(r <= 0.0 && g >= 1.0 && b >= 0.0) b -= 0.02;
    if(r <= 1.0 && g >= 1.0 && b <= 0.0) r += 0.02;
    if(r >= 1.0 && g >= 0.0 && b <= 0.0) g -= 0.02;


    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureId);
    glPushMatrix();
        glTranslated(x, y, 0.0);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex2d(-width/2,  height/2);
            glTexCoord2f(1, 0); glVertex2d( width/2,  height/2);
            glTexCoord2f(1, 1); glVertex2d( width/2, -height/2);
            glTexCoord2f(0, 1); glVertex2d(-width/2, -height/2);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
