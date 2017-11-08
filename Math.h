#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <vector>
#include <iostream>

struct Vector3
{
	Vector3() {};
	Vector3(float _x, float _y, float _z) { x = _x, y = _y, z = _z; }
	float x, y, z;
};

struct Line
{
	Line() {};
	Line(float startingX, float startingY, float startingZ, float directionX, float directionY, float directionZ) 
	{
		startingPoint.x = startingX;
		startingPoint.y = startingY;
		startingPoint.z = startingZ;
		
		direction.x = directionX;
		direction.y = directionY;
		direction.z = directionZ;
	}
	Vector3 startingPoint, direction;	
};


class Math
{
	public:
		static float GetMagnitude(Vector3 _vector);
		static float GetDotProduct(Vector3 _vector1, Vector3 _vector2);
		static float GetShortestAngle(Vector3 _vector1, Vector3 _vector2);
		static Vector3 GetCrossProduct(Vector3 _vector1, Vector3 _vector2);
		static float GetTripleProduct(Vector3 _vector1, Vector3 _vector2, Vector3 _vector3);
		static float GetAntiClockwiseAngle(Vector3 _vector1, Vector3 _vector2, Vector3 _viewVector);
		static float GetQuickSqrt(float _number);
		static float GetQuickMagnitude(Vector3 _vector);
		static Vector3 CheckForIntersection(Line _line1, Line _line2);
		static void WriteVector(Vector3 _vector);
};

#endif 