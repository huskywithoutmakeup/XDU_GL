#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

int currentMode = 0;
int angle = 0;
const int ModeNums = 7;

void myKey( unsigned char key, int x, int y) //响应ASCII对应键，鼠标的当前x和y位置也被返回。
{
	switch(key)
	{
		case ' ': currentMode = (currentMode+1)%ModeNums;
			      glutPostRedisplay();
				  break;
		case 27:  exit(-1);
	}
}

void timerFunction(int id)
{
	angle  = (angle+3)%360;

	glutPostRedisplay();
	glutTimerFunc(33, timerFunction, 1);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch(currentMode)
	{
	    case 0: break;

		case 1: glPointSize(5);
				glBegin(GL_POINTS);
			    glColor3f(1.0,0.0,0.0);
				glVertex2f(-2.0, -3.0);
				glVertex2f(2.0, -3.0);
				glVertex2f(0.0, 3.0);
				glEnd();

				break;
		case 2: glBegin(GL_LINE_STRIP);
			    glColor3f(0.0,1.0,0.0);
				glVertex2f(-2.0, -3.0);
				glVertex2f(2.0, -3.0);
				glVertex2f(0.0, 3.0);
				glEnd();
			    break;

		case 3: glBegin(GL_TRIANGLES);
			    glColor3f(0.8, 0.3, 0.0);
				glVertex2f(-2.0, -3.0);
				glVertex2f(2.0, -3.0);
				glVertex2f(0.0, 3.0);
				glEnd();
				break;

		case 4: glPushMatrix();
			glTranslatef(0.5, 1.0, 0.5);
			glBegin(GL_TRIANGLES);
			glColor3f(0.8, 0.3, 0.0);
			glVertex2f(-2.0, -3.0);
			glVertex2f(2.0, -3.0);
			glVertex2f(0.0, 3.0);
			glEnd();
			glPopMatrix();
				break;

		case 5:glPushMatrix();
			glScalef(0.5, 0.5, 0.5);
			glBegin(GL_TRIANGLES);
			glColor3f(0.8, 0.3, 0.0);
			glVertex2f(-2.0, -3.0);
			glVertex2f(2.0, -3.0);
			glVertex2f(0.0, 3.0);
			glEnd();
			glPopMatrix();
			break;

		case 6:glPushMatrix();
			glRotatef(angle, 0.0, 0.0, 1.0);
			glBegin(GL_TRIANGLES);
			glColor3f(0.8, 0.3, 0.0);
			glVertex2f(-2.0, -3.0);
			glVertex2f(2.0, -3.0);
			glVertex2f(0.0, 3.0);
			glEnd();
			glPopMatrix();
			break;
	} //旋转部分更新详见 RotateDev
	glutSwapBuffers();
}

void ChangeSize(GLsizei w,GLsizei h)
{
	float ratio;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	ratio = 1.0*(float)w/(float)h;
	if(w<=h)
		gluOrtho2D(-10.0,10.0,-10.0/ratio,10.0/ratio);
	else
		gluOrtho2D(-10.0*ratio,10.0*ratio,-10.0,10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(500,200);
	glutInitWindowSize(400,400);
	glutCreateWindow("KeyboardFunc");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);  //为当前窗口设置键盘回调函数。
	glutTimerFunc(33, timerFunction, 1);    //注册定时器
	
	printf("Press space to continue,press escape to exit!\n");
	glutMainLoop();
}