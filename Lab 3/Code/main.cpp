#include <windows.h>
#include <math.h>
#include <gl.h>
#include <glut.h>
#include <iostream>

#define PI			3.1415926
#define	COLORNUM		14

using namespace std;

//==============Support Class============================
class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	void set(Point3& p)
						{ x = p.x; y = p.y; z = p.z;}
	Point3() { x = y = z = 0;}
	Point3(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
						{ r = red; g = green; b = blue;}
	void set(Color3& c)
						{ r = c.r; g = c.g; b = c.b;}
	Color3() { r = g = b = 0;}
	Color3(float red, float green, float blue)
						{ r = red; g = green; b = blue;}

};
class Point2
{
	public:
		Point2() { x = y = 0.0f; } // constructor 1
		Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
		void set(float xx, float yy) { x = xx; y = yy; }
		float getX() { return x;}
		float getY() { return y;}
		void draw()		{	glBegin(GL_POINTS);
								glVertex2f((GLfloat)x, (GLfloat)y);
							glEnd();
						}
	private:
		float 	x, y;
};
class IntRect
{
	 public:
		IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
		IntRect( int left, int right, int bottom, int top)
			{ l = left; r = right; b = bottom; t = top; }
		void set( int left, int right, int bottom, int top)
			{ l = left; r = right; b = bottom; t = top; }
		void draw(){
						glRecti(l, b, r, t);
						glFlush();
					} // draw this rectangle using OpenGL
		int  getWidth(){return (r-l);}
		int  getHeight() { return (t-b);}
	 private:
		int	l, r, b, t;
};


class RealRect
{
	 public:
		RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
		RealRect( float left, float right, float bottom, float top)
			{ l = left; r = right; b = bottom; t = top; }
		void set( float left, float right, float bottom, float top)
			{ l = left; r = right; b = bottom; t = top; }
		float  getWidth(){return (r-l);}
		float  getHeight() { return (t-b);}
		void draw(){
							glRectf(l, b, r, t);
							glFlush();
						};// draw this rectangle using OpenGL
	 private:
		float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	void set(Vector3& v)
						{ x = v.x; y = v.y; z = v.z;}
	void flip()
						{ x = -x; y = -y; z = -z;}
	void normalize();
	Vector3() { x = y = z = 0;}
	Vector3(float dx, float dy, float dz)
						{ x = dx; y = dy; z = dz;}
	Vector3(Vector3& v)
						{ x = v.x; y = v.y; z = v.z;}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};
//==============Support Class============================

//==============Mesh Class===============================
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
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
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
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if(face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCuboid(float fSizeX, float fSizeY, float fSizeZ);
	void CreateCylinderWithHole(int nSegment, float fHeight, float f0Radius, float fIRadius);
	void CreateShape1(float height, float topLength, float botLength, float topWidth, float botWidth);
	void CreateShape2(float height, float topLength, float botLength, float width);
	void CreateShape3(float height, int inSegment, float inIRadius, float inORadius, int outSegment, float outIRadius, float outORadius);
	void CreateShape4(float fSizeX, float fSizeY, float fSizeZ, float fSizeX2, float fSizeY2, float fSizeZ2);
	void SetColor(int colorIdx);
};
//==============Mesh Class===============================

//==============Implement================================
int		screenWidth = 1400;
int		screenHeight= 700;
float   angle = 45;
float   cameraHeight = 4;
float   cameraDistance = 12;
bool    drawMode = 0;
bool    viewMode = 1;
float   wheelAngle = 0.0f;
bool    autoMode = 0;
bool    wheelDirection = 0;


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0},
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0},
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {0.7, 0.8, 0.7}};





void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight/2, 0);
	for(i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight/2;
		pt[i+1].set(x, y, z);

		y = -fHeight/2;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, -fHeight/2, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}


void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;


	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;


	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ){
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set( fSizeX, fSizeY, fSizeZ);
	pt[2].set( fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set( fSizeX, -fSizeY, fSizeZ);
	pt[6].set( fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

    numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateShape1(float height, float topLength, float botLength, float topWidth, float botWidth){
    int i;
    numVerts = 16;
    pt = new Point3[numVerts];
    pt[0].set(-topLength / 2, height / 2, -topWidth / 2);
	pt[1].set(-topLength / 2, height / 2, topWidth / 2);
	pt[2].set(topLength / 2, height / 2, topWidth / 2);
	pt[3].set(topLength / 2, height / 2, -topWidth / 2);
	pt[4].set(-topLength / 2, -height / 2, -topWidth / 2);
	pt[5].set(-topLength / 2, -height / 2, topWidth / 2);
	pt[6].set(topLength / 2, -height / 2, topWidth / 2);
	pt[7].set(topLength / 2, -height / 2, -topWidth / 2);
	pt[8].set(-botLength / 2, -height / 2 - 0.1*height, -botWidth / 2);
	pt[9].set(-botLength / 2, -height / 2 - 0.1*height, botWidth / 2);
	pt[10].set(botLength / 2, -height / 2 - 0.1*height, botWidth / 2);
	pt[11].set(botLength / 2, -height / 2 - 0.1*height, -botWidth / 2);
    pt[12].set(-botLength / 2, -height / 2 - 0.15*height, -botWidth / 2);
	pt[13].set(-botLength / 2, -height / 2 - 0.15*height, botWidth / 2);
	pt[14].set(botLength / 2, -height / 2 - 0.15*height, botWidth / 2);
	pt[15].set(botLength / 2, -height / 2 - 0.15*height, -botWidth / 2);

	numFaces = 14;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;

    face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 1;
	face[1].vert[1].vertIndex = 5;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 2;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

    face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 2;
	face[2].vert[1].vertIndex = 6;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

    face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 3;
	face[3].vert[1].vertIndex = 7;
	face[3].vert[2].vertIndex = 4;
	face[3].vert[3].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

    face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 4;
	face[4].vert[2].vertIndex = 5;
	face[4].vert[3].vertIndex = 1;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

    face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 5;
	face[5].vert[1].vertIndex = 9;
	face[5].vert[2].vertIndex = 10;
	face[5].vert[3].vertIndex = 6;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

    face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 6;
	face[6].vert[1].vertIndex = 10;
	face[6].vert[2].vertIndex = 11;
	face[6].vert[3].vertIndex = 7;
	for(i = 0; i<face[6].nVerts ; i++)
		face[6].vert[i].colorIndex = 6;

    face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 7;
	face[7].vert[1].vertIndex = 11;
	face[7].vert[2].vertIndex = 8;
	face[7].vert[3].vertIndex = 4;
	for(i = 0; i<face[7].nVerts ; i++)
		face[7].vert[i].colorIndex = 7;

    face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 5;
	face[8].vert[1].vertIndex = 9;
	face[8].vert[2].vertIndex = 8;
	face[8].vert[3].vertIndex = 4;
	for(i = 0; i<face[8].nVerts ; i++)
		face[8].vert[i].colorIndex = 8;

    face[9].nVerts = 4;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 9;
	face[9].vert[1].vertIndex = 13;
	face[9].vert[2].vertIndex = 14;
	face[9].vert[3].vertIndex = 10;
	for(i = 0; i<face[9].nVerts ; i++)
		face[9].vert[i].colorIndex = 9;

    face[10].nVerts = 4;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 10;
	face[10].vert[1].vertIndex = 14;
	face[10].vert[2].vertIndex = 15;
	face[10].vert[3].vertIndex = 11;
	for(i = 0; i<face[10].nVerts ; i++)
		face[10].vert[i].colorIndex = 10;

    face[11].nVerts = 4;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 11;
	face[11].vert[1].vertIndex = 15;
	face[11].vert[2].vertIndex = 12;
	face[11].vert[3].vertIndex = 8;
	for(i = 0; i<face[11].nVerts ; i++)
		face[11].vert[i].colorIndex = 11;

    face[12].nVerts = 4;
	face[12].vert = new VertexID[face[12].nVerts];
	face[12].vert[0].vertIndex = 9;
	face[12].vert[1].vertIndex = 13;
	face[12].vert[2].vertIndex = 12;
	face[12].vert[3].vertIndex = 8;
	for(i = 0; i<face[12].nVerts ; i++)
		face[12].vert[i].colorIndex = 12;

    face[13].nVerts = 4;
	face[13].vert = new VertexID[face[13].nVerts];
	face[13].vert[0].vertIndex = 12;
	face[13].vert[1].vertIndex = 13;
	face[13].vert[2].vertIndex = 14;
	face[13].vert[3].vertIndex = 15;
	for(i = 0; i<face[13].nVerts ; i++)
		face[13].vert[i].colorIndex = 13;
}

void Mesh::CreateShape2(float height, float topWidth, float botWidth, float length){
    int i;
    numVerts = 12;
    pt = new Point3[numVerts];
    pt[0].set(-length / 2, height / 2, -topWidth / 2);
	pt[1].set(-length / 2, height / 2, topWidth / 2);
	pt[2].set(length/ 2, height / 2, topWidth/ 2);
	pt[3].set(length / 2, height / 2, -topWidth / 2);
	pt[4].set(-length / 2, -height / 2, -topWidth / 2);
	pt[5].set(-length / 2, -height / 2, topWidth / 2);
	pt[6].set(length / 2, -height / 2, topWidth / 2);
	pt[7].set(length / 2, -height / 2, -topWidth / 2);
	pt[8].set(-length/ 2, -height / 2 - 0.15*height, -botWidth / 2);
	pt[9].set(-length / 2, -height / 2 - 0.15*height, botWidth / 2);
	pt[10].set(length / 2, -height / 2 - 0.15*height, botWidth / 2);
	pt[11].set(length / 2, -height / 2 - 0.15*height, -botWidth / 2);

	numFaces = 10;
	face = new Face[numFaces];

    face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;

    face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 1;
	face[1].vert[1].vertIndex = 5;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 2;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

    face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 2;
	face[2].vert[1].vertIndex = 6;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

    face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 3;
	face[3].vert[1].vertIndex = 7;
	face[3].vert[2].vertIndex = 4;
	face[3].vert[3].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

    face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 4;
	face[4].vert[2].vertIndex = 5;
	face[4].vert[3].vertIndex = 1;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

    face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 5;
	face[5].vert[1].vertIndex = 9;
	face[5].vert[2].vertIndex = 10;
	face[5].vert[3].vertIndex = 6;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

    face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 6;
	face[6].vert[1].vertIndex = 10;
	face[6].vert[2].vertIndex = 11;
	face[6].vert[3].vertIndex = 7;
	for(i = 0; i<face[6].nVerts ; i++)
		face[6].vert[i].colorIndex = 6;

    face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 7;
	face[7].vert[1].vertIndex = 11;
	face[7].vert[2].vertIndex = 8;
	face[7].vert[3].vertIndex = 4;
	for(i = 0; i<face[7].nVerts ; i++)
		face[7].vert[i].colorIndex = 7;

    face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 5;
	face[8].vert[1].vertIndex = 9;
	face[8].vert[2].vertIndex = 8;
	face[8].vert[3].vertIndex = 4;
	for(i = 0; i<face[8].nVerts ; i++)
		face[8].vert[i].colorIndex = 8;

    face[9].nVerts = 4;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 8;
	face[9].vert[1].vertIndex = 9;
	face[9].vert[2].vertIndex = 10;
	face[9].vert[3].vertIndex = 11;
	for(i = 0; i<face[9].nVerts ; i++)
		face[9].vert[i].colorIndex = 9;
}

void Mesh::CreateShape3(float height, int inSegment, float inIRadius, float inORadius, int outSegment, float outIRadius, float outORadius) {
    int numRectangles = 5;
    int vertsPerRect = 8;
    int facesPerRect = 6;
    numVerts = inSegment * 4 + outSegment * 4 + numRectangles * vertsPerRect;
    pt = new Point3[numVerts];

    int i;
    int idx;
    float inAngle = 2*PI/inSegment;
    float x,y,z;

    for(i = 0; i < inSegment; i++){
        x = inORadius * cos(inAngle*i);
        z = inORadius * sin(inAngle*i);
        y = height/2;
        pt[i].set(x, y, z);
        y = -height/2;
        pt[i + inSegment].set(x, y, z);
    }

    for(i = 0; i < inSegment; i++){
        x = inIRadius * cos(inAngle*i);
        z = inIRadius * sin(inAngle*i);
        y = height/2;
        pt[i + 2*inSegment].set(x, y, z);
        y = -height/2;
        pt[i + 3*inSegment].set(x, y, z);
    }
    idx = 4*inSegment;
    float outAngle = 2*PI/outSegment;
    for(i = 0; i < outSegment; i++){
        x = outORadius * cos(outAngle*i);
        z = outORadius * sin(outAngle*i);
        y = height/2;
        pt[idx].set(x, y, z);
        y = -height/2;
        pt[idx + outSegment].set(x, y, z);
        idx++;
    }
    idx = 4*inSegment;
    for(i = 0; i < outSegment; i++){
        x = outIRadius * cos(outAngle*i);
        z = outIRadius * sin(outAngle*i);
        y = height/2;
        pt[idx + 2*outSegment].set(x, y, z);
        y = -height/2;
        pt[idx + 3*outSegment].set(x, y, z);
        idx++;
    }
    numFaces = inSegment * 4 + outSegment * 4 + numRectangles * facesPerRect;
    face = new Face[numFaces];

    idx = 0;
    // Cylinder Inside
    // Outside
    for(i = 0; i < inSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = i;
        if(i < inSegment - 1)
            face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = 0;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + inSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + inSegment;

		idx++;
    }

    // Inside
    for(i = 2*inSegment; i<3*inSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[1].vertIndex = i;

		if(i <3*inSegment - 1)
			face[idx].vert[0].vertIndex = i + 1;
		else
			face[idx].vert[0].vertIndex = 2*inSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + inSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + inSegment;

		idx++;
	}

    // Top
	for(i = 0; i<inSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[1].vertIndex = i;

		if(i <inSegment - 1)
			face[idx].vert[0].vertIndex = i + 1;
		else
			face[idx].vert[0].vertIndex = 0;
        face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*inSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*inSegment;

		idx++;
	}

	// Bottom
	for(i = 0; i<inSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + inSegment;

		if(i <inSegment - 1)
			face[idx].vert[1].vertIndex = i + inSegment + 1;
		else
			face[idx].vert[1].vertIndex = inSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*inSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*inSegment;

		idx++;
	}

    // Cylinder Outside
    // Outside
	idx = inSegment*4;
	int pad = inSegment*4;
    for(i = 0; i < outSegment; i++){
        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[face[idx].nVerts];

        face[idx].vert[0].vertIndex = pad;
        if(i < outSegment - 1)
            face[idx].vert[1].vertIndex = pad + 1;
		else
			face[idx].vert[1].vertIndex = inSegment*4;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + outSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + outSegment;

		idx++;
		pad++;
    }

    // Inside
    pad = 4*inSegment + 2*outSegment;
    for(i = 2*outSegment; i<3*outSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[1].vertIndex = pad;

		if(i <3*outSegment - 1)
			face[idx].vert[0].vertIndex = pad + 1;
		else
			face[idx].vert[0].vertIndex = 4*inSegment + 2*outSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + outSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + outSegment;

		idx++;
		pad++;
	}

    // Top
    pad = 4*inSegment;
	for(i = 0; i<outSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[1].vertIndex = pad;

		if(i <outSegment - 1)
			face[idx].vert[0].vertIndex = pad + 1;
		else
			face[idx].vert[0].vertIndex = 4*inSegment;
        face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*outSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*outSegment;

		idx++;
		pad++;
	}

    // Bottom
	pad = 4*inSegment;
	for(i = 0; i<outSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = pad + outSegment;

		if(i <outSegment - 1)
			face[idx].vert[1].vertIndex = pad + outSegment + 1;
		else
			face[idx].vert[1].vertIndex = 4*inSegment + outSegment;

		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*outSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*outSegment;

		idx++;
		pad++;
	}

    float rectAngle = 2 * PI / numRectangles;
    float rectWidth = (outIRadius - inORadius) * 0.4;
    idx = inSegment * 4 + outSegment * 4;
    for (i = 0; i < numRectangles; i++) {
        float angle = i * rectAngle;
        float adjustInORadius = inORadius - rectWidth/5;
        float adjustOutIRadius = outIRadius + rectWidth/5;
        float xInner = adjustInORadius * cos(angle);
        float zInner = adjustInORadius * sin(angle);
        float xOuter = adjustOutIRadius * cos(angle);
        float zOuter = adjustOutIRadius * sin(angle);
        float nx = cos(angle + PI / 2);
        float nz = sin(angle + PI / 2);

        pt[idx + i * vertsPerRect + 0].set(xInner - nx*rectWidth / 2, height / 2, zInner - nz*rectWidth / 2);
        pt[idx + i * vertsPerRect + 1].set(xInner + nx*rectWidth / 2, height / 2, zInner + nz*rectWidth / 2);
        pt[idx + i * vertsPerRect + 2].set(xOuter + nx*rectWidth / 2, height / 2, zOuter + nz*rectWidth / 2);
        pt[idx + i * vertsPerRect + 3].set(xOuter - nx*rectWidth / 2, height / 2, zOuter - nz*rectWidth / 2);

        pt[idx + i * vertsPerRect + 4].set(xInner - nx*rectWidth / 2, -height / 2, zInner - nz*rectWidth / 2);
        pt[idx + i * vertsPerRect + 5].set(xInner + nx*rectWidth / 2, -height / 2, zInner + nz*rectWidth / 2);
        pt[idx + i * vertsPerRect + 6].set(xOuter + nx*rectWidth / 2, -height / 2, zOuter + nz*rectWidth / 2);
        pt[idx + i * vertsPerRect + 7].set(xOuter - nx*rectWidth / 2, -height / 2, zOuter - nz*rectWidth / 2);
    }

    idx = inSegment * 4 + outSegment * 4;

    for (int i = 0; i < numRectangles; i++) {
        int baseIdx = inSegment * 4 + outSegment * 4 + i * vertsPerRect;

        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[4]{
            {baseIdx + 3}, {baseIdx + 2}, {baseIdx + 6}, {baseIdx + 7}
        };
        idx++;

        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[4]{
            {baseIdx + 4}, {baseIdx + 5}, {baseIdx + 0}, {baseIdx + 1}
        };
        idx++;


        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[4]{
            {baseIdx + 3}, {baseIdx + 7}, {baseIdx + 4}, {baseIdx + 0}
        };
        idx++;

        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[4]{
            {baseIdx + 1}, {baseIdx + 5}, {baseIdx + 6}, {baseIdx + 2}
        };
        idx++;

        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[4]{
            {baseIdx + 0}, {baseIdx + 1}, {baseIdx + 2}, {baseIdx + 3}
        };
        idx++;

        face[idx].nVerts = 4;
        face[idx].vert = new VertexID[4]{
            {baseIdx + 7}, {baseIdx + 6}, {baseIdx + 5}, {baseIdx + 4}
        };
        idx++;
    }
}

void Mesh::CreateShape4(float fSizeX, float fSizeY, float fSizeZ, float fSizeX2, float fSizeY2, float fSizeZ2){
    int i;
    numVerts = 16;
    pt = new Point3[numVerts];
    pt[0].set(-fSizeX, fSizeY, -fSizeZ);
    pt[1].set(-fSizeX, fSizeY, fSizeZ);
    pt[2].set(fSizeX, fSizeY, fSizeZ);
    pt[3].set(fSizeX, fSizeY, -fSizeZ);
    pt[4].set(-fSizeX2, fSizeY2, -fSizeZ2);
    pt[5].set(-fSizeX2, fSizeY2, fSizeZ2);
    pt[6].set(fSizeX2, fSizeY2, fSizeZ2);
    pt[7].set(fSizeX2, fSizeY2, -fSizeZ2);
    pt[8].set(-fSizeX2, -fSizeY2, -fSizeZ2);
    pt[9].set(-fSizeX2, -fSizeY2, fSizeZ2);
    pt[10].set(fSizeX2, -fSizeY2, fSizeZ2);
    pt[11].set(fSizeX2, -fSizeY2, -fSizeZ2);
    pt[12].set(-fSizeX, -fSizeY, -fSizeZ);
    pt[13].set(-fSizeX, -fSizeY, fSizeZ);
    pt[14].set(fSizeX, -fSizeY, fSizeZ);
    pt[15].set(fSizeX, -fSizeY, -fSizeZ);

    numFaces = 18;
    face = new Face[numFaces];

    face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;

    face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 1;
	face[1].vert[1].vertIndex = 5;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 2;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

    face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 1;
	face[2].vert[1].vertIndex = 13;
	face[2].vert[2].vertIndex = 9;
	face[2].vert[3].vertIndex = 5;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

    face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 6;
	face[3].vert[1].vertIndex = 10;
	face[3].vert[2].vertIndex = 14;
	face[3].vert[3].vertIndex = 2;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

    face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 9;
	face[4].vert[1].vertIndex = 13;
	face[4].vert[2].vertIndex = 14;
	face[4].vert[3].vertIndex = 10;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

    face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 2;
	face[5].vert[1].vertIndex = 14;
	face[5].vert[2].vertIndex = 15;
	face[5].vert[3].vertIndex = 3;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

    face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 1;
	face[6].vert[1].vertIndex = 0;
	face[6].vert[2].vertIndex = 12;
	face[6].vert[3].vertIndex = 13;
	for(i = 0; i<face[6].nVerts ; i++)
		face[6].vert[i].colorIndex = 6;

    face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 0;
	face[7].vert[1].vertIndex = 3;
	face[7].vert[2].vertIndex = 7;
	face[7].vert[3].vertIndex = 4;
	for(i = 0; i<face[5].nVerts ; i++)
		face[7].vert[i].colorIndex = 7;

    face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 0;
	face[8].vert[1].vertIndex = 4;
	face[8].vert[2].vertIndex = 8;
	face[8].vert[3].vertIndex = 12;
	for(i = 0; i<face[5].nVerts ; i++)
		face[8].vert[i].colorIndex = 8;

    face[9].nVerts = 4;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 7;
	face[9].vert[1].vertIndex = 3;
	face[9].vert[2].vertIndex = 15;
	face[9].vert[3].vertIndex = 11;
	for(i = 0; i<face[5].nVerts ; i++)
		face[9].vert[i].colorIndex = 9;

    face[10].nVerts = 4;
	face[10].vert = new VertexID[face[10].nVerts];
	face[10].vert[0].vertIndex = 8;
	face[10].vert[1].vertIndex = 11;
	face[10].vert[2].vertIndex = 15;
	face[10].vert[3].vertIndex = 12;
	for(i = 0; i<face[5].nVerts ; i++)
		face[10].vert[i].colorIndex = 10;

    face[11].nVerts = 4;
	face[11].vert = new VertexID[face[11].nVerts];
	face[11].vert[0].vertIndex = 12;
	face[11].vert[1].vertIndex = 15;
	face[11].vert[2].vertIndex = 14;
	face[11].vert[3].vertIndex = 13;
	for(i = 0; i<face[5].nVerts ; i++)
		face[11].vert[i].colorIndex = 11;

    face[12].nVerts = 4;
	face[12].vert = new VertexID[face[12].nVerts];
	face[12].vert[0].vertIndex = 1;
	face[12].vert[1].vertIndex = 0;
	face[12].vert[2].vertIndex = 4;
	face[12].vert[3].vertIndex = 5;
	for(i = 0; i<face[5].nVerts ; i++)
		face[12].vert[i].colorIndex = 12;

    face[13].nVerts = 4;
	face[13].vert = new VertexID[face[13].nVerts];
	face[13].vert[0].vertIndex = 2;
	face[13].vert[1].vertIndex = 3;
	face[13].vert[2].vertIndex = 7;
	face[13].vert[3].vertIndex = 6;
	for(i = 0; i<face[5].nVerts ; i++)
		face[13].vert[i].colorIndex = 13;

    face[14].nVerts = 4;
	face[14].vert = new VertexID[face[14].nVerts];
	face[14].vert[0].vertIndex = 9;
	face[14].vert[1].vertIndex = 8;
	face[14].vert[2].vertIndex = 12;
	face[14].vert[3].vertIndex = 13;
	for(i = 0; i<face[5].nVerts ; i++)
		face[14].vert[i].colorIndex = 14;

    face[15].nVerts = 4;
	face[15].vert = new VertexID[face[15].nVerts];
	face[15].vert[0].vertIndex = 11;
	face[15].vert[1].vertIndex = 10;
	face[15].vert[2].vertIndex = 14;
	face[15].vert[3].vertIndex = 15;
	for(i = 0; i<face[5].nVerts ; i++)
		face[15].vert[i].colorIndex = 0;

    face[16].nVerts = 4;
	face[16].vert = new VertexID[face[16].nVerts];
	face[16].vert[0].vertIndex = 4;
	face[16].vert[1].vertIndex = 5;
	face[16].vert[2].vertIndex = 6;
	face[16].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[16].vert[i].colorIndex = 1;

    face[17].nVerts = 4;
	face[17].vert = new VertexID[face[17].nVerts];
	face[17].vert[0].vertIndex = 8;
	face[17].vert[1].vertIndex = 9;
	face[17].vert[2].vertIndex = 10;
	face[17].vert[3].vertIndex = 11;
	for(i = 0; i<face[5].nVerts ; i++)
		face[17].vert[i].colorIndex = 2;
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

void Mesh::SetColor(int colorIdx){
    for (int f = 0; f < numFaces; f++){
        for (int v = 0; v < face[f].nVerts; v++){
            face[f].vert[v].colorIndex = colorIdx;
        }
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

Mesh	tetrahedron;
Mesh	cube;
Mesh    cuboid;
Mesh    cylinder;
Mesh    cylinder2;
Mesh    shape1_1;
Mesh    shape1_2;
Mesh    shape2_1;
Mesh    shape2_2;
Mesh    shape3;
Mesh    shape4;
Mesh    cuboid2;
Mesh    cuboid3;
Mesh    cylinder3;
Mesh    cylinder4;

int		nChoice = 1;

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(-5, 0, 0);
		glVertex3f(5, 0, 0);
    glEnd();

    glColor3f(0, 1, 0);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 5, 0);
    glEnd();

    glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex3f(0, 0, -5);
		glVertex3f(0, 0, 5);
	glEnd();
}

void setupCameraVolume(){
    if(viewMode){
        gluPerspective(50.0f,1,1.0f, 1000.0f);
    }
    else{
        float	fHalfSize = 5;
        glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
    }
}

void updateAngle(int value){
    if(autoMode){
        if(!wheelDirection){
            wheelAngle -= 5;
        }
        else {
            wheelAngle += 5;
        }
	}
	glutPostRedisplay();
	glutTimerFunc(30, updateAngle, 0);
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setupCameraVolume();
	if(viewMode){
        float cameraX = cameraDistance * sin(angle * PI / 180.0);
        float cameraZ = cameraDistance * cos(angle * PI / 180.0);


        gluLookAt(cameraX, cameraHeight, cameraZ, 0, 0, 0, 0, 1, 0);
        glTranslated(0, -0.5, 0);
	}
	else{
        gluLookAt(10, 0, 0, 0, 0, 0, 0, 1, 0);
        glTranslated(0, -1.5, 0);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(screenWidth/5, 0, screenWidth/2, screenHeight);

	drawAxis();

	// Gia do
    glPushMatrix();
	glTranslated(0, 0.4, 0);
	if (viewMode == false || drawMode == false){
        cuboid.SetColor(1);
	}
	else {
        cuboid.DrawWireframe();
	}
	glPopMatrix();

    glPushMatrix();
    glTranslated(0, 2.75, 2.5);
    if (viewMode == false || drawMode == false){
        shape1_1.SetColor(2);
    }
    else{
        shape1_1.DrawWireframe();
    }
	glPopMatrix();

    glPushMatrix();
    glTranslated(0, 2.75, -2.5);
    if (viewMode == false || drawMode == false){
        shape1_2.SetColor(2);
    }
    else{
        shape1_2.DrawWireframe();
    }
	glPopMatrix();

    glPushMatrix();
    glTranslated(0, 2.75, -1);
    glRotated(90, 1.0, 0, 0);
    if (viewMode == false || drawMode == false){
        shape2_1.SetColor(3);
    }
    else {
        shape2_1.DrawWireframe();
    }
	glPopMatrix();

	glPushMatrix();
    glTranslated(0, 2.75, 1);
    glRotated(-90, 1.0, 0, 0);
	if (viewMode == false || drawMode == false){
        shape2_2.SetColor(3);
    }
    else {
        shape2_2.DrawWireframe();
    }
	glPopMatrix();

	glPushMatrix();
    glTranslated(0.3, 2.75, 0);
    glRotated(-90, 0, 0, 1.0);
	if (viewMode == false || drawMode == false){
        cylinder.SetColor(4);
    }
    else {
        cylinder.DrawWireframe();
    }
	glPopMatrix();

    // Banh xe
    glPushMatrix();
    glTranslated(0.3, 2.75, 0);
    glRotated(-90, 0, 0, 1.0);
    glRotatef(wheelAngle, 0.0f, 1.0f, 0.0f);
	if (viewMode == false || drawMode == false){
        shape3.SetColor(5);
    }
    else {
        shape3.DrawWireframe();
    }
	glPopMatrix();


	glPushMatrix();
	float radius = 1.125;
	float y = 2.75  + radius * sin(-PI/2 - wheelAngle * PI / 180.0);
	float z = radius * cos(-PI/2 - wheelAngle * PI / 180.0);
	glTranslated(0.6, y, z);
    glRotated(-90, 0, 0, 1.0);
	if (viewMode == false || drawMode == false){
        cylinder2.SetColor(11);
    }
    else {
        cylinder2.DrawWireframe();
    }
	glPopMatrix();

	// Thanh truot
	glPushMatrix();
    glTranslated(0.6, 2.85, z);
    glRotated(90, 0, 1.0, 0);
	if (viewMode == false || drawMode == false){
        shape4.SetColor(0);
    }
    else {
        shape4.DrawWireframe();
    }
	glPopMatrix();

    glPushMatrix();
    glTranslated(0.55, 2.75, 2.5);
	if (viewMode == false || drawMode == false){
        cuboid2.SetColor(1);
    }
    else {
        cuboid2.DrawWireframe();
    }
	glPopMatrix();

    glPushMatrix();
    glTranslated(0.55, 2.75, -2.5);
	if (viewMode == false || drawMode == false){
        cuboid3.SetColor(1);
    }
    else {
        cuboid3.DrawWireframe();
    }
	glPopMatrix();

	glPushMatrix();
    glTranslated(0.6, 2.75, -2.0 + z);
    glRotated(90, 1.0, 0, 0);
	if (viewMode == false || drawMode == false){
        cylinder3.SetColor(11);
    }
    else {
        cylinder3.DrawWireframe();
    }
	glPopMatrix();

	glPushMatrix();
    glTranslated(0.6, 2.75, 2.0 + z);
    glRotated(90, 1.0, 0, 0);
	if (viewMode == false || drawMode == false){
        cylinder4.SetColor(11);
    }
    else {
        cylinder4.DrawWireframe();
    }
	glPopMatrix();

	glFlush();
    glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y) {
    if (key == '+'){
        cameraDistance += 0.1;
    }
    else if (key == '-') {
        cameraDistance -= 0.1;
    }
    else if (key == 'W' || key == 'w'){
        drawMode = !drawMode;
    }
    else if (key == 'v' || key == 'V'){\
        wheelAngle = 0;
        viewMode = !viewMode;
    }
    else if (key == '1'){
        wheelAngle += 5.0f;
    }
    else if (key == '2'){
        wheelAngle -= 5.0f;
    }
    else if (key == 'a' || key == 'A'){
        autoMode = !autoMode;
    }
    else if (key == 'b' || key == 'B'){
        wheelDirection = !wheelDirection;
    }
    glutPostRedisplay();
}

void mySpecialFunc(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT){
        angle += 1;
    }
    else if (key == GLUT_KEY_RIGHT){
        angle -= 1;
    }
    else if (key == GLUT_KEY_UP) {
        cameraHeight += 0.1;
    }
    else if (key == GLUT_KEY_DOWN) {
        cameraHeight -= 0.1;
    }
    glutPostRedisplay();
}

void myInit()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

int main(int argc, _TCHAR* argv[])
{
    cout << "1     :  Xoay banh xe nguoc chieu kim dong ho" << endl;
    cout << "2     :  Xoay banh xe cung chieu kim dong ho" << endl;
    cout << "a, A  :  Bat/tat che do xoay banh xe tu dong" << endl;
    cout << "b, B  :  Chuyen huong quay cua banh xe" << endl;
    cout << "W, w  :  Chuyen doi qua lai giua che do khung day va to mau" << endl;
    cout << "V, v  :  Chuyen doi qua lai giua view 3D va 2D" << endl;
    cout << "+     : Tang khoang cach camera" << endl;
    cout << "-     : Giam khoang cach camera" << endl;
    cout << "up arrow  : Tang chieu cao camera" << endl;
    cout << "down arrow: Giam chieu cao camera" << endl;
    cout << "<-        : Quay camera theo chieu kim dong ho" << endl;
    cout << "->        : Quay camera nguoc chieu kim dong ho" << endl;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(0, 0); // set window position on screen
	glutCreateWindow("Hoang Minh Hai Dang - 2110120"); // open the screen window
    glutSpecialFunc(mySpecialFunc);
    glutKeyboardFunc(myKeyboard);
	cuboid.CreateCuboid(0.8, 0.4, 3.25);
	shape1_1.CreateShape1(3, 0.3, 0.5, 0.4, 0.7);
	shape1_2.CreateShape1(3, 0.3, 0.5, 0.4, 0.7);
	shape2_1.CreateShape2(2, 0.3, 0.6, 0.3);
	shape2_2.CreateShape2(2, 0.3, 0.6, 0.3);
	cylinder.CreateCylinder(20, 0.25, 0.15);
	shape3.CreateShape3(0.2, 20, 0.15, 0.4, 40, 1.0, 1.25);
	cylinder2.CreateCylinder(20, 0.75, 0.075);
	shape4.CreateShape4(0.25, 1.75, 0.15, 0.075, 1.5, 0.1);
	cuboid2.CreateCuboid(0.4, 0.15, 0.15);
	cuboid3.CreateCuboid(0.4, 0.15, 0.15);
	cylinder3.CreateCylinder(20, 3.5, 0.1);
	cylinder4.CreateCylinder(20, 3.5, 0.1);

	myInit();
    glutDisplayFunc(myDisplay);
    glutTimerFunc(30, updateAngle, 0);

	glutMainLoop();
	return 0;
}

