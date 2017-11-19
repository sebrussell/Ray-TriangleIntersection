#include "Math.h"
#include <iostream>

float Math::GetQuickMagnitude(Vector3 _vector)
{
	return GetQuickSqrt(pow(_vector.x, 2) + pow(_vector.y, 2) + pow(_vector.z, 2));
}

float Math::GetMagnitude(Vector3 _vector)
{
	return pow(pow(_vector.x, 2) + pow(_vector.y, 2) + pow(_vector.z, 2), 0.5);
}


float Math::GetDotProduct(Vector3 _vector1, Vector3 _vector2)
{
	return (_vector1.x * _vector2.x) + (_vector1.y * _vector2.y) + (_vector1.z * _vector2.z); // 3 multiplications + 2 additions
}

float Math::GetShortestAngle(Vector3 _vector1, Vector3 _vector2)
{	
	return acos((GetDotProduct(_vector1, _vector2)) / (GetMagnitude(_vector1) * GetMagnitude(_vector2))) * 180 / 3.1459;
}

Vector3 Math::GetCrossProduct(Vector3 _vector1, Vector3 _vector2)
{
	Vector3 result(0, 0, 0);
	
	result.x = (_vector1.y * _vector2.z) - (_vector1.z * _vector2.y);	//6 multiplications and 3 subtractions which is 9 operations
	result.y = (_vector1.z * _vector2.x) - (_vector1.x * _vector2.z);
	result.z = (_vector1.x * _vector2.y) - (_vector1.y * _vector2.x);
	
	
	return result;	
}

float Math::GetTripleProduct(Vector3 _vector1, Vector3 _vector2, Vector3 _vector3)
{
	float result;
	
	Vector3 cross = GetCrossProduct(_vector1, _vector2);
	result = GetDotProduct(_vector3, cross);
	
	return result;
}

float Math::GetAntiClockwiseAngle(Vector3 _vector1, Vector3 _vector2, Vector3 _viewVector)
{
	float result = GetShortestAngle(_vector1, _vector2);
	
	float tripleProduct = GetTripleProduct(_vector1, _vector2, _viewVector);
	
	if(tripleProduct < 0)
	{
		result = 360 - result;
	}

	return result;
}

float Math::GetQuickSqrt(float _number)
{	
		float y = _number;
		long i = *(long *)&y;
		i = 0x1fbd1df5 + (i >> 1);
		return *(float *)&i;
}

Vector3 Math::CheckForIntersection(Ray _Ray1, Ray _Ray2)
{
	Ray tempRay1, tempRay2, totalRay;
	Vector3 interestionPoint;
	
	float sValue;	
	float tValue;
	
	
	//finds the multiplier
	float xMultiplier = _Ray1.direction.y;
	float yMultiplier = _Ray1.direction.x;
	
	//multiplies out the first 2 equations - similinatneous equations
	tempRay1.startingPoint.x = _Ray1.startingPoint.x * xMultiplier;
	tempRay1.direction.x = _Ray1.direction.x * xMultiplier;
	tempRay1.startingPoint.y = _Ray1.startingPoint.y * yMultiplier;	
	tempRay1.direction.y = _Ray1.direction.y * yMultiplier;
		
	tempRay2.startingPoint.x = _Ray2.startingPoint.x * xMultiplier;
	tempRay2.direction.x = _Ray2.direction.x * xMultiplier;
	tempRay2.startingPoint.y = _Ray2.startingPoint.y * yMultiplier;	
	tempRay2.direction.y = _Ray2.direction.y * yMultiplier;
	
	//finds out the value of the integerer on the right hand side
	float x = tempRay2.startingPoint.x - tempRay2.startingPoint.y;
	
	//works out the s value
	sValue = (tempRay1.startingPoint.x - tempRay1.startingPoint.y - x) / (tempRay2.direction.x - tempRay2.direction.y);
	
	//from the s value it can calculate the t value
	tValue = ((tempRay2.startingPoint.y + (tempRay2.direction.y * sValue)) - tempRay1.startingPoint.y) / tempRay1.direction.y;
	
	//checks with the 3rd equation to see if the intersect
	if((_Ray1.startingPoint.z + (_Ray1.direction.z * tValue)) == (_Ray2.startingPoint.z + (_Ray2.direction.z * sValue)))
	{
		interestionPoint.x = _Ray1.startingPoint.x + (_Ray1.direction.x * tValue);
		interestionPoint.y = _Ray1.startingPoint.y + (_Ray1.direction.y * tValue);
		interestionPoint.z = _Ray1.startingPoint.z + (_Ray1.direction.z * tValue);

	}
	//if they dont intersect
	else
	{
		//return 0, 0, 0
		interestionPoint = Vector3(0, 0, 0);
	}
	
	return interestionPoint;	
}

