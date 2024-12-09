#include <windows.h>
#include <gl\glut.h>

#define	WINDOW_LEFT		-10
#define	WINDOW_RIGHT		 10
#define	WINDOW_BOTTOM		-10
#define	WINDOW_TOP		 10

void myInit(){
	glClearColor(1.0,1.0,1.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(WINDOW_LEFT, WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_TOP);
}
void drawGrid(){
	glColor3f(0.6f, 0.6f, 0.6f);
	glLineWidth(1.0);

	glBegin(GL_LINES);
		for(int i = WINDOW_LEFT; i<=WINDOW_RIGHT; i++){
			glVertex2i(i, WINDOW_BOTTOM);
			glVertex2i(i, WINDOW_TOP);
		}
		for(int i = WINDOW_BOTTOM; i<WINDOW_TOP; i++){
			glVertex2i(WINDOW_LEFT, i);
			glVertex2i(WINDOW_RIGHT, i);
		}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(5.0);

	glBegin(GL_LINES);
		glVertex2i(WINDOW_LEFT, 0);
		glVertex2i(WINDOW_RIGHT, 0);
		glVertex2i(0, WINDOW_BOTTOM);
		glVertex2i(0, WINDOW_TOP);
	glEnd();
}
void drawHouse(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(3.0);
	glBegin(GL_POLYGON);
        glVertex2i(0, 0);
        glVertex2i(0, 2);
        glVertex2i(2, 4);
        glVertex2i(4, 2);
        glVertex2i(4, 0);
	glEnd();

	glBegin(GL_LINES);
        glVertex2f(0.5f, 2.5f);
        glVertex2f(0.5f, 4.0f);
        glVertex2f(0.5f, 4.0f);
        glVertex2f(1.5f, 4.0f);
        glVertex2f(1.5f, 4.0f);
        glVertex2f(1.5f, 3.5f);
	glEnd();
}
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f);
	drawHouse();

    glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(4, 3, 0);
	drawHouse();
	glPopMatrix();

    glPushMatrix();
	glColor3f(0.6f, 0.0f, 1.0f);
	glTranslatef(2, -3, 0);
	glScalef(1, 1.5f, 1);
	drawHouse();
	glPopMatrix();

    glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glRotatef(90, 0, 0, 1);
	glTranslatef(2, 0, 0);
	drawHouse();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glScalef(-1, -1, 0);
	glScalef(1.5f, 1.5f, 0);
	drawHouse();
	glPopMatrix();

	glFlush();
}

int main(int argc, _TCHAR* argv[]) {
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB); //set the display mode
	glutInitWindowSize(650, 650); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Hoàng Minh Hải Đăng - 2110120");//open the screen window

	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
