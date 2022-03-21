//中点圆算法 MidPointCircle
#include <GL/glut.h>
#include <math.h>

typedef struct {
	float x, y;
}point;

int CirclePoint(int x1, int y1, int x, int y,int num, point pixels[]) {
	pixels[num].x = x1+x;
	pixels[num].y = y1+y;
	num++;
	pixels[num].x = x1 + y;
	pixels[num].y = y1 + x;
	num++;
	pixels[num].x = x1  - x;
	pixels[num].y = y1 + y;
	num++;
	pixels[num].x = x1  - y;
	pixels[num].y = y1 + x;
	num++;;
	pixels[num].x = x1 - x;
	pixels[num].y = y1 - y;
	num++;
	pixels[num].x = x1 - y;
	pixels[num].y = y1 - x;
	num++;
	pixels[num].x = x1 + x;
	pixels[num].y = y1 - y;
	num++;
	pixels[num].x = x1 + y;
	pixels[num].y = y1 - x;
	num++;

	return num;
}

int MidPointCircle(int x1, int y1, int r, point pixels[])
{
	int num=0;
	int x = 0;
	int y = r;
	int d = 1 - r;
	num = CirclePoint(x1, y1, x, y, num, pixels);
	while (x < y) {
		if (d < 0)
			d += 2 * x + 3;
		else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		num = CirclePoint(x1, y1, x, y, num, pixels);
	}

	return num;
}

void drawLine(int x1, int y1, int r)
{
	point pixels[10000];
	int num=0;
	int i;
	num = MidPointCircle(x1, y1, r, pixels);
	glBegin(GL_POINTS);
	for (i = 0; i < num; i++)
		glVertex2f(pixels[i].x, pixels[i].y);   //表示一个空间顶点
	glEnd();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLine(0,0,50);
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
	glutCreateWindow("MidPointCircle");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}