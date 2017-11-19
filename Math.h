#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <vector>
#include <iostream>
#include <memory>

struct Vector3
{
	Vector3() {};
	Vector3(float _x, float _y, float _z) { x = _x, y = _y, z = _z; }
	float x, y, z;
};

struct Ray
{
	Ray() {};
	Ray(float startingX, float startingY, float startingZ, float directionX, float directionY, float directionZ) 
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

struct Plane
{
	Plane(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz)
	{
		a = Vector3(ax, ay, az);
		b = Vector3(bx, by, bz);
		c = Vector3(cx, cy, cz);
	}
	Vector3 a, b, c;
	Vector3 normal;
	float k;
	int memoryLocation;
	bool previouslyHit;
};


class Math
{
	public:
		static float GetMagnitude(Vector3 _vector);
		static float GetDotProduct(Vector3 _vector1, Vector3 _vector2);
		static Vector3 GetPlaneNormal(Plane _plane);
		static float GetShortestAngle(Vector3 _vector1, Vector3 _vector2);
		static Vector3 GetCrossProduct(Vector3 _vector1, Vector3 _vector2);
		static float GetTripleProduct(Vector3 _vector1, Vector3 _vector2, Vector3 _vector3);
		static float GetAntiClockwiseAngle(Vector3 _vector1, Vector3 _vector2, Vector3 _viewVector);
		static float GetQuickSqrt(float _number);
		static float GetQuickMagnitude(Vector3 _vector);
		static Vector3 CheckForIntersection(Ray _Ray1, Ray _Ray2);
		static void WriteVector(Vector3 _vector);
		static Vector3 AddVectors(Vector3 _vector1, Vector3 _vector2);
		static Vector3 SubtractVectors(Vector3 _vector1, Vector3 _vector2);
		static Vector3 MultiplyVectorWithFloat(Vector3 _vector1, float _float);
		static bool CheckForPlaneIntersection(Plane _plane, Ray _ray, std::shared_ptr<Vector3> _intersectionPoint);
		static Plane SetupPlane(Plane _plane);
};

#endif 