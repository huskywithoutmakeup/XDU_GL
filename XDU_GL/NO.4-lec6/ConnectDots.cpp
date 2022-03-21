#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include<string.h>
#include<time.h>

#define MaxNumPts 64
float PointArray[MaxNumPts][2];
int NumPts = 0;

int mode = 0;
char num[2] = "3";
int sum = 0;

int WindowHeight;
int WindowWidth;

void CharDisplay(double x, double y, double z, char str[])//显示字符函数
{
	glRasterPos3d(x, y, z);
	for (unsigned int i = 0; i < strlen(str); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}

void removeFirstPoint() {
	int i;
	if (NumPts > 0) {

		NumPts--;
		for (i = 0; i < NumPts; i++) {
			PointArray[i][0] = PointArray[i + 1][0];
			PointArray[i][1] = PointArray[i + 1][1];
		}
	}
}

void removeAllPoint() {
		NumPts=0;
}

void removeLastPoint() {
	if (NumPts > 0) {
		NumPts--;
	}
}


void addNewPoint(float x, float y) {
	if (NumPts >= MaxNumPts) {
		removeFirstPoint();
	}
	PointArray[NumPts][0] = x;
	PointArray[NumPts][1] = y;
	NumPts++;
}

void myKeyboardFunc (unsigned char key, int x, int y)
{
	switch (key) {
	case '3':
	{
		strcpy_s(num, "3");
		mode = 1;
		sum = 3;
		glFlush();
		glutPostRedisplay();
		break;
	}

	case '4':
	{
		strcpy_s(num, "4");
		mode = 1;
		sum = 4;
		glFlush();
		glutPostRedisplay();

		break;
	}

	case '5':
	{
		strcpy_s(num, "5");
		mode = 1;
		sum = 5;
		glFlush();
		glutPostRedisplay();
		break;
	}

	case '6':
	{
		strcpy_s(num, "6");
		mode = 1;
		sum = 6;
		glFlush();
		glutPostRedisplay();
		break;
	}

	case '7':
	{
		strcpy_s(num, "7");
		mode = 1;
		sum = 7;
		glFlush();
		glutPostRedisplay();
		break;
	}

	case '8':
	{
		strcpy_s(num, "8");
		mode = 1;
		sum = 8;
		glFlush();
		glutPostRedisplay();
		break;
	}

	case '9':
	{
		strcpy_s(num, "9");
		mode = 1;
		sum = 9;
		glFlush();
		glutPostRedisplay();
		break;
	}
	case 's':
		mode = 2;
		glutPostRedisplay();
		break;
	case 'f':
		removeFirstPoint();
		glutPostRedisplay();
		break;
	case 'r':
		removeAllPoint();
		glutPostRedisplay();
		break;
	case 27:		
		exit(0);
		break;
	}
}

void myMouseFunc( int button, int state, int x, int y ) {
	if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN ) {
		float xPos = ((float)x)/((float)(WindowWidth-1));
		float yPos = ((float)y)/((float)(WindowHeight-1));

		yPos = 1.0f-yPos;			

		addNewPoint( xPos, yPos );
		glutPostRedisplay();
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		removeLastPoint();
		glutPostRedisplay();
	}
}

void title()
{
	glColor3f(0, 0, 0);
	char str[80] = " Enter the number of sides of the polygon";
	CharDisplay(0.03, 0.8, 0, str);
	char str1[20] = "Range:3-9";
	CharDisplay(0.35, 0.65, 0, str1);
	char str2[20] = "The input is :";
	CharDisplay(0.25, 0.5, 0, str2);
}

void setColor()
{
	double r = rand() % 256;
	double g = rand() % 256;
	double b = rand() % 256;

	glColor3d(r / 256, g / 256, b / 256);
}


void RenderScene(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	if (mode == 0)
	{
		title();
		glColor3f(0, 0, 0);
	}
	else if (mode == 1)
	{
		title();
		glColor3f(1, 0, 0);
		CharDisplay(0.65, 0.5, 0, num);
		glColor3f(0, 0, 1);
		char str[20] = "Press 'S' to start!";
		CharDisplay(0.3, 0.4, 0, str);
		glColor3f(1, 0, 1);
	}
	else if (mode == 2)
	{
		// 画填充
		glColor3f(1.0f, 0.0f, 0.8f);
		if (NumPts > 1) {
			int n = NumPts / sum;
			int counter = 0;
			for (i = 0; i < n; i++) {
				setColor();
				glBegin(GL_POLYGON);
				for (int j = 0; j < sum; j++)
				{
					glVertex2f(PointArray[counter][0], PointArray[counter][1]);
					counter++;
				}
				glEnd();
			}
		}

		// 画控制点
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		for (i = 0; i < NumPts; i++) {
			glVertex2f(PointArray[i][0], PointArray[i][1]);
		}
		glEnd();
	}
	glFlush();
}

void init() {
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

	// 设置点大小和线宽
	glPointSize(8);
	glLineWidth(5);

	glEnable(GL_POINT_SMOOTH);  //点抗锯齿
	glEnable(GL_LINE_SMOOTH);   //线抗锯齿
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// 选择特定的渲染，如渲染质量
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		
	glEnable(GL_BLEND);  //颜色混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ChangeSize(int w, int h)
{
	WindowHeight = (h>1) ? h : 2;
	WindowWidth = (w>1) ? w : 2;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB ); 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ConnectDots");
	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKeyboardFunc);
	glutMouseFunc(myMouseFunc);
	glutMainLoop();

	return 0;				
}
