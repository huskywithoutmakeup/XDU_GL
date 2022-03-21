#include<GL/glut.h>

void init()
{	
	GLfloat light_position[]={1.0,1.0,1.0,0.0};
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable( GL_DEPTH_TEST );
}

void RenderScene()
{
		//设置材质的各种光的颜色成分反射率
	GLfloat no_mat[] ={0.0,0.0,0.0,1.0};
	GLfloat mat_ambient[] = {0.8,0.8,0.8,1.0};
	GLfloat mat_diffuse[] = {0.1,0.5,0.8,1.0};
	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat no_shininess[] = {0.0};
	GLfloat low_shininess[] = {5.0};
	GLfloat high_shininess[] = {100.0};
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glTranslated(0.0,0.0,-20.0);

	glDisable(GL_LIGHTING);

	glColor3f(0.2, 0.2, 0.8);

	//线框
	glPushMatrix();
	glTranslated(-60.0, 60.0, 0.0);
	glutWireTeapot(10.0);
	glPopMatrix();

	//无光照
	glPushMatrix();
	glTranslated(0.0, 60.0, 0.0);
	glutSolidTeapot(10.0);
	glPopMatrix();

	glEnable(GL_LIGHTING);

	//仅有环境光
	glPushMatrix();
	glTranslated(60.0, 60.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shininess);
	glutSolidTeapot(10.0);
	glPopMatrix();

	//有环境光和漫反射光，采用Gouraud插值着色的茶壶
	glPushMatrix();
	glTranslated(-60.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
	glutSolidTeapot(10.0);
	glPopMatrix();

	//有环境光、漫反射光和镜面高光，采用Gouraud插值着色的茶壶
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
	glutSolidTeapot(10.0);
	glPopMatrix();

	//有环境光、漫反射光和镜面高光，采用Phone插值着色的茶壶
	glPushMatrix();
	glTranslated(60.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
	glutSolidTeapot(10.0);
	glPopMatrix();
	
	glFlush();
}

void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspecratio = (GLfloat)w/(GLfloat)h;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-100,100,-100.0/aspecratio,100.0/aspecratio,10.0,40.0);
	else
		glOrtho(-100.0*aspecratio,100.0*aspecratio,-100.0,100.0,10.0,40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple Lighting");
	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();

	return 0;
}