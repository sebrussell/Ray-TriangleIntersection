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

	
	if(!std::isinf(t) && t > 0)
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

bool Math::MollerTrumboreIntersection(Plane _plane, Ray _ray, std::shared_ptr<Vector3> _intersectionPoint)
{
	const float epsilon = 0.0000001;
	Vector3 edge1, edge2, h, s, q;
	float a,f,u,v;
	
	edge1 = SubtractVectors(_plane.b, _plane.a);	//3 operations
	edge2 = SubtractVectors(_plane.c, _plane.a);	//3 operations
	h = GetCrossProduct(_ray.direction, edge2);		//9 operations
	a = GetDotProduct(edge1, h);					//5 operations
	if(a > -epsilon && a < epsilon)
	{
		return false;
	}
	
	f = 1 / a;												//1 operations
	s = SubtractVectors(_ray.startingPoint, _plane.a);		//3 operations
	u = f * GetDotProduct(s, h);							//6 operations (5 + 1)
	if (u < 0.0 || u > 1.0)
	{
		return false;
	}
	
	q = GetCrossProduct(s, edge1);					//9 operations
    v = f * GetDotProduct(_ray.direction, q);		//6 operations
	if (v < 0.0 || u + v > 1.0)
	{
        return false;
	}
	
	float t = f * GetDotProduct(edge2, q);			//6 operations
	
	if (t > epsilon) // ray intersection
    {											//	3					3					== 6 operations
        Vector3 outIntersectionPoint = MultiplyVectorWithFloat(AddVectors(_ray.startingPoint, _ray.direction), t); 
		_intersectionPoint->x = outIntersectionPoint.x;
		_intersectionPoint->y = outIntersectionPoint.y;
		_intersectionPoint->z = outIntersectionPoint.z;		
        return true;
    }
	//57 total operations
	return false;
}

bool Math::MatrixIntersection(Plane _plane, Ray _ray, std::shared_ptr<Vector3> _intersectionPoint)
{
					
	const float dz =   _plane.worldToLocal[2][0] * _ray.direction.x
    				 + _plane.worldToLocal[2][1] * _ray.direction.y
    				 + _plane.worldToLocal[2][2] * _ray.direction.z;			//5 operations
	if(dz == 0.0f)
	{
		return false;
	}
	
	const float oz =   _plane.worldToLocal[2][0] * _ray.startingPoint.x
    				 + _plane.worldToLocal[2][1] * _ray.startingPoint.y
    				 + _plane.worldToLocal[2][2] * _ray.startingPoint.z
    				 + _plane.worldToLocal[2][3];								//6 operations
					 
	const float t = - oz / dz;													//2 operations
	
	if(t < 0)
	{
		return false;
	}
						  //		  1	   1										 1	  1										    1	1			=6 operations
	Vector3 hit( _ray.startingPoint.x + (t * _ray.direction.x), _ray.startingPoint.y + (t * _ray.direction.y), _ray.startingPoint.z + (t * _ray.direction.z));
	
	const float b1 =   _plane.worldToLocal[0][0] * hit.x
    				 + _plane.worldToLocal[0][1] * hit.y
    				 + _plane.worldToLocal[0][2] * hit.z
    				 + _plane.worldToLocal[0][3];				//6 operations

	const float b2 =   _plane.worldToLocal[1][0] * hit.x
					 + _plane.worldToLocal[1][1] * hit.y
					 + _plane.worldToLocal[1][2] * hit.z
					 + _plane.worldToLocal[1][3];				//6 operations
					 
	if (  b1 < 0.0f  ||  b2 < 0.0f  ||  b1 + b2 > 1.0f  )
	{
        return false;
	}
	
	_intersectionPoint->x = hit.x;
	_intersectionPoint->y = hit.y;
	_intersectionPoint->z = hit.z;
	
	//31 operations
	return true;
}

