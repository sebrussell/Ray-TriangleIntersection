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
	return (_vector1.x * _vector2.x) + (_vector1.y * _vector2.y) + (_vector1.z * _vector2.z);
}

float Math::GetShortestAngle(Vector3 _vector1, Vector3 _vector2)
{	
	return acos((GetDotProduct(_vector1, _vector2)) / (GetMagnitude(_vector1) * GetMagnitude(_vector2))) * 180 / 3.1459;
}

Vector3 Math::GetCrossProduct(Vector3 _vector1, Vector3 _vector2)
{
	Vector3 result(0, 0, 0);
	
	result.x = (_vector1.y * _vector2.z) - (_vector1.z * _vector2.y);
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

Vector3 Math::CheckForIntersection(Line _line1, Line _line2)
{
	Line tempLine1, tempLine2, totalLine;
	Vector3 interestionPoint;
	
	float sValue;	
	float tValue;
	
	
	//finds the multiplier
	float xMultiplier = _line1.direction.y;
	float yMultiplier = _line1.direction.x;
	
	//multiplies out the first 2 equations - similinatneous equations
	tempLine1.startingPoint.x = _line1.startingPoint.x * xMultiplier;
	tempLine1.direction.x = _line1.direction.x * xMultiplier;
	tempLine1.startingPoint.y = _line1.startingPoint.y * yMultiplier;	
	tempLine1.direction.y = _line1.direction.y * yMultiplier;
		
	tempLine2.startingPoint.x = _line2.startingPoint.x * xMultiplier;
	tempLine2.direction.x = _line2.direction.x * xMultiplier;
	tempLine2.startingPoint.y = _line2.startingPoint.y * yMultiplier;	
	tempLine2.direction.y = _line2.direction.y * yMultiplier;
	
	//finds out the value of the integerer on the right hand side
	float x = tempLine2.startingPoint.x - tempLine2.startingPoint.y;
	
	//works out the s value
	sValue = (tempLine1.startingPoint.x - tempLine1.startingPoint.y - x) / (tempLine2.direction.x - tempLine2.direction.y);
	
	//from the s value it can calculate the t value
	tValue = ((tempLine2.startingPoint.y + (tempLine2.direction.y * sValue)) - tempLine1.startingPoint.y) / tempLine1.direction.y;
	
	//checks with the 3rd equation to see if the intersect
	if((_line1.startingPoint.z + (_line1.direction.z * tValue)) == (_line2.startingPoint.z + (_line2.direction.z * sValue)))
	{
		interestionPoint.x = _line1.startingPoint.x + (_line1.direction.x * tValue);
		interestionPoint.y = _line1.startingPoint.y + (_line1.direction.y * tValue);
		interestionPoint.z = _line1.startingPoint.z + (_line1.direction.z * tValue);

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