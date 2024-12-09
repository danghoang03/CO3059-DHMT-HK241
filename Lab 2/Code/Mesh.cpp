#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		14


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

void Mesh::CreateShape2(float height, float topLength, float botLength, float width){
    int i;
    numVerts = 12;
    pt = new Point3[numVerts];
    pt[0].set(-topLength / 2, height / 2, -width / 2);
	pt[1].set(-topLength / 2, height / 2, width / 2);
	pt[2].set(topLength / 2, height / 2, width/ 2);
	pt[3].set(topLength / 2, height / 2, -width / 2);
	pt[4].set(-topLength / 2, -height / 2, -width / 2);
	pt[5].set(-topLength / 2, -height / 2, width / 2);
	pt[6].set(topLength / 2, -height / 2, width / 2);
	pt[7].set(topLength / 2, -height / 2, -width / 2);
	pt[8].set(-botLength / 2, -height / 2 - 0.15*height, -width / 2);
	pt[9].set(-botLength / 2, -height / 2 - 0.15*height, width / 2);
	pt[10].set(botLength / 2, -height / 2 - 0.15*height, width / 2);
	pt[11].set(botLength / 2, -height / 2 - 0.15*height, -width / 2);

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

void Mesh::CreateShape4(float fSizeX, float fSizeY, float fSizeZ){
    int i;
    numVerts = 16;
    pt = new Point3[numVerts];
    pt[0].set(-fSizeX, fSizeY, -fSizeZ);
    pt[1].set(-fSizeX, fSizeY, fSizeZ);
    pt[2].set(fSizeX, fSizeY, fSizeZ);
    pt[3].set(fSizeX, fSizeY, -fSizeZ);
    pt[4].set(-fSizeX + 0.4*fSizeX, fSizeY - 0.2*fSizeY, -fSizeZ + 0.4*fSizeZ);
    pt[5].set(-fSizeX + 0.4*fSizeX, fSizeY - 0.2*fSizeY, fSizeZ - 0.4*fSizeZ);
    pt[6].set(fSizeX - 0.4*fSizeX, fSizeY - 0.2*fSizeY, fSizeZ - 0.4*fSizeZ);
    pt[7].set(fSizeX - 0.4*fSizeX, fSizeY - 0.2*fSizeY, -fSizeZ + 0.4*fSizeZ);
    pt[8].set(-fSizeX + 0.4*fSizeX, -fSizeY + 0.2*fSizeY, -fSizeZ + 0.4*fSizeZ);
    pt[9].set(-fSizeX + 0.4*fSizeX, -fSizeY + 0.2*fSizeY, fSizeZ - 0.4*fSizeZ);
    pt[10].set(fSizeX - 0.4*fSizeX, -fSizeY + 0.2*fSizeY, fSizeZ - 0.4*fSizeZ);
    pt[11].set(fSizeX - 0.4*fSizeX, -fSizeY + 0.2*fSizeY, -fSizeZ + 0.4*fSizeZ);
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



