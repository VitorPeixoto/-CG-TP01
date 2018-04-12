#include <SOIL/SOIL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <random>

#include "ScreenController.h"
#include "LandingSite.h"
#include "include/Spaceship.h"
#include "TextureLoader.h"
#include "include/Map.h"

using namespace std;

#define R 0
#define G 1
#define B 2

#define X 0
#define Y 1
#define Z 2

#define KEY_ESC 27
#define MULTIPLIER 0.5
#define FPS_CONST 0.017*MULTIPLIER
#define HUD_MARGIN 20
#define BG_MOVEMENT_DELAY 25

const double landingSpeedThreshold = 4.0;

bool* keyStates = new bool[127];
bool* specialKeyStates = new bool[127];
bool isPaused = false, isExiting = false, isRestarting = false, landedOnSpot = false, landedOff = false, gameEnded = false, flewOutOfBounds = false;
bool isOnMenu = true, isOnHelp = false, isOnCredits = false;
bool isHorizontallyLocked = false;

int windowWidth,
    windowHeight;

int backgroundTextureId;

double orthoHalfWidth, orthoHalfHeight;
double horizontallyLockedAt = 0.0;

Spaceship s(0.0, 0.0, 39.0, 60.0, 20.0);
LandingSite l(0.0, 0.0, 90.0, 30.0);
Map m;
TextureLoader textureLoader;

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 11);

Vector3d movement(0.0, 0.0, 0.0);
double gravity = -9.8;
Vector3d gravityVector(0.0, gravity*FPS_CONST, 0.0);

void drawHUD() {
    glColor3f(1.0, 1.0, 1.0);

    char *message = (char*)"Altura:";
    drawText(message, -orthoHalfWidth+HUD_MARGIN, orthoHalfHeight-20);

    message = (char*)std::to_string((int)s.getY()).c_str();
    drawText(message, -orthoHalfWidth+HUD_MARGIN+150, orthoHalfHeight-20);

    message = (char*)"Velocidade:";
    drawText(message, -orthoHalfWidth+HUD_MARGIN, orthoHalfHeight-40);

    message = (char*)std::to_string((int)movement.getNorm()).c_str();
    drawText(message, -orthoHalfWidth+HUD_MARGIN+150, orthoHalfHeight-40);

    message = (char*)"Aceleracao:";
    drawText(message, -orthoHalfWidth+HUD_MARGIN, orthoHalfHeight-60);

    message = (char*)std::to_string((int)abs(gravity - (s.isEngineOn() ? s.getSpeed() : 0))).c_str();
    drawText(message, -orthoHalfWidth+HUD_MARGIN+150, orthoHalfHeight-60);

    message = (char*)"Combustivel:";
    drawText(message, -orthoHalfWidth+HUD_MARGIN, orthoHalfHeight-80);

    message = (char*)(std::to_string((int)s.getFuel())+" L").c_str();
    drawText(message, -orthoHalfWidth+HUD_MARGIN+150, orthoHalfHeight-80);

    /*message = (char*)"Distancia:";
    drawText(message, -orthoHalfWidth+HUD_MARGIN, orthoHalfHeight-100);

    message = (char*)std::to_string(abs(s.getX() - l.getX())).c_str();
    drawText(message, -orthoHalfWidth+HUD_MARGIN+150, orthoHalfHeight-100);*/

    double directiveArrowAngle = atan2(-s.getY() + l.getY(), -s.getX() + l.getX());
    double magnitude = (sqrt(((-s.getX() + l.getX()) * (-s.getX() + l.getX())) + ((-s.getY() + l.getY()) * (-s.getY() + l.getY()))) + 60) / 30;

    glBegin(GL_LINES);
        glVertex3f(0.0, orthoHalfHeight, 0.0);
        glVertex3f(0.0 + cos(directiveArrowAngle)*magnitude, orthoHalfHeight, 0);
    glEnd();
}

