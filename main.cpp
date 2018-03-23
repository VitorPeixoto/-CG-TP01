#include <SOIL/SOIL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>

#include "include/Spaceship.h"
#include "include/Map.h"

using namespace std;

#define R 0
#define G 1
#define B 2

#define X 0
#define Y 1
#define Z 2

#define MULTIPLIER 0.5
#define FPS_CONST 0.017*MULTIPLIER

bool* keyStates = new bool[127];
bool* specialKeyStates = new bool[127];

bool isEngineOn = false;

int windowWidth,
    windowHeight;

double oWidth, oHeight;

Spaceship s(0.0, 0.0, 26.0, 40.0, 20.0);
Map m;
double angle = 0.0;

Vector3d movement(0.0, 0.0, 0.0);
double gravity = -9.8;
Vector3d gravityVector(0.0, gravity*FPS_CONST, 0.0);

void drawSpaceship(void) {
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
        glTranslated(s.getX(), s.getY(), 0.0);
        //cout << s.getX() << "   " << s.getY() << endl;
        int currentIndex = s.getFireTextureIndex();
        int steps = s.getMaxFireTextureIndex()+1;

        glRotated(angle, 0.0, 0.0, 1.0);

        if(isEngineOn) {
            glBindTexture(GL_TEXTURE_2D, s.getFireTextureId());
            glBegin(GL_TRIANGLE_FAN);
                glTexCoord2f(currentIndex*(1.0/steps), 0);     glVertex2d(-5, -10);
                glTexCoord2f((currentIndex+1)*(1.0/steps), 0); glVertex2d( 5, -10);
                glTexCoord2f((currentIndex+1)*(1.0/steps), 1); glVertex2d( 5, -25);
                glTexCoord2f(currentIndex*(1.0/steps), 1);     glVertex2d(-5, -25);
            glEnd();
        }

        glBindTexture(GL_TEXTURE_2D, s.getTextureId());
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0, 0); glVertex2d(-s.getWidth()/2,  s.getHeight()/2);
            glTexCoord2f(1, 0); glVertex2d( s.getWidth()/2,  s.getHeight()/2);
            glTexCoord2f(1, 1); glVertex2d( s.getWidth()/2, -s.getHeight()/2);
            glTexCoord2f(0, 1); glVertex2d(-s.getWidth()/2, -s.getHeight()/2);
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}


void drawScene(void) {
    // Limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
    // possamos desenhar
    glClear(GL_COLOR_BUFFER_BIT);
        drawSpaceship();
        m.drawMap();
    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
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

    if (fireTexture == 0 || spaceshipTexture == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
        exit(-1);
    }

    s.setTextures(spaceshipTexture, fireTexture, 15);
    m.generateRandom(1000 * (double)windowWidth/windowHeight, 1000);

    // cor para limpar a tela
    glClearColor(1, 1, 1, 0); // branco
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Callback de redimensionamento
void resizeScreen(int w, int h) {
    double aspectRatio = (double)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    oWidth  = 500 * aspectRatio;
    oHeight = 500;

    glOrtho(-oWidth, oWidth, -oHeight, oHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyDown(unsigned char key, int x, int y) {
    keyStates[key] = true;

    if(key == 27) exit(0); //ESC
}

void specialKeyDown(int key, int x, int y) {
    specialKeyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
    if(key == 'w') {
    //    movement *= 0.0;
        isEngineOn = false;
    }
}

void specialKeyUp(int key, int x, int y) {
    specialKeyStates[key] = false;
}

void keyboardHandle() {
    if(keyStates['w']) {
        double sAngle = 90 + angle;
        sAngle *= M_PI/180;

        movement[X] += s.getSpeed() * cos(sAngle) * FPS_CONST;
        movement[Y] += s.getSpeed() * sin(sAngle) * FPS_CONST;
        isEngineOn = true;
    }
    if(keyStates['a']) {
        angle -= 1.0;
    }
    if(keyStates['d']) {
        angle += 1.0;
    }

    movement += gravityVector;

    s.moveSpaceship(movement);
    glutPostRedisplay();
}

void atualiza(int time) {
    keyboardHandle();
    glutTimerFunc(time, atualiza, time);
    s.incrementTextureId();
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
    glutCreateWindow("Title");

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
