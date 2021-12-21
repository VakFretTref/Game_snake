//Разрабочик Шатунов Александр Вячеславович УТС/б-21-2о
#include "GL/freeglut.h"
#include <cmath>
#include <ctime>

float GineretApple()
{
    return round((2 * (float)rand() / RAND_MAX - 1) * 10) / 10;
}
//трава на задний фон и затемнение фона
float x_apple = GineretApple(), 
      y_apple = GineretApple(),
      xt[289], yt[289]; //кардинаты тела
char nap; //напровление
int h, //длинна змемйки
    Ri; //угол поворота головы (графика)
bool Q = true;
struct GRE
{
    float x, 
          y;
} gre[82];

void dravGreen(GRE gre2)
{
    glPushMatrix();
    glTranslatef(gre2.x, gre2.y, 0);
    glBegin(GL_TRIANGLES);

    glColor3f(.3, .7, .2);
    glVertex2f(0.01, 0);
    glVertex2f(0.026, 0.06);
    glVertex2f(0.03, 0.0);

    glColor3f(.35, .75, .25);
    glVertex2f(0.03, 0);
    glVertex2f(0.056, 0.09);
    glVertex2f(0.061, 0.0);

    glColor3f(.315, .715, .215);
    glVertex2f(0.06, 0);
    glVertex2f(0.084, 0.08);
    glVertex2f(0.1, 0.0);

    glEnd();
    glPopMatrix();
}

void Fon()
{
    glPushMatrix();
    glBegin(GL_QUADS);

    glColor3f(.4, .8, .3);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);

    glEnd();
    glPopMatrix();
}

void DravHead()
{
    glPushMatrix();

    //поворот говолы (чисто графика)
    switch (Ri)
    {
    case 90:
        glTranslatef(xt[0] + .1, yt[0], 0);
        break;
    case 180:
        glTranslatef(xt[0] + .1, yt[0] + .1, 0);
        break;
    case 270:
        glTranslatef(xt[0], yt[0] + .1, 0);
        break;
    default:
        glTranslatef(xt[0], yt[0], 0);
    }
    glRotatef(Ri, 0, 0, 1);

    glBegin(GL_QUADS);

    glColor3f(.09, 1, .09);
    glVertex2f(0, 0);
    glVertex2f(0, .1);
    glVertex2f(.1, .1);
    glVertex2f(.1, 0);

    glColor3f(.1, .1, .1);
    glVertex2f(.0125, .0625);
    glVertex2f(.0375, .0625);
    glVertex2f(.0375, .0875);
    glVertex2f(.0125, .0875);

    glVertex2f(.0625, .0625);
    glVertex2f(.0875, .0625);
    glVertex2f(.0875, .0875);
    glVertex2f(.0625, .0875);

    glEnd();
    glPopMatrix();
}

void DravBady(float xT, float yT)
{
    glPushMatrix();
    glTranslatef(xT, yT, 0);
    glBegin(GL_QUADS);

    glColor3f(.2, .9, .4);
    glVertex2f(.01, .01);
    glVertex2f(.01, .09);
    glVertex2f(.09, .09);
    glVertex2f(.09, .01);

    glEnd();
    glPopMatrix();
}

void DravApple()
{
    glPushMatrix();
    glTranslatef(x_apple, y_apple, 0);
    glBegin(GL_QUADS);

    glColor3f(1, .1, .1);
    glVertex2f(.014, .014);
    glVertex2f(.014, .056);
    glVertex2f(.086, .056);
    glVertex2f(.086, .014);

    glVertex2f(.028, .0);
    glVertex2f(.028, .071);
    glVertex2f(.072, .071);
    glVertex2f(.072, .0);

    glColor3f(.2, .2, .2);
    glVertex2f(.042, .056);
    glVertex2f(.042, .085);
    glVertex2f(.057, .085);
    glVertex2f(.057, .056);

    glVertex2f(.056, .085);
    glVertex2f(.056, .099);
    glVertex2f(.072, .099);
    glVertex2f(.072, .085);

    //блик яблока
    glColor3f(.8, .8, .8);
    glVertex2f(.056, .019);
    glVertex2f(.070, .019);
    glVertex2f(.070, .033);
    glVertex2f(.056, .033);

    glEnd();
    glPopMatrix();
}

void Dead()
{
    for (int i = h; i >= 0; i--)
    {
        xt[i] = 0;
        yt[i] = 0;
    }
    if (Q)
    {
        for (int i = 0; i < 82; i++)
        {
            gre[i].x = GineretApple();
            gre[i].y = GineretApple();
        }
        Q = false;
    }
    h = 3;
    Ri = 0;
    nap = NULL;
}

void tik(int n)
{
    for (int i = h; i > 0; i--)
    {
        xt[i] = xt[i - 1];
        yt[i] = yt[i - 1];
    }

    //движение по напровлению
    switch (nap)
    {
    case 'w':
        yt[0] += .1;
        Ri = 0;
        break;
    case 's':
        yt[0] -= .1;
        Ri = 180;
        break;
    case 'd':
        xt[0] += .1;
        Ri = 270;
        break;
    case 'a':
        xt[0] -= .1;
        Ri = 90;
        break;
    }

    //подбор яблока и поевление нового
    if ((round(xt[0] * 10)/10 == x_apple) && (round(yt[0] * 10) / 10 == y_apple))
    {
        h++;
        x_apple = GineretApple();
        y_apple = GineretApple();

        //дебаг спавна яблок "в теле" И за картой
        for (int i = 0; i <= h; i++)
        {
            if ((x_apple == xt[i]) || (x_apple >= 1) || (x_apple <= -1))
                x_apple = GineretApple();

            if ((y_apple == yt[i]) || (y_apple >= 1) || (y_apple <= -1)) 
                y_apple = GineretApple();
        }
    }

    //смерти от стены
    if ((xt[0] >= 1) || (xt[0] <= -1.1) || (yt[0] >= 1) || (yt[0] <= -1.1))
    {
        Dead();
        Q = true;
    }

    /*  
    // Альтернотивные правила _ открытое поле
    if (xt[0] >= 1) xt[0] = (float)-1;
    if (xt[0] <= -1.1) xt[0] = (float)1;
    if (yt[0] >= 1) yt[0] = (float)-1;
    if (yt[0] <= -1.1) yt[0] = (float)1;
    */

    //смерть от тела
    for (int i = 1; i <= h; i++)
        if ((xt[0] == xt[i]) && (yt[0] == yt[i]))
            Dead();
    glutPostRedisplay();
    glutTimerFunc(100, tik, 0);
}

void renderScene(void);

void processKeys(unsigned char key, int x, int y)
{
    //Логика упровления
    if ((key == 100 || key == 226) && (nap != 'a')) nap = 'd';
    if ((key == 97 || key == 244) && (nap != 'd')) nap = 'a';
    if ((key == 119 || key == 246) && (nap != 's')) nap = 'w';
    if ((key == 115 || key == 251) && (nap != 'w')) nap = 's';
    
    if (key == 114 || key == 234)
    {
        Q = true;
        Dead();//рецтарт
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    srand(time(0));
    Dead();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(605, 200);
    glutInitWindowSize(650, 650);
    glutCreateWindow("Змейка");
    glutDisplayFunc(renderScene);
    glutTimerFunc(100, tik, 0);
    glutKeyboardFunc(processKeys);
    glutMainLoop();
    return 0;
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // эта функция должна быть первой в renderScene

    Fon();
    for (int i = 0; i < 82; i++)
        dravGreen(gre[i]);
    for (int i = 1; i < h; i++)
        DravBady(xt[i], yt[i]);
    DravHead();
    DravApple();
    

    glutSwapBuffers(); // эта функция должна быть последний в renderScene
}