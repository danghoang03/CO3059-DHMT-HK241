#include <Windows.h>
#include <math.h>
#include <iostream>
#include <glut.h>

using namespace std;
/////////////////////////////////////////////////////////////////////
#define PI			3.1415926
#define	COLORNUM	14

float	ColorArr[COLORNUM][3] = { { 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0,  0.0, 1.0 },
					{ 1.0, 1.0,  0.0 },{ 1.0, 0.0, 1.0 },{ 0.0, 1.0, 1.0 },
					{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },{ 0.9,  0.9, 0.9 },
					{ 1.0, 0.5,  0.5 },{ 0.5, 1.0, 0.5 },{ 0.5, 0.5, 1.0 },
					{ 0.0, 0.0, 0.0 },{ 0.7, 0.7, 0.7 } };
class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;

	int		numFaces;
	Face*		face;
public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();
	void DrawPoint();


	void CreateCube(float fSize);
	void CreateShape1(float radius, float height, int nSlice);
	void CreateShape2(float fSize, float radius, int nSlice);
};
void Mesh::CreateShape1(float radius, float height, int nSlice)
{
    numVerts = nSlice + 1;
    pt = new Point3[numVerts];
    pt[0].set(0, height, 0);
    for(int i = 0; i < nSlice; i++){
        float angle = 2*PI* i/nSlice;

        float x = radius * sin(angle);
        float z = radius * cos(angle);
        pt[i+1].set(x, 0, z);
	}

	numFaces = nSlice;
	face = new Face[numFaces];
	for(int i = 0; i < nSlice; i++){
        face[i].nVerts = 3;
        face[i].vert = new VertexID[3];
        face[i].vert[0].vertIndex = 0;
        face[i].vert[1].vertIndex = i % nSlice + 1;
        face[i].vert[2].vertIndex = (i + 1) % nSlice + 1;
	}
}
void Mesh::CreateShape2(float fSize, float radius, int nSlice)
{
    if(nSlice % 8 != 0)
        throw("So slice phai chia het cho 8");
    float d = 360 / nSlice;
	float dL = fSize/ (nSlice / 4);

	numVerts = 2 * 2 * nSlice;
	numFaces = 3 * nSlice + 4;
	pt = new Point3[numVerts];

	for (int i = 0; i < nSlice / 4; i++) {

        pt[i].set(fSize, fSize, (nSlice/4-i)*dL);
        pt[i+ 2*nSlice].set(fSize, 0, (nSlice/4-i)*dL);
        pt[i + nSlice/4].set((nSlice/4-i)*dL, fSize, 0);
        pt[i + nSlice/4 + 2*nSlice].set((nSlice/4-i)*dL, 0, 0);
        pt[i + 2*nSlice/4].set(0, fSize, i*dL);
        pt[i + 2*nSlice/4 + 2*nSlice].set(0, 0, i*dL);
        pt[i + 3*nSlice/4].set(i*dL, fSize, fSize);
        pt[i + 3*nSlice/4 + 2*nSlice].set(i*dL, 0, fSize);

	}

    for (int i = 0; i < nSlice; i++) {
        float alpha = (45 + i*d)*PI/180;
        float x = fSize/2.0 + radius * sin(alpha);
        float z = fSize/2.0 + radius * cos(alpha);
        pt[i + nSlice].set(x, fSize, z);
        pt[i + 3*nSlice].set(x, 0, z);
	}


	face = new Face[numFaces];

    for (int i = 0; i < nSlice; i++) {
        int next = (i + 1) % nSlice;
        face[i].nVerts = 4;
        face[i].vert = new VertexID[4];
        face[i].vert[0].vertIndex = i + nSlice;
        face[i].vert[1].vertIndex = next + nSlice;
        face[i].vert[2].vertIndex = next + 3*nSlice;
        face[i].vert[3].vertIndex = i + 3*nSlice;

        face[i + nSlice].nVerts = 4;
        face[i + nSlice].vert = new VertexID[4];
        face[i + nSlice].vert[0].vertIndex = i;
        face[i + nSlice].vert[1].vertIndex = next;
        face[i + nSlice].vert[2].vertIndex = next + nSlice;
        face[i + nSlice].vert[3].vertIndex = i + nSlice;

        face[i + 2*nSlice].nVerts = 4;
        face[i + 2*nSlice].vert = new VertexID[4];
        face[i + 2*nSlice].vert[0].vertIndex = i + 2*nSlice ;
        face[i + 2*nSlice].vert[1].vertIndex = next + 2*nSlice ;
        face[i + 2*nSlice].vert[2].vertIndex = next + 3*nSlice;
        face[i + 2*nSlice].vert[3].vertIndex = i + 3*nSlice;
    }

    face[0 + 3*nSlice].nVerts = 4;
    face[0 + 3*nSlice].vert = new VertexID[4];
    face[0 + 3*nSlice].vert[0].vertIndex = 0*nSlice/4;
    face[0 + 3*nSlice].vert[1].vertIndex = 0*nSlice/4 + nSlice / 4;
    face[0 + 3*nSlice].vert[2].vertIndex = 0*nSlice/4 + nSlice / 4 + 2*nSlice;
    face[0 + 3*nSlice].vert[3].vertIndex = 0*nSlice/4 + 2*nSlice;

    face[1 + 3*nSlice].nVerts = 4;
    face[1 + 3*nSlice].vert = new VertexID[4];
    face[1 + 3*nSlice].vert[0].vertIndex = 1*nSlice/4;
    face[1 + 3*nSlice].vert[1].vertIndex = 1*nSlice/4 + nSlice / 4;
    face[1 + 3*nSlice].vert[2].vertIndex = 1*nSlice/4 + nSlice / 4 + 2*nSlice;
    face[1 + 3*nSlice].vert[3].vertIndex = 1*nSlice/4 + 2*nSlice;

    face[2 + 3*nSlice].nVerts = 4;
    face[2 + 3*nSlice].vert = new VertexID[4];
    face[2 + 3*nSlice].vert[0].vertIndex = 2*nSlice/4;
    face[2 + 3*nSlice].vert[1].vertIndex = 2*nSlice/4 + nSlice / 4;
    face[2 + 3*nSlice].vert[2].vertIndex = 2*nSlice/4 + nSlice / 4 + 2*nSlice;
    face[2 + 3*nSlice].vert[3].vertIndex = 2*nSlice/4 + 2*nSlice;

    face[3 + 3*nSlice].nVerts = 4;
    face[3 + 3*nSlice].vert = new VertexID[4];
    face[3 + 3*nSlice].vert[0].vertIndex = 3*nSlice/4;
    face[3 + 3*nSlice].vert[1].vertIndex = 0*nSlice/4;
    face[3 + 3*nSlice].vert[2].vertIndex = 0*nSlice/4 + 2*nSlice;
    face[3 + 3*nSlice].vert[3].vertIndex = 3*nSlice/4 + 2*nSlice;

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;


	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}
void Mesh::DrawPoint()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	glPointSize(3);
	glColor3f(0, 0, 0);
	for (int f = 0; f < numVerts; f++)
	{
		glBegin(GL_POINTS);
		glVertex3f(pt[f].x, pt[f].y, pt[f].z);
		glEnd();
	}
}


//////////////////////////////////////////////////////////////////////
int		screenWidth = 1000;
int		screenHeight = 500;

float	angle = 0;

int		nChoice = 0;

Mesh    cube;
Mesh	shape1;
Mesh    shape2;

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);//x - red
		glVertex3f(4, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);//y - green
		glVertex3f(0, 4, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);//z - blue
		glVertex3f(0, 0, 4);
	glEnd();
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 4, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////////////////////////////////////////////////////
	glViewport(0, 0, screenWidth / 2, screenHeight);

	glPushMatrix();
	drawAxis();

	glRotatef(angle, 0, 1, 0);

	glColor3f(0, 0, 0);
	if (nChoice == 0)
		cube.DrawWireframe();
	else if (nChoice == 1)
		shape1.DrawWireframe();
	else if (nChoice == 2)
		shape2.DrawWireframe();

	/////////////////////////////////////////////////////////////
	glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

	glPopMatrix();
	drawAxis();
	glRotatef(angle, 0, 1, 0);

	if (nChoice == 0)
		cube.DrawColor();
	else if (nChoice == 1)
		shape1.DrawColor();
	else if (nChoice == 2)
		shape2.DrawColor();

	glFlush();
	glutSwapBuffers();
}
void mySpecialFunc(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		angle = angle + 5;
	else if (key == GLUT_KEY_RIGHT)
		angle = angle - 5;
	glutPostRedisplay();
}
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '0':
		nChoice = 0;
		break;
	case '1':
		nChoice = 1;
		break;
	case '2':
		nChoice = 2;
		break;
	}
	glutPostRedisplay();
}
void myInit()
{
	float	fHalfSize = 5;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}


int main(int argc, _TCHAR* argv[])
{
	cout << "Press -> or <- to rotate" << endl;

	cout << "0. Cube" << endl;
	cout << "1. Shape 1" << endl;
	cout << "2. Shape 2" << endl;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Hoàng Minh Hải Đăng - 2110120"); // open the screen window

	myInit();
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(mySpecialFunc);

	cube.CreateCube(2);
	shape1.CreateShape1(2, 4, 10);
	shape2.CreateShape2(4, 2, 16);//Sinh vien tu dien tham so

	glutMainLoop();
    return 0;
}
