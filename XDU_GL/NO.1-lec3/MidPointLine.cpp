//中点线算法 MidPointLine
#include <GL/glut.h>
#include <math.h>

typedef struct {
	float x, y;
}point;

int MidPointLine(int x1, int y1, int xn, int yn, point pixels[])
{
	int num, x, y, dx, dy,d,d1,d2;
	x = x1; y = y1;
	dx = xn - x1;
	dy = yn - y1;
	num = 0;
	d = dx - 2*dy;
	d1 = 2*dx - 2*dy;
	d2 = -2*dy;

	while (x < xn) {
		if (d < 0) {
			pixels[num].x = x;
			pixels[num].y = y;
			x++;
			y++;
			d += d1;
			num++;
		}
		else {
			pixels[num].x = x;
			pixels[num].y = y;
			x++;
			d += d2;
			num++;
		}
	}
	pixels[num].x = x;
	pixels[num].y = y;

	return num;
}

void drawLine(int x1, int y1, int x2, int y2)
{
	point pixels[100];
	int num;
	int i;
	num = MidPointLine(x1, y1, x2, y2, pixels);
	glBegin(GL_POINTS);
	for (i = 0; i < num; i++)
		glVertex2f(pixels[i].x, pixels[i].y);   //表示一个空间顶点
	glEnd();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLine(-10, -10, 40, 80);
	glFlush();
}

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
		glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);   //将当前矩阵指定为模型视图矩阵
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(400, 400); //设置窗口大小
	glutInitWindowPosition(500, 200);   //设置窗口在屏幕上的位置 
	glutCreateWindow("MidPointLine");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}