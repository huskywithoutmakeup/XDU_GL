#include<GL/glut.h>

GLfloat ctrlpoints[4][4][3] = {
	{ {-2, -1, 0}, { -2.0, -1.0, 4.0},
	{ 2.0, -1.0, 4.0}, { 2, -1, 0} },
	{ {-3, 0, 0}, { -3.0, 0, 6.0},
	{ 3.0, 0, 6.0}, { 3, 0, 0}},
	{ {-1.5, 0.5, 0}, {-1.5, 0.5, 3.0},
	{1.5, 0.5, 3.0}, {1.5, 0.5, 0}},
	{ {-2, 1, 0}, { -2.0,  1.0, 4.0},
	{ 2.0,  1.0, 4.0}, { 2,  1, 0} }
};

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMap2f(GL_MAP2_VERTEX_3,0.0,1.0,3,4,0.0,1.0,12,4,&ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);	
	glEnable(GL_DEPTH_TEST);
}

void DrawCurvedSurface(int n,int m)
{
	int i,j;

	glMapGrid2f(n,0.0,1.0,m,0.0,1.0);
	glEvalMesh2(GL_LINE,0,n,0,m);
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++)
		for(j=0;j<4;j++)
			glVertex3f(ctrlpoints[i][j][0],ctrlpoints[i][j][1],ctrlpoints[i][j][2]);
	glEnd();	
}

void RenderScence()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glTranslated(0.0,0.0,-8);
	glRotatef(25.0,1.0,1.0,1.0);
	DrawCurvedSurface(100,16);
	glPopMatrix();
	glFlush();
}

void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspectRatio;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w/(GLfloat)h;
	if(w<=h)
		glOrtho(-5.0,5.0,-5.0/aspectRatio,5.0/aspectRatio,0.0,12.0);
	else
		glOrtho(-5.0*aspectRatio,5.0*aspectRatio,-5.0,5.0,0.0,12.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("BezierTeapot");
	
	init();
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();

	return 0;
}