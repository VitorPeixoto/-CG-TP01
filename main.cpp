#include <SOIL/SOIL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <random>

#include "LandingSite.h"
#include "include/Spaceship.h"
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
bool isPaused = true, isExiting = false, isRestarting = false, landedOnSpot = false, landedOff = false, gameEnded = false, flewOutOfBounds = false;
bool isHorizontallyLocked = false;

int windowWidth,
    windowHeight;

int backgroundTextureId;

double orthoHalfWidth, orthoHalfHeight;
double horizontallyLockedAt = 0.0;

Spaceship s(0.0, 0.0, 26.0, 40.0, 20.0);
LandingSite l(0.0, 0.0, 90.0, 30.0);
Map m;

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1, 11);

Vector3d movement(0.0, 0.0, 0.0);
double gravity = -9.8;
Vector3d gravityVector(0.0, gravity*FPS_CONST, 0.0);

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

void drawExitingConfirmation() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Voce tem certeza que deseja sair do jogo?";
    drawText(message, -getStringBitmapLength(message)/2, 0);

    message = (char*)"S/N";
    drawText("S/N", -getStringBitmapLength(message)/2, -20);
}

void drawPaused() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Pausado";
    drawText(message, -getStringBitmapLength(message)/2, 0);
}

void drawLandedOn() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Parabens, voce pousou corretamente. Nova fase? (S/N)";
    drawText(message, -getStringBitmapLength(message)/2, 0);
}

void drawLandedOff() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Voce pousou fora do local de pouso. Nova fase? (S/N)";
    drawText(message, -getStringBitmapLength(message)/2, 0);
}

void drawExploded() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Voce explodiu. Nova fase? (S/N)";
    drawText(message, -getStringBitmapLength(message)/2, 0);
}

void drawFlewOutOfBounds() {
    glColor3f(1.0, 1.0, 1.0);
    char *message = (char*)"Voce voou para longe e saiu de orbita. Nova fase? (S/N)";
    drawText(message, -getStringBitmapLength(message)/2, 0);
}

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

// Inicia algumas variáveis de estado
void inicializa(void) {
    //anti-aliasing
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    int spaceshipTexture =  SOIL_load_OGL_texture(
        "src/images/spaceship.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);

    int fireTexture = SOIL_load_OGL_texture(
        "src/images/firesprite.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);

	int mapTexture = SOIL_load_OGL_texture(
        "src/images/mountain2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);

	int landingSiteTexture = SOIL_load_OGL_texture(
        "src/images/LandingSite.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);

	int explosionTexture = SOIL_load_OGL_texture(
        "src/images/Explosion.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);

	backgroundTextureId = SOIL_load_OGL_texture(
        "src/images/Coutinho.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        0
	);

    if (fireTexture == 0 || spaceshipTexture == 0 || mapTexture == 0 || landingSiteTexture == 0 || explosionTexture == 0 || backgroundTextureId == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
        exit(-1);
    }

    s.setTextures(spaceshipTexture, fireTexture, 15, explosionTexture, 5);
    m.setTexture(mapTexture);
    l.setTexture(landingSiteTexture);

    // cor para limpar a tela
    glClearColor(0, 0, 0.0, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

    gameEnded = landedOnSpot = landedOff = flewOutOfBounds = false;
    s.setExploded(false);

    movement *= 0.0;
    isRestarting = false;
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
    //glOrtho(-1500, 1500, -orthoHalfHeight, orthoHalfHeight, -1, 1);
    restart();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyDown(unsigned char key, int x, int y) {
    keyStates[key] = true;

    if(key == 'p' && !isExiting && !isRestarting) {
        isPaused = !isPaused;
        //glViewport(0, 0, w, h);
        /*glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //orthoHalfWidth  = 500 * aspectRatio;
        //orthoHalfHeight = 500;
        glOrtho(-orthoHalfWidth/1.3, orthoHalfWidth/1.3, -orthoHalfHeight/1.3, orthoHalfHeight/1.3, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();*/
    }
    if(key == 'r') {
        isRestarting = true;
        isExiting = isPaused = landedOff = landedOnSpot = flewOutOfBounds = false;
    }

    if(key == KEY_ESC) {
        isExiting = true;
        isRestarting = isPaused = landedOff = landedOnSpot = flewOutOfBounds = false;
    }
}

void specialKeyDown(int key, int x, int y) {
    specialKeyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
    if(key == 'w') {
        s.setEngineOn(false);
    }
    if(key == 's') {
        if(isExiting) exit(0);
        if(isRestarting || landedOff || landedOnSpot || flewOutOfBounds) restart();
    }
    if(key == 'n') {
        if(isExiting)       isExiting       = isPaused = false;
        if(isRestarting)    isRestarting    = isPaused = false;
        if(flewOutOfBounds) flewOutOfBounds = isPaused = false;

        if(gameEnded)    landedOff = landedOnSpot = flewOutOfBounds = false;
    }
}

void specialKeyUp(int key, int x, int y) {
    specialKeyStates[key] = false;
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
    glutCreateWindow("Lander");
    glutFullScreen();

    // Registra callbacks para alguns eventos
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resizeScreen);

    // Keyboard up and down callbacks
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    // Special keyboard up and down callbacks
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);

    inicializa();

    glutTimerFunc(0, atualiza, 17);

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
