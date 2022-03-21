#include <GL/glut.h>

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// 初始矩形
	glColor3f(1.0, 0.0, 0.0);
	glRectf(-10.0, 10.0 ,-30.0,  30.0);
	// 对称线 y = x + 5
	glBegin(GL_LINE_STRIP);
	    glColor3f(0.0, 0.0, 1.0);
		glVertex2f(-50, -45);
	    glVertex2f(45,50);
	glEnd();

	glTranslatef(0, 5, 0);
	glPushMatrix();
	glRotated(45, 0, 0, 1);
	glPushMatrix();
	glScaled(1, -1, 1);
	glPushMatrix();
	glRotated(-45, 0, 0, 1);
	glPushMatrix();
	glTranslated(0, -5, 0);
	glPushMatrix();

	glColor3f(1.0, 0.0, 0.0);
	glRectf(-10.0, 10.0, -30.0, 30.0);

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

	aspectRatio = 1.0 * (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-50.0, 50.0, -50.0 / aspectRatio, 50.0 / aspectRatio, -1.0, 1.0);
	else
		glOrtho(-50.0 * aspectRatio, 50.0 * aspectRatio, -50.0, 50.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("reflection");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}
