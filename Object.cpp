#include "Object.h"

Object::Object(std::string _location)
{
	m_loader.LoadFile(_location);
	
	vertexAmount = m_loader.LoadedVertices.size() * 3;
	
	float vertices[vertexAmount];
	
	float x, y, z;
	float g, h, j;
	float c, v, b;
	
	for(int i = 0; i < m_loader.LoadedVertices.size(); i++)
	{
		int n = i * 3;
		vertices[n] = m_loader.LoadedVertices[i].Position.X;
		vertices[n + 1] = m_loader.LoadedVertices[i].Position.Y;
		vertices[n + 2] = m_loader.LoadedVertices[i].Position.Z;
		
		if(i % 3 == 0)
		{
			
			x = m_loader.LoadedVertices[n].Position.X;
			y = m_loader.LoadedVertices[n].Position.Y;
			z = m_loader.LoadedVertices[n].Position.Z;

			
			g = m_loader.LoadedVertices[n + 1].Position.X;
			h = m_loader.LoadedVertices[n + 1].Position.Y;
			j = m_loader.LoadedVertices[n + 1].Position.Z;

			
			c = m_loader.LoadedVertices[n + 2].Position.X;
			v = m_loader.LoadedVertices[n + 2].Position.Y;
			b = m_loader.LoadedVertices[n + 2].Position.Z;

			Plane plane(x, y, z, g, h, j, c, v, b);
			plane = Math::SetupPlane(plane);
			triangles.push_back(plane);
		}
		

	}
	
	std::cout << "b";
	
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 	
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

void Object::DrawHit()
{
	unsigned int hitVBO, hitVAO;
	float vertices[30];
	for(int i = 0; i < 10; i ++)
	{
		int n = i * 3;
		vertices[n] = 0;
		vertices[n + 1] = 0;
		vertices[n + 2] = 0;
	}
	
}

bool Object::CheckForIntersection(Ray _ray)
{
	return true;
}