Plane Math::SetupPlane(Plane _plane)
{	
	_plane.edge1 = SubtractVectors(_plane.b, _plane.a);
	_plane.edge2 = SubtractVectors(_plane.c, _plane.a);
	_plane.normal = GetCrossProduct(_plane.edge1, _plane.edge2);
	_plane.k = GetDotProduct(_plane.normal, _plane.a);
	
    if (fabs(_plane.normal.x) > fabs(_plane.normal.y) && fabs(_plane.normal.x) > fabs(_plane.normal.z)) 
	{
    	_plane.worldToLocal[0][0] = 0.0f;
		_plane.worldToLocal[0][1] = _plane.edge2.z / _plane.normal.x;
		_plane.worldToLocal[0][2] = - _plane.edge2.y / _plane.normal.x;
		_plane.worldToLocal[0][3] = GetCrossProduct( _plane.c, _plane.a ).x / _plane.normal.x;
    	
		_plane.worldToLocal[1][0] = 0.0f;
		_plane.worldToLocal[1][1] = - _plane.edge1.z / _plane.normal.x;
		_plane.worldToLocal[1][2] = _plane.edge1.y / _plane.normal.x;		
		_plane.worldToLocal[1][3] = - GetCrossProduct( _plane.b, _plane.a  ).x / _plane.normal.x;
    	
		_plane.worldToLocal[2][0] = 1.0f;    	
    	_plane.worldToLocal[2][1] = _plane.normal.y / _plane.normal.x;   
    	_plane.worldToLocal[2][2] = _plane.normal.z / _plane.normal.x;
    	_plane.worldToLocal[2][3] = - GetDotProduct( _plane.a, _plane.normal ) / _plane.normal.x;
    }
    else if (  fabs( _plane.normal.y ) > fabs( _plane.normal.z )  ) {
    	_plane.worldToLocal[0][0] = - _plane.edge2.z / _plane.normal.y;
		_plane.worldToLocal[0][1] = 0.0f;
		_plane.worldToLocal[0][2] = _plane.edge2.x / _plane.normal.y;
		_plane.worldToLocal[0][3] = GetCrossProduct( _plane.c, _plane.a ).y / _plane.normal.y;
		
    	_plane.worldToLocal[1][0] = _plane.edge1.z / _plane.normal.y;
		_plane.worldToLocal[1][1] = 0.0f;
		_plane.worldToLocal[1][2] = - _plane.edge1.x / _plane.normal.y;
		_plane.worldToLocal[1][3] = - GetCrossProduct( _plane.b, _plane.a ).y / _plane.normal.y;
		
    	_plane.worldToLocal[2][0] = _plane.normal.x / _plane.normal.y;
		_plane.worldToLocal[2][1] = 1.0f;
    	_plane.worldToLocal[2][2] = _plane.normal.z / _plane.normal.y;    	
    	_plane.worldToLocal[2][3] = - GetDotProduct( _plane.a, _plane.normal ) / _plane.normal.y;
    }
    else if (  fabs( _plane.normal.z ) > 0.0f  ) {
    	_plane.worldToLocal[0][0] = _plane.edge2.y / _plane.normal.z;
		_plane.worldToLocal[0][1] = - _plane.edge2.x / _plane.normal.z;
		_plane.worldToLocal[0][2] = 0.0f;
		_plane.worldToLocal[0][3] = GetCrossProduct( _plane.c, _plane.a).z / _plane.normal.z;
		
    	_plane.worldToLocal[1][0] = - _plane.edge1.y / _plane.normal.z;
		_plane.worldToLocal[1][1] = _plane.edge1.x / _plane.normal.z;
		_plane.worldToLocal[1][2] = 0.0f;
		_plane.worldToLocal[1][3] = - GetCrossProduct( _plane.b, _plane.a ).z / _plane.normal.z;
		
    	_plane.worldToLocal[2][0] = _plane.normal.x / _plane.normal.z;
		_plane.worldToLocal[2][1] = _plane.normal.y / _plane.normal.z;
    	_plane.worldToLocal[2][2] = 1.0f;
    	_plane.worldToLocal[2][3] = - GetDotProduct( _plane.a, _plane.normal ) / _plane.normal.z;
    }
    else {
    	// This triangle is degenerate. Set the transformation matrix to
    	// the 0 matrix, which in turn will yield 0 values in places that
    	// intersection calculations will detect and treat as a miss.
    	_plane.worldToLocal[0][0] = 0.0f;
    	_plane.worldToLocal[1][0] = 0.0f;
    	_plane.worldToLocal[2][0] = 0.0f;
    	_plane.worldToLocal[0][1] = 0.0f;
    	_plane.worldToLocal[1][1] = 0.0f;
    	_plane.worldToLocal[2][1] = 0.0f;
    	_plane.worldToLocal[0][2] = 0.0f;
    	_plane.worldToLocal[1][2] = 0.0f;
    	_plane.worldToLocal[2][2] = 0.0f;
    	_plane.worldToLocal[0][3] = 0.0f;
    	_plane.worldToLocal[1][3] = 0.0f;
    	_plane.worldToLocal[2][3] = 0.0f;
    }

	return _plane;
}

