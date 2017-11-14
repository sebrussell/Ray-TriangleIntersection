#include <iostream>
#include <time.h>

#include "OBJ_Loader.h"
#include "Math.h"

int main(int argc, char* argv[])
{	
	objl::Loader loader;
	loader.LoadFile("..//models/teapot.obj");
	
	std::vector<Plane> triangles;	
	Ray ray(0, 1, 5, 0, 0, 1);
	std::shared_ptr<Vector3> intersectionPoint(new Vector3);
	
	for(int i = 0; i < loader.LoadedIndices.size() / 3; i++)
	{
		int n = i * 3;
		float x, y, z;
		x = loader.LoadedVertices[loader.LoadedIndices[n]].Position.X;
		y = loader.LoadedVertices[loader.LoadedIndices[n]].Position.Y;
		z = loader.LoadedVertices[loader.LoadedIndices[n]].Position.Z;
		
		float g, h, j;
		g = loader.LoadedVertices[loader.LoadedIndices[n + 1]].Position.X;
		h = loader.LoadedVertices[loader.LoadedIndices[n + 1]].Position.Y;
		j = loader.LoadedVertices[loader.LoadedIndices[n + 1]].Position.Z;
		
		float c, v, b;
		c = loader.LoadedVertices[loader.LoadedIndices[n + 2]].Position.X;
		v = loader.LoadedVertices[loader.LoadedIndices[n + 2]].Position.Y;
		b = loader.LoadedVertices[loader.LoadedIndices[n + 2]].Position.Z;

		Plane plane(x, y, z, g, h, j, c, v, b);
		plane = Math::SetupPlane(plane);
		triangles.push_back(plane);
	}
	
	
	
	for(int i = 0; i < triangles.size(); i++)
	{
		if(Math::CheckForPlaneIntersection(triangles[i], ray, intersectionPoint))
		{			
			Math::WriteVector(Vector3(intersectionPoint->x, intersectionPoint->y, intersectionPoint->z)); 
		}
	}


	return 0;
}

