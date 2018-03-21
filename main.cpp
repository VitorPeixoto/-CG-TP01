#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "Spaceship.h"

using namespace std;

#define sin_45 0.7071

#define R 0
#define G 1
#define B 2

#define X 0
#define Y 1
#define Z 2

bool* keyStates = new bool[127];
bool* specialKeyStates = new bool[127];

int windowWidth,
    windowHeight;

Spaceship s(0.0, 0.0, 40.0, 40.0, 1.0);

Vector3d movement(0.0, 0.0, 0.0);

void drawSpaceship(void) {
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslated(s.getX(), s.getY(), 0.0);
        //cout << s.getX() << "   " << s.getY() << endl;
        glBegin(GL_TRIANGLE_FAN);
            glVertex2d(-s.getWidth()/2,  s.getHeight()/2);
            glVertex2d( s.getWidth()/2,  s.getHeight()/2);
            glVertex2d( s.getWidth()/2, -s.getHeight()/2);
            glVertex2d(-s.getWidth()/2, -s.getHeight()/2);
        glEnd();
    glPopMatrix();
}


void drawScene(void) {
    // Limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
    // possamos desenhar
    glClear(GL_COLOR_BUFFER_BIT);
        drawSpaceship();
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
    glOrtho(-50 * aspectRatio, 50 * aspectRatio, -50, 50, -1, 1);
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
    if(key == 'w' || key == 's') {
        movement[Y] = 0.0;
    }
    if(key == 'a' || key == 'd') {
        movement[X] = 0.0;
    }
}

void specialKeyUp(int key, int x, int y) {
    specialKeyStates[key] = false;
}

void keyboardHandle() {
    if(keyStates['w']) {
        movement[Y] += s.getSpeed();
    }
    if(keyStates['a']) {
        movement[X] -= s.getSpeed();
    }
    if(keyStates['s']) {
        movement[Y] -= s.getSpeed();
    }
    if(keyStates['d']) {
        movement[X] += s.getSpeed();
    }

    if(movement[X] && movement[Y])
        movement *= sin_45;

    s.moveSpaceship(movement);
    glutPostRedisplay();
}

void atualiza(int time) {
    movement *= 0.0;
    keyboardHandle();
    glutTimerFunc(time, atualiza, time);
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