void Math::WriteVector(Vector3 _vector)
{
	std::cout << "X Component: " << _vector.x << std::endl;
	std::cout << "Y Component: " << _vector.y << std::endl;
	std::cout << "Z Component: " << _vector.z << std::endl;
}

Vector3 Math::GetPlaneNormal(Plane _plane)
{
	Vector3 a = SubtractVectors(_plane.b, _plane.a);
	Vector3 b = SubtractVectors(_plane.c, _plane.a);
	
	Vector3 topVector = GetCrossProduct(a, b);
	float bottomVector = GetMagnitude(topVector);
	
	topVector.x = topVector.x / bottomVector;
	topVector.y = topVector.y / bottomVector;
	topVector.z = topVector.z / bottomVector;

	return topVector;
}

Vector3 Math::AddVectors(Vector3 _vector1, Vector3 _vector2)
{
	Vector3 temp;
	
	temp.x = _vector1.x + _vector2.x;	//3 operations
	temp.y = _vector1.y + _vector2.y;
	temp.z = _vector1.z + _vector2.z;
	
	return temp;
}

Vector3 Math::SubtractVectors(Vector3 _vector1, Vector3 _vector2)
{
	Vector3 temp;
	
	temp.x = _vector1.x - _vector2.x;	//3 operations
	temp.y = _vector1.y - _vector2.y;
	temp.z = _vector1.z - _vector2.z;
	
	return temp;
}

Vector3 Math::MultiplyVectorWithFloat(Vector3 _vector1, float _float)
{
	Vector3 temp;
	
	temp.x = _vector1.x * _float;	//3  operations
	temp.y = _vector1.y * _float;
	temp.z = _vector1.z * _float;
	
	return temp;
}

bool Math::CheckForPlaneIntersection(Plane _plane, Ray _ray, std::shared_ptr<Vector3> _intersectionPoint)
{		
	float top = _plane.k - GetDotProduct(_plane.normal, _ray.startingPoint); //1 subtraction + function which is 5 operations = 6 operations
	float bottom = GetDotProduct(_plane.normal, _ray.direction); // functions which is 5 operations

	float t = top / bottom;	//division is 1 operations
	
	//total of 12 operations so far

	
	if(!isinf(t) && t > 0)
	{
		Vector3 temp = AddVectors(_ray.startingPoint, MultiplyVectorWithFloat(_ray.direction, t));	//6 operations
				
				//5				9				3									3					= total of 20 operations
		if((GetDotProduct(GetCrossProduct(SubtractVectors(_plane.b, _plane.a), SubtractVectors(temp, _plane.a)), _plane.normal)) >= 0)
		{
			if((GetDotProduct(GetCrossProduct(SubtractVectors(_plane.c, _plane.b), SubtractVectors(temp, _plane.b)), _plane.normal)) >= 0)
			{
				if((GetDotProduct(GetCrossProduct(SubtractVectors(_plane.a, _plane.c), SubtractVectors(temp, _plane.c)), _plane.normal)) >= 0)
				{
					//comparison if statements = 60 operations therefore 72 operations so far
					_intersectionPoint->x = temp.x;
					_intersectionPoint->y = temp.y;
					_intersectionPoint->z = temp.z;
					return true;
				}
			}
		}
	}
	
	//72 total operations
	return false;
	
	
}

Plane Math::SetupPlane(Plane _plane)
{
	_plane.normal = GetPlaneNormal(_plane);
	_plane.k = GetDotProduct(_plane.normal, _plane.a);
	return _plane;
}

