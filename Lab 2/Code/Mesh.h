#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


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
	void CreateShape4(float fSizeX, float fSizeY, float fSizeZ);
};

#endif
