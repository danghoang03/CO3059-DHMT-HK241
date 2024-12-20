#include <windows.h>
#include <math.h>
#include <gl\glut.h>

const int screenWidth = 820;
const int screenHeight = 400;

void display()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //VIEWPORT 1
	glViewport(0, 0, 400, 400);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float fSize = 2;
	glOrtho(-fSize, fSize,-fSize, fSize, -10, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 4, 3, 0, 0, 0, 0, 1, 0);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for(float x = -10; x<= 10; x+=0.15)
	{
		glVertex3f(x, 0, 100);
		glVertex3f(x, 0, -100);
	}
	for(float x = -10; x<= 10; x+=0.15)
	{
		glVertex3f(100, 0, x);
		glVertex3f(-100, 0, x);
	}
	glEnd();
	////////////////////////////////////////////
	//VIEWPORT 2
	glViewport(420, 0, 400, 400);
	//Code here - Ve hinh anh o khung nhin 2
	/*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45.0, 1, 1.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 4, 3, 0, 0, 0, 0, 1, 0);

    glBegin(GL_LINES);
	for(float x = -10; x<= 10; x+=0.15)
	{
		glVertex3f(x, 0, 100);
		glVertex3f(x, 0, -100);
	}
    for(float x = -10; x<= 10; x+=0.15)
	{
		glVertex3f(100, 0, x);
		glVertex3f(-100, 0, x);
	}
	glEnd();*/

	glFlush();
}


int main(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Hoàng Minh Hải Đăng - 2110120"); // open the screen window

	glutDisplayFunc(display);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}
