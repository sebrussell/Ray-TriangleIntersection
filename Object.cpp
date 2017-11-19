#include "Object.h"

Object::Object(std::string _location)
{
	m_loader.LoadFile(_location);
	
	vertexAmount = m_loader.LoadedVertices.size() * 6;
	
	float vertices[vertexAmount];
	
	float x, y, z;
	float g, h, j;
	float c, v, b;
	int memoryLocation = 0;
	
	for(int i = 0; i < m_loader.LoadedVertices.size(); i++)
	{
		int n = i * 6;
		vertices[n] = m_loader.LoadedVertices[i].Position.X;
		vertices[n + 1] = m_loader.LoadedVertices[i].Position.Y;
		vertices[n + 2] = m_loader.LoadedVertices[i].Position.Z;
		
		vertices[n + 3] = 1.0;
		vertices[n + 4] = 1.0;
		vertices[n + 5] = 0.0;
		
		if(i % 3 == 0)
		{			
			x = m_loader.LoadedVertices[i].Position.X;
			y = m_loader.LoadedVertices[i].Position.Y;
			z = m_loader.LoadedVertices[i].Position.Z;	
			memoryLocation = n;
		}			
		if(i % 3 == 1)
		{
			g = m_loader.LoadedVertices[i].Position.X;
			h = m_loader.LoadedVertices[i].Position.Y;
			j = m_loader.LoadedVertices[i].Position.Z;
		}
		if(i % 3 == 2)
		{
			c = m_loader.LoadedVertices[i].Position.X;
			v = m_loader.LoadedVertices[i].Position.Y;
			b = m_loader.LoadedVertices[i].Position.Z;
			
			Plane plane(x, y, z, g, h, j, c, v, b);
			plane = Math::SetupPlane(plane);
			plane.memoryLocation = memoryLocation;
			plane.previouslyHit = false;
			triangles.push_back(plane);
		}
	}
	
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

	intersectionPoint = std::shared_ptr<Vector3>(new Vector3);
}

Object::~Object()
{
	
}

void Object::Draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexAmount);
	glBindVertexArray(0);
}

void Object::DrawHit(int _memoryLocation, bool _hit)
{
	int n = _memoryLocation + 3;
	int m = _memoryLocation + 9;
	int o = _memoryLocation + 15;
	
	float data[] = { 1.0f, 0.0f, 0.0f };
	
	if(_hit)
	{
		float data[] = { 0.0f, 0.0f, 1.0f };
	}
	else
	{
		float data[] = { 1.0f, 0.0f, 0.0f };
	}
	
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, n * sizeof(float), sizeof(data), &data); 
	glBufferSubData(GL_ARRAY_BUFFER, m * sizeof(float), sizeof(data), &data); 
	glBufferSubData(GL_ARRAY_BUFFER, o * sizeof(float), sizeof(data), &data); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Object::CheckForIntersection(Ray _ray)
{
	int count = 0;
	
	for(int i = 0; i < triangles.size(); i++)
	{
		if(Math::CheckForPlaneIntersection(triangles[i], _ray, intersectionPoint))
		{
			DrawHit(triangles[i].memoryLocation, true);
			count++;
		}
	}
	return count;
}

int Object::CheckForIntersection()
{
	int x_max = 256;
	int y_max = 256;
	int averageAmount = 10;
	int count = 0;
	
	std::vector<Ray> rays;
	for (int xy = 0; xy < x_max*y_max; ++xy) {
		int x = xy / y_max;
		int y = xy % y_max;
		rays.push_back(Ray(0, x, y, 1, 0, 0));
	}
	
	for(int i = 0; i < averageAmount; i++)
	{	
		for(int m = 0; m < triangles.size(); m++)
		{	
			for(int n = 0; n < rays.size(); n++)
			{
				if(Math::CheckForPlaneIntersection(triangles[m], rays[n], intersectionPoint))
				{
					DrawHit(triangles[m].memoryLocation, true);
					count++;
				}
			}
		}
	}
	return count;
}

