#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265

GLfloat win = 3.0f;
GLint milisec = 1000;
GLint segundos = 1;
GLint minutos = 1;
GLint horas = 1;

void RedimensionaJanela(GLsizei w, GLsizei h)
{
    // Especifica as dimens�es da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-win, win, -win, win);
}



void circulo(float raio){
    double val = PI/ 180.0;
    glBegin(GL_TRIANGLE_FAN);
        for(int i = 0; i <= 360; i++){
            glVertex2f(cos(i * val) * raio,sin(i * val) * raio);
        }
    glEnd();
}


void relogio(int arg){
    double val = PI/ 180.0;
    int pontosMinutos = 4;

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(1,1,1);
        for(double i = 0; i <= 360.0;  i = i + 6.0){
            if(pontosMinutos == 4){
                pontosMinutos = 0;
                glBegin(GL_LINES);
                    glVertex2f(cos(i * val),sin(i * val));
                    glVertex2f((cos(i * val) * 0.85) ,(sin(i * val) * 0.85) );
                glEnd();
            }else{
                glBegin(GL_LINES);
                    glVertex2f(cos(i * val),sin(i * val));
                    glVertex2f((cos(i * val) * 0.95) ,(sin(i * val) * 0.95) );
                glEnd();
                pontosMinutos++;
            }

        }

        //contadores de tempo
        if(segundos > 60){
            segundos = 1;
            minutos++;
        }
        if(minutos > 60){
            minutos = 1;
            horas++;
        }
        if(horas > 24){
            horas = 1;
        }

         glColor3f(1,1,0);
        //circulo central
        circulo(0.1);

        //horas
        glRotatef(((-1)*horas) * 30.0,0,0,1);
        glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f((cos(210 * val) * 0.7), (sin(210 * val) * 0.7) );
        glEnd();

        //minutos
        glRotatef(((-1)*minutos)* 6.0,0,0,1);
        glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f((cos(138 * val) * 0.8), (sin(138 * val) * 0.8) );
        glEnd();

        //segundos
        glRotatef(((-1)*segundos) * 6.0,0,0,1);
        glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f((cos(306 * val) * 0.95), (sin(306 * val) * 0.95) );
        glEnd();

        glFlush();
        segundos++;
        glutTimerFunc(milisec,relogio,0);

}

void animacao() {
    glutTimerFunc(0,relogio,0);
}

void desenhaRelogio(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-win,win,-win,win);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    animacao();
    glFlush();
}

int main(void){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,150);
    glutCreateWindow("Relógio");
    glutDisplayFunc(desenhaRelogio);
    glutReshapeFunc(RedimensionaJanela);
    glClearColor(0,0,0,0);
    glutMainLoop();
    return 0;
}