void drawBackground() {
   glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, backgroundTextureId);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0); glVertex2d(-orthoHalfWidth,  orthoHalfHeight);
        glTexCoord2f(1, 0); glVertex2d( orthoHalfWidth,  orthoHalfHeight);
        glTexCoord2f(1, 1); glVertex2d( orthoHalfWidth, -orthoHalfHeight);
        glTexCoord2f(0, 1); glVertex2d(-orthoHalfWidth, -orthoHalfHeight);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
            if(!isHorizontallyLocked)
                glTranslated(-s.getX()/BG_MOVEMENT_DELAY, -s.getY()/BG_MOVEMENT_DELAY, 0.0);
            else
                glTranslated(-horizontallyLockedAt/BG_MOVEMENT_DELAY, -s.getY()/BG_MOVEMENT_DELAY, 0.0);

            drawBackground();
        glPopMatrix();
        glPushMatrix();
            if(!isHorizontallyLocked)
                glTranslated(-s.getX(), -s.getY(), 0.0);
            else
                glTranslated(-horizontallyLockedAt, -s.getY(), 0.0);

            m.drawMap();
            l.drawSite();
        glPopMatrix();
        s.drawSpaceship(isHorizontallyLocked, horizontallyLockedAt);
        if(isRestarting) drawRestartingConfirmation();
        if(isExiting)    drawExitingConfirmation();
        if(isPaused)     drawPaused();

        if(s.hasExploded() && (landedOff || landedOnSpot))   drawExploded();
        else if(landedOff)       drawLandedOff();
        else if(landedOnSpot)    drawLandedOn();
        else if(flewOutOfBounds) drawFlewOutOfBounds();
        drawHUD();
    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}

void verifyLock() {
    if(!(s.getX() > m.getLeft() + orthoHalfWidth)) {
        horizontallyLockedAt = -orthoHalfWidth*3;
        isHorizontallyLocked = true;
    }
    else if(!(s.getX() < m.getRight() - orthoHalfWidth)) {
        horizontallyLockedAt = orthoHalfWidth*3;
        isHorizontallyLocked = true;
    }
    else {
        isHorizontallyLocked = false;
    }
}

void restart() {
    s.randomLocation(orthoHalfWidth*2*4, orthoHalfHeight*2);
    verifyLock();

    m.generateRandom(orthoHalfWidth*2*4, orthoHalfHeight*2);
    Vector3d v = m.getRandomPlane();
    l.setX(v.getX());
    l.setY(v.getY());

    gravity = -distribution(generator);

    gravityVector = Vector3d(0.0, gravity*FPS_CONST, 0.0);

    //cout << "angle: " << abs(asin(gravity/s.getSpeed()))*180/M_PI << endl;
    //cout << "Fmx: "   << cos(abs(asin(gravity/s.getSpeed())))*20  << endl;

    double t = (abs(s.getX() - l.getX())*0.7)/(cos(abs(asin(gravity*1.8/s.getSpeed())))*s.getSpeed());
    double fuel = 30+t*0.15;
    s.setFuel(fuel);

    if(landedOnSpot && !s.hasExploded()) {
        textureLoader.randomizeTexture();
        s.setTextures(textureLoader.getSpaceshipTexture(), textureLoader.getFireTexture(), textureLoader.getExplosionTexture());
        m.setTexture(textureLoader.getMapTexture()->getId());
        l.setTexture(textureLoader.getLandingSiteTexture()->getId());
        backgroundTextureId = textureLoader.getBackgroundTexture()->getId();
    }

    isOnMenu = gameEnded = landedOnSpot = landedOff = flewOutOfBounds = false;
    s.setExploded(false);

    movement *= 0.0;
    isRestarting = false;
}

// Inicia algumas variáveis de estado
void inicializa(void) {
    //anti-aliasing
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    textureLoader.loadTextures();
    Texture* spaceshipTexture   = textureLoader.getSpaceshipTexture();
    Texture* fireTexture        = textureLoader.getFireTexture();
	Texture* mapTexture         = textureLoader.getMapTexture();
	Texture* landingSiteTexture = textureLoader.getLandingSiteTexture();
	Texture* explosionTexture   = textureLoader.getExplosionTexture();
	backgroundTextureId         = textureLoader.getBackgroundTexture()->getId();

    if (fireTexture->getId()      == 0 || spaceshipTexture->getId()    == 0 ||
        mapTexture->getId()       == 0 || landingSiteTexture->getId()  == 0 ||
        explosionTexture->getId() == 0 || backgroundTextureId          == 0) {
        exit(-1);
    }

    s.setTextures(spaceshipTexture, fireTexture, explosionTexture);
    m.setTexture(mapTexture->getId());
    l.setTexture(landingSiteTexture->getId());
    restart();

    // cor para limpar a tela
    glClearColor(0, 0, 0.0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Callback de redimensionamento
void resizeScreen(int w, int h) {
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

void keyboardHandle() {
    if(!gameEnded) {
        if(keyStates['w'] && s.hasFuel()) {
            double radAngle = s.getAngle();
            radAngle *= M_PI/180;

            movement[X] += s.getSpeed() * cos(radAngle) * FPS_CONST;
            movement[Y] += s.getSpeed() * sin(radAngle) * FPS_CONST;
            s.setEngineOn(true);
            s.decreaseFuel();
        }
        if(keyStates['a']) {
            s.incrementAngle();
        }
        if(keyStates['d']) {
            s.decrementAngle();
        }
        movement += gravityVector;
    }
    glutPostRedisplay();
}

void atualiza(int time) {
    glutTimerFunc(time, atualiza, time);
    if(isPaused || isRestarting || isExiting || gameEnded) {
        s.incrementExplosionTextureIndex();
        glutPostRedisplay();
        return;
    }
    keyboardHandle();
    if(s.collidesWith(m.getPolygons(), m.getX(), m.getY(), 0.0)) {
        if(movement.getNorm() > landingSpeedThreshold) {
            s.explode();
        }
        gameEnded = landedOff = true;
        movement *= 0.0;
    }
    if(s.collidesWith(l.getPolygons(), l.getX(), l.getY(), 0.0)) {
        if(movement.getNorm() > landingSpeedThreshold) {
            s.explode();
        }
        gameEnded = landedOnSpot = true;
        movement *= 0.0;
    }

    s.translate(movement);
    s.incrementFireTextureIndex();
    verifyLock();

    if(m.isOutOfBounds(s.getX(), s.getY())) {
        gameEnded = flewOutOfBounds = true;
    }
}


void keyDown(unsigned char key, int x, int y) {
    keyStates[key] = true;

    if(key == KEY_ESC) {
        isExiting = true;
        isRestarting = isPaused = landedOff = landedOnSpot = flewOutOfBounds = false;
        glutPostRedisplay();
    }
    if(isOnMenu) {
        if(key == 's') {
            glutDisplayFunc(drawScene);
            inicializa();
            glutTimerFunc(0, atualiza, 17);
        }
        if(key == 'h') {
            isOnHelp = true;
        }
        if(key == 'c') {
            isOnCredits = true;
        }
        if(key == 'b') {
            isOnHelp = isOnCredits = false;
        }
        glutPostRedisplay();
        return;
    }

    if(key == 'p' && !isExiting && !isRestarting) {
        isPaused = !isPaused;
    }
    if(key == 'r') {
        isRestarting = true;
        isExiting = isPaused = landedOff = landedOnSpot = flewOutOfBounds = false;
    }
}

void specialKeyDown(int key, int x, int y) {
    specialKeyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;

    if(key == 's') {
        if(isExiting) exit(0);
        if(isRestarting || landedOff || landedOnSpot || flewOutOfBounds) restart();
    }
    if(key == 'n') {
        if(isExiting)       isExiting       = isPaused = false;
        if(isRestarting)    isRestarting    = isPaused = false;
        if(flewOutOfBounds) flewOutOfBounds = isPaused = false;

        if(gameEnded)    landedOff = landedOnSpot = flewOutOfBounds = false;
        glutPostRedisplay();
    }

    if(isOnMenu) return;

    if(key == 'w') {
        s.setEngineOn(false);
    }
}

void specialKeyUp(int key, int x, int y) {
    specialKeyStates[key] = false;
}

// Rotina principal
int main(int argc, char **argv) {
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    windowWidth  = glutGet(GLUT_SCREEN_WIDTH);
    windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);

    // Abre a janela
    glutCreateWindow("[TP1] Moon Lander");
    glutFullScreen();

    // Registra callbacks para alguns eventos
    glutDisplayFunc(drawMenu);
    //glutDisplayFunc(drawScene);
    glutReshapeFunc(resizeScreen);

    // Keyboard up and down callbacks
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    // Special keyboard up and down callbacks
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);

    inicializaMenu();
    //inicializa();

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
