//Разрабочик Шатунов Александр Вячеславович УТС/б-21-2о
#include "GL/freeglut.h"
#include <cmath>
#include <ctime>

float GineretСordenate()
{
    return round((2 * (float)rand() / RAND_MAX - 1) * 10) / 10;
}

char nap; //напровление
int h, //длинна змемйки
    Ri; //угол поворота головы (графика)

struct obj
{
    float x, 
          y;
} gren[93], Snake[289], apple;

void GineretApple()
{
    apple.x = GineretСordenate();
    apple.y = GineretСordenate();

    //дебаг спавна яблок "в теле" И за картой
    for (int i = 0; i <= h; i++)
    {
        if ((apple.x == round(Snake[i].x * 10) / 10) || (apple.x > 0.9) || (apple.x < -0.9))
            apple.x = GineretСordenate();

        if ((apple.y == round(Snake[i].y * 10) / 10) || (apple.y > 0.9) || (apple.y < -0.9))
            apple.y = GineretСordenate();
    }
}

void dravGreen(obj grass)
{
    glPushMatrix();
    glTranslatef(grass.x, grass.y, 0);
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
        glTranslatef(Snake[0].x + .1, Snake[0].y, 0);
        break;
    case 180:
        glTranslatef(Snake[0].x + .1, Snake[0].y + .1, 0);
        break;
    case 270:
        glTranslatef(Snake[0].x, Snake[0].y + .1, 0);
        break;
    default:
        glTranslatef(Snake[0].x, Snake[0].y, 0);
    }
    glRotatef(Ri, 0, 0, 1);

    glBegin(GL_QUADS);

    glColor3f(.08, 1, .07);
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

void DravBody(obj body)
{
    glPushMatrix();
    glTranslatef(body.x, body.y, 0);
    glBegin(GL_QUADS);

    glColor3f(.25, .95, .4);
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
    glTranslatef(apple.x, apple.y, 0);
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
        Snake[i].x = 0;
        Snake[i].y = 0;
    }
    for (int i = 0; i < 93; i++)
    {
        gren[i].x = GineretСordenate();
        gren[i].y = GineretСordenate();
    }
    GineretApple();
    h = 3;
    Ri = 0;
    nap = NULL;
}

void tik(int n)
{
    for (int i = h; i > 0; i--)
    {
        Snake[i].x = Snake[i - 1].x;
        Snake[i].y = Snake[i - 1].y;
    }

    //движение по напровлению
    switch (nap)
    {
    case 'w':
        Snake[0].y += .1;
        Ri = 0;
        break;
    case 's':
        Snake[0].y -= .1;
        Ri = 180;
        break;
    case 'd':
        Snake[0].x += .1;
        Ri = 270;
        break;
    case 'a':
        Snake[0].x -= .1;
        Ri = 90;
        break;
    }

    //подбор яблока и поевление нового
    if ((round(Snake[0].x * 10)/10 == apple.x) && (round(Snake[0].y * 10) / 10 == apple.y))
    {
        h++;
        GineretApple();
    }

    //смерти от стены
    if ((Snake[0].x >= 1) || (Snake[0].x <= -1.1) || (Snake[0].y >= 1) || (Snake[0].y <= -1.1)) Dead();

    //смерть от тела
    for (int i = 1; i <= h; i++)
        if ((Snake[0].x == Snake[i].x) && (Snake[0].y == Snake[i].y))
            if (nap != NULL)
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
    //рецтарт
    if (key == 114 || key == 234) Dead();

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

    for (int i = 0; i < 93; i++)
        dravGreen(gren[i]);

    for (int i = 1; i < h; i++)
        DravBody(Snake[i]);

    DravHead();

    DravApple();

    glutSwapBuffers(); // эта функция должна быть последний в renderScene
}