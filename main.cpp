#include <GL/glew.h>
#include <GL/freeglut.h>

#define R 0
#define G 1
#define B 2

#define X 0
#define Y 1
#define Z 2

void desenhaCena(void)
{
    // Limpa a tela (com a cor definida por glClearColor(r,g,b)) para que
    // possamos desenhar
    glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POLYGON);

        glEnd();
    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}

// Inicia algumas variáveis de estado
void inicializa(void)
{
    //anti-aliasing
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // cor para limpar a tela
    glClearColor(1, 1, 1, 0); // branco
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// Callback de redimensionamento
void redimensiona(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50, 50, -50, 50, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Callback de evento de teclado
void teclado(unsigned char key, int x, int y)
{
    switch(key)
    {
        // Tecla ESC
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

// Rotina principal
int main(int argc, char **argv)
{
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a versão do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // Configuração inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);

    // Abre a janela
    glutCreateWindow("Title");

    // Registra callbacks para alguns eventos
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    inicializa();

    // Entra em loop e nunca sai
    glutMainLoop();
    return 0;
}
