#include "OBJ_Loader.h"
#include "Shader.h"
#include "Object.h"

std::shared_ptr<Camera> cameraMain = std::make_shared<Camera>(Camera());

int main(int argc, char* argv[])
{	
	
	OpenGL openGL;
	openGL.Setup();
	openGL.SetCamera(cameraMain);
	
	Shader ourShader("..//shaders/defaultShader.vs", "..//shaders/defaultShader.fs");	
	Shader blueShader("..//shaders/defaultShader.vs", "..//shaders/blueShader.fs");	
	ourShader.CreateMatrixBuffer();
	
	Object teapot("..//models/teapot.obj");

	
    Ray ray(0, 0, 0, 1, 0, 0);

	

	while(openGL.ShouldWindowClose())
	{	
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		openGL.ProcessInput();

		
		glm::mat4 model = glm::mat4();		
        glm::mat4 view = cameraMain->GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(cameraMain->Zoom), (float)openGL.GetWindowWidth() / (float)openGL.GetWindowHeight(), 0.1f, 1000.0f);
		ourShader.UpdateMatrix(projection, view);	

		blueShader.use();
		blueShader.setMat4("model", model);		
		teapot.Draw();
		
		ourShader.use();
		ourShader.setMat4("model", model);		
		teapot.Draw();
		

		
		openGL.SwapBuffers(); 
	}
	
	
	/*
	
	
	
	 // 256 * 256 0, 256, 256, 1, 0, 0
	
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
	
	
	int count = 0;
	for(int i = 0; i < 1; i++)
	{
		if(Math::CheckForPlaneIntersection(triangles[i], ray, intersectionPoint))
		{		
			count += 1;
			Math::WriteVector(Vector3(intersectionPoint->x, intersectionPoint->y, intersectionPoint->z)); 
		}
	}
	 
	 std::cout << count;
	*/

	return 0;
}

