#include <iostream>
#include <time.h>

#include "Math.h"

int main(int argc, char* argv[])
{	

	Line line1(0, 0, 0, 1, 0, 0);
	Line line2(0.5, 0.001, -3, 0, 0, 1);
	
	Math::WriteVector(Math::CheckForIntersection(line1, line2));
	


	return 0;
}

