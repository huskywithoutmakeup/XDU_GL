#include<GL/glut.h>
#include<iostream>

using namespace std;

int n;

typedef struct {
    float r, g, b;
}point;

point Color[9] = { {0.0,0.0,0.0},{1.0,1.0,1.0},{1.0,0.5,0.0},{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{0.0,1.0,1.0},{1.0,0.0,1.0},{1.0,1.0,0.0} };

void init()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
}

void DrawSquare(int n,float x1,float x2)
{
    for (int i = 0; i < 9; i++)
    {
        glColor3f(Color[i].r, Color[i].g, Color[i].b);
        glBegin(GL_QUADS);
        x1 += n ;
        x2 += n;
        glVertex2f(x1, 0.0);
        glVertex2f(x1, n);
        glVertex2f(x2, n);
        glVertex2f(x2, 0);
        glEnd();
        x1++;
        x2++;
    }
}

void RenderScence()
{
    glClear(GL_COLOR_BUFFER_BIT);
    DrawSquare(n,-5*n,-4*n);
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
        glOrtho(-30.0, 30.0, -30.0 / aspectRatio, 30.0 / aspectRatio, -1.0, 1.0);
    else
        glOrtho(-30.0 * aspectRatio, 30.0 * aspectRatio, -30.0, 30.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(500, 200);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Color 2");

    cout << "ÊäÈëÏñËØ´óÐ¡n" << endl;
    cin >> n;

    init();
    glutDisplayFunc(RenderScence);
    glutReshapeFunc(ChangeSize);
    glutMainLoop();

    return 0;
}
