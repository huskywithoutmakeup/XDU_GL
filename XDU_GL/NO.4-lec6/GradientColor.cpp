#include<GL/glut.h>

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void RenderScence()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-3.0, -3.0);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(3.0, 3.0);
	glEnd();

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
		glOrtho(-5.0, 5.0, -5.0 / aspectRatio, 5.0 / aspectRatio, 0.0, 1.0);
	else
		glOrtho(-5.0 * aspectRatio, 5.0 * aspectRatio, -5.0, 5.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("GradientColor");

	init();
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();

	return 0;
}