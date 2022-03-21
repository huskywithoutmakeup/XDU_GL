#include<GL/glut.h>
#include<string>
#include<iostream>

using namespace std;

typedef struct {
    float x, y, z;
}Point;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void DrawBezier3D(int n, Point P[])
{
    Point p;
    double t, deltat, t2, t3, et, et2, et3;
    int i;
    deltat = 1.0 / (n - 1);

    glBegin(GL_LINE_STRIP);
    for (i = 0; i < 100; i++)
    {
        t = i * deltat;
        et = 1 - t;
        t2 = t * t;
        et2 = et * et;
        t3 = t * t2;
        et3 = et * et2;
        p.x = et3 * P[0].x + 3 * t * et2 * P[1].x + 3 * t2 * et * P[2].x + t3 * P[3].x;
        p.y = et3 * P[0].y + 3 * t * et2 * P[1].y + 3 * t2 * et * P[2].y + t3 * P[3].y;
        p.z = et3 * P[0].z + 3 * t * et2 * P[1].z + 3 * t2 * et * P[2].z + t3 * P[3].z;

        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
    //glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    for (i = 0; i < 4; i++)
    {
        glVertex2d(P[i].x, P[i].y);
    }
    glEnd();
}

void DrawB3D(int n, Point P[])
{
    Point p;
    double t, deltat, t2, t3, et, et2, et3;
    int i;
    deltat = 1.0 / (n - 1);
    glBegin(GL_LINE_STRIP);
    for (i = 0; i < 100; i++)
    {
        t = i * deltat;
        et = 1 - t;
        t2 = t * t;
        et2 = et * et;
        t3 = t * t2;
        et3 = et * et2;
        p.x = et3 * P[0].x / 6 + (3 * t3 - 6 * t2 + 4) * P[1].x / 6 + (-3 * t3 + 3 * t2 + 3 * t + 1) * P[2].x / 6 + t3 * P[3].x / 6;
        p.y = et3 * P[0].y / 6 + (3 * t3 - 6 * t2 + 4) * P[1].y / 6 + (-3 * t3 + 3 * t2 + 3 * t + 1) * P[2].y / 6 + t3 * P[3].x / 6;
        p.z = et3 * P[0].z / 6 + (3 * t3 - 6 * t2 + 4) * P[1].z / 6 + (-3 * t3 + 3 * t2 + 3 * t + 1) * P[2].z / 6 + t3 * P[3].z / 6;
   
        glVertex3f(p.x, p.y, p.z);
    }
    cout << "" << endl;
    glEnd();
    //glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(0, 0, 1);
    for (i = 0; i < 4; i++)
    {
        glVertex2d(P[i].x, P[i].y);
    }

    glEnd();
}


void RenderScence()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Point P[4] = { {0,0,0},{1,1,1},{2,-1,-1},{3,0,0} };
    DrawBezier3D(100, P);
    DrawB3D(100, P);
    glFlush();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLfloat aspectRatio;
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h)
        glOrtho(-5, 5, -5 / aspectRatio, 5 / aspectRatio, 1.0, -1.0);
    else
        glOrtho(-5 * aspectRatio, 5 * aspectRatio, -5, 5, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Draw Bezier and B");

    init();
    glutDisplayFunc(RenderScence);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();

    return 0;
}
