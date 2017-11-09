#include <iostream>
#include <time.h>

#include "Math.h"

int main(int argc, char* argv[])
{	

	Plane plane(1, 0, 1, 0, 3, 0, -2, 0, 0);
	Ray ray(0, 1, 5, 0, 0, -1);
	
	plane = Math::SetupPlane(plane);
	
	Math::WriteVector(Math::CheckForPlaneIntersection(plane, ray));
	


	return 0;
}

