#include "ScreenController.h"

extern double orthoHalfWidth, orthoHalfHeight;
extern int windowWidth, windowHeight;
extern bool isExiting, isOnHelp, isOnCredits;
int textTexture, bgTexture, helpTexture, creditsTexture;

void inicializaMenu() {
    //anti-aliasing
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glClearColor(0, 0, 0.0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    bgTexture = SOIL_load_OGL_texture(
        "../../src/images/MainMenuBackground.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!bgTexture) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    textTexture = SOIL_load_OGL_texture(
        "../../src/images/MainMenuText.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!textTexture) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    helpTexture = SOIL_load_OGL_texture(
        "../../src/images/HelpText.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!helpTexture) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
    creditsTexture = SOIL_load_OGL_texture(
        "../../src/images/CreditsText.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);
	if (!creditsTexture) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }
}

void resizeMenu(int w, int h) {
    double aspectRatio = (double)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    orthoHalfWidth  = 500 * aspectRatio;
    orthoHalfHeight = 500;

    glOrtho(-orthoHalfWidth, orthoHalfWidth, -orthoHalfHeight, orthoHalfHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawMainMenu() {
    glBindTexture(GL_TEXTURE_2D, textTexture);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex2d(-orthoHalfWidth,  orthoHalfHeight);
        glTexCoord2f(1, 0); glVertex2d( orthoHalfWidth,  orthoHalfHeight);
        glTexCoord2f(1, 1); glVertex2d( orthoHalfWidth, -orthoHalfHeight);
        glTexCoord2f(0, 1); glVertex2d(-orthoHalfWidth, -orthoHalfHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.0, 0.0, 0.0);
    if(isExiting) drawExitingConfirmation(0.0, -40.0);
}

void drawHelp() {
    glBindTexture(GL_TEXTURE_2D, helpTexture);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex2d(-orthoHalfWidth,  orthoHalfHeight);
        glTexCoord2f(1, 0); glVertex2d( orthoHalfWidth,  orthoHalfHeight);
        glTexCoord2f(1, 1); glVertex2d( orthoHalfWidth, -orthoHalfHeight);
        glTexCoord2f(0, 1); glVertex2d(-orthoHalfWidth, -orthoHalfHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.0, 0.0, 0.0);
    if(isExiting) drawExitingConfirmation(0.0, -40.0);
}

void drawCredits() {
    glBindTexture(GL_TEXTURE_2D, creditsTexture);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex2d(-orthoHalfWidth,  orthoHalfHeight);
        glTexCoord2f(1, 0); glVertex2d( orthoHalfWidth,  orthoHalfHeight);
        glTexCoord2f(1, 1); glVertex2d( orthoHalfWidth, -orthoHalfHeight);
        glTexCoord2f(0, 1); glVertex2d(-orthoHalfWidth, -orthoHalfHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.0, 0.0, 0.0);
    if(isExiting) drawExitingConfirmation(0.0, -40.0);
}

void drawMenu() {
    glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bgTexture);
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex2d(-orthoHalfWidth,  orthoHalfHeight);
            glTexCoord2f(1, 0); glVertex2d( orthoHalfWidth,  orthoHalfHeight);
            glTexCoord2f(1, 1); glVertex2d( orthoHalfWidth, -orthoHalfHeight);
            glTexCoord2f(0, 1); glVertex2d(-orthoHalfWidth, -orthoHalfHeight);
        glEnd();
        if(isOnHelp) drawHelp();
        else if(isOnCredits) drawCredits();
        else drawMainMenu();
    glutSwapBuffers();
}

void drawText(char* s, float x, float y) {
    unsigned int i;
    glRasterPos2f(x, y);

    for (i = 0; i < strlen (s); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }
}

double getStringBitmapLength(char* str) {
    return ((double)glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (unsigned const char*) str)/windowWidth)*(orthoHalfWidth*2);
}

void drawRestartingConfirmation() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Voce tem certeza que deseja reiniciar o jogo?";
    drawText(message, -getStringBitmapLength(message)/2, 0);

    message = (char*)"S/N";
    drawText("S/N", -getStringBitmapLength(message)/2, -20);
}

void drawExitingConfirmation(double x, double y) {
    char *message = (char*)"Voce tem certeza que deseja sair do jogo?";
    drawText(message, x-getStringBitmapLength(message)/2, y);

    message = (char*)"S/N";
    drawText("S/N", x-getStringBitmapLength(message)/2, y-20);
}

void drawExitingConfirmation() {
    glColor3f(1.0, 1.0, 1.0);
    drawExitingConfirmation(0.0, 0.0);
}

void drawPaused() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Pausado";
    drawText(message, -getStringBitmapLength(message)/2, 0);
}

void drawLandedOn() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Parabens, voce pousou corretamente. Nova fase? (S/N)";
    drawText(message, -getStringBitmapLength(message)/2, 50);
}

void drawLandedOff() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Voce pousou fora do local de pouso. Nova fase? (S/N)";
    drawText(message, -getStringBitmapLength(message)/2, 50);
}

void drawExploded() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Voce explodiu. Nova fase? (S/N)";
    drawText(message, -getStringBitmapLength(message)/2, 50);
}

void drawFlewOutOfBounds() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Voce voou para longe e saiu de orbita. Nova fase? (S/N)";
    drawText(message, -getStringBitmapLength(message)/2, 0);
}
