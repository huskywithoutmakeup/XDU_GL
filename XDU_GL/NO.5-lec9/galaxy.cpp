#include<GL/glut.h>
#include <math.h>

#define pi 3.14

GLfloat angle_ES = 0.0f;      //地球相对于太阳的旋转角度
GLfloat speed_ES = 0.005f;    //地球绕日旋转速度
GLfloat angle_ME = 0.0f;      //月亮相对于地球的旋转角度
GLfloat speed_ME = 0.015f;    //月亮绕地旋转速度
GLfloat angle_self = 0.0f;    //自转角度
GLfloat speed_self = 1.0f;    //自转速度
//这里我们假设日-地-月 自转速度的倍率 为 1-5-3
GLfloat distance_ES = 2.5f; //地球中心离太阳的距离
GLfloat distance_ME = 0.5f; //月亮中心离地球的距离

GLfloat earthPosX = 2.5f;  //地球的坐标
GLfloat earthPosZ = 0.0f;
GLfloat monthPosX = 3.0f;  //月亮的坐标
GLfloat monthPosZ = 0.0f;


GLfloat n = 6000;//构成轨道点数

void init()
{
	GLfloat whiteLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(30, 1.0f, 1.0f, 1.0f);


	//SUN
	glPushMatrix();
	glRotatef(angle_self, 0.0f, 1.0f, 0.0f); 	//自转
	glColor3f(1.0f, 0.0f, 0.0f);
	glDisable(GL_LIGHTING);
	glutWireSphere(0.6, 30, 30);
	glPopMatrix();

	//EARTH
	glPushMatrix();
	glTranslatef(earthPosX, 0.0f, earthPosZ);       //地球位置
	glRotatef(5 * angle_self, 0.0f, 1.0f, 0.0f);	//自转
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glutWireSphere(0.3, 30, 30);
	glPopMatrix();

	//MOON
	glPushMatrix();
	glTranslatef(monthPosX, 0.0f, monthPosZ);       //月球位置
	glRotatef(3 * angle_self, 0.0f, 1.0f, 0.0f);	//自转
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glutWireSphere(0.15, 20, 20);
	glPopMatrix();

	//SUN-EARTH LINE
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(distance_ES * cos(2 * pi * i / n), 0.0f, distance_ES * sin(2 * pi * i / n));
	}
	glEnd();
	glFlush();
	glPopMatrix();

	//EARTH-MOON LINE
	glPushMatrix();
	glTranslatef(earthPosX, 0, earthPosZ);  //移动当前坐标系原点至地球处
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(distance_ME * cos(2 * pi * i / n), 0.0f, distance_ME * sin(2 * pi * i / n));
	}
	glEnd();
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

void timerFunction(int value)
{
	earthPosX = distance_ES * cos(angle_ES * pi); 	//求地球x，z坐标
	earthPosZ = distance_ES * sin(angle_ES * pi);
	monthPosX = earthPosX + distance_ME * cos(angle_ME * pi);//求月球x，z坐标
	monthPosZ = earthPosZ + distance_ME * sin(angle_ME * pi);

	angle_ES += speed_ES;     //地日角度增加
	angle_ME += speed_ME;     //地月角度增加
	angle_self += speed_self; //自转角度增加

	if (angle_self > 360)
	{
		angle_self = 0.0f;
	}
	glutPostRedisplay();
	glutTimerFunc(33, timerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspecratio = (GLfloat)w / (GLfloat)h;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-3, 3, -3 / aspecratio, 3 / aspecratio, -6.0, 6.0);
	else
		glOrtho(-3 * aspecratio, 3 * aspecratio, -3, 3, -6, 6.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 500);
	glutCreateWindow("Galaxy");
	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutTimerFunc(33, timerFunction, 1);
	glutMainLoop();

	return 0;
}