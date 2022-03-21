#include <GL/glut.h>

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);   //将当前矩阵指定为投影矩阵
	glLoadIdentity();                             //把矩阵设为单位矩阵

	aspectRatio = 1.0f * (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-200.0, 200.0, -200.0 / aspectRatio, 200.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-200.0 * aspectRatio, 200.0 * aspectRatio, -200.0, 200.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);   //将当前矩阵指定为模型视图矩阵
	glLoadIdentity();
}

void DrawMyObjects()
{
	//画点
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-100.0, 120.0);
	glVertex2f(-95.0, 110.0);
	glVertex2f(-80.0, 120.0);
	glVertex2f(-85.0, 110.0);
	glVertex2f(-75.0, 130.0);
	glEnd();

	//画线段
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-110.0, 80.0);
	glVertex2f(-70.0, 70.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-110.0, 90.0);
	glVertex2f(-80.0, 60.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-95.0, 92.0);
	glVertex2f(-70.0, 82.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-90.0, 95.0);
	glVertex2f(-115.0, 80.0);
	glEnd();

	//画开折线
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-30.0, 90.0);
	glVertex2f(20.0, 60.0);
	glVertex2f(30.0, 80.0);
	glVertex2f(-25.0, 65.0);
	glEnd();

	//画闭折线
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(70.0, 70.0);
	glVertex2f(80.0, 80.0);
	glVertex2f(90.0, 65.0);
	glVertex2f(105.0, 75.0);
	glVertex2f(115.0, 60.0);
	glVertex2f(75.0, 60.0);
	glEnd();

	//画填充多边形
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-77.0, 14.0);
	glVertex2f(-70.0, 30.0);
	glVertex2f(-105.0, 26.0);
	glVertex2f(-110.0, 16.0);
	glVertex2f(-108.0, 8.0);
	glEnd();

	//画四边形
	glBegin(GL_QUADS);
	glColor3f(0.7, 0.5, 0.2);
	glVertex2f(-30.0, 30.0);
	glVertex2f(-35.0, 15.0);
	glVertex2f(-5.0, 12.0);
	glVertex2f(-5.0, 32.0);

	glColor3f(0.5, 0.3, 0.2);
	glVertex2f(12.0, 30.0);
	glVertex2f(10.0,0.0);
	glVertex2f(20.0, 0.0);
	glVertex2f(30.0, 35.0);
	glEnd();

	//画连接四边形
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.8, 1.0, 0.0);
	glVertex2f(90.0, 0.0);
	glVertex2f(88.0, 20.0);
	glVertex2f(105.0, 0.0);
	glColor3f(1.0, 8.0, 0.0);
	glVertex2f(105.0, 22.0);
	glVertex2f(114.0, 3.0);
	glColor3f(1.0, 0.8, 0.0);
	glVertex2f(110.0, 25.0);
	glVertex2f(120.0, 4.0);
	glColor3f(1.0, 0.8, 1.0);
	glVertex2f(119.0, 28.0);
	glEnd();

	//画三角形
	glBegin(GL_TRIANGLES);
	glColor3f(0.2, 0.5, 0.7);
	glVertex2f(-100.0, -70.0);
	glVertex2f(-100.0, -50.0);
	glVertex2f(-80.0, -70.0);	
	glColor3f(0.2, 0.7, 0.5);
	glVertex2f(-95.0, -45.0);
	glVertex2f(-75.0, -65.0);
	glVertex2f(-55.0, -45.0);
	glEnd();

	//画连续三角形
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-10.0, -50.0);
	glVertex2f(-10.0, -75.0);
	glColor3f(0.8, 0.8, 1.0);
	glVertex2f(10.0, -50.0);
	glColor3f(1.0, 0.8, 0.8);
	glVertex2f(15.0, -75.0);
	glColor3f(0.8, 1.0, 0.8);
	glVertex2f(20.0, -50.0);
	glVertex2f(23.0, -80.0);
	glEnd();

	//画扇形三角形
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(100.0, -60.0);
	glVertex2f(100.0, -30.0);
	glColor3f(0.8, 0.2, 0.5);
	glVertex2f(120.0, -40.5);
	glColor3f(0.2, 0.5, 0.8);
	glVertex2f(130.0, -70.5);
	glColor3f(0.8, 0.5, 0.2);
	glVertex2f(100.0, -90.0);
	glEnd();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	DrawMyObjects();
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("drawGeom");
	glClearColor(1.0, 1.0, 1.0, 1.0);


	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}
