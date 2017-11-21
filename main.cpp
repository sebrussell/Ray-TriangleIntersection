#include "OBJ_Loader.h"
#include "Shader.h"
#include "Object.h"
#include <time.h>

std::shared_ptr<Camera> cameraMain = std::make_shared<Camera>(Camera());

int main(int argc, char* argv[])
{	
	
	OpenGL openGL;
	openGL.Setup();
	openGL.SetCamera(cameraMain);
	
	Shader ourShader("..//shaders/defaultShader.vs", "..//shaders/defaultShader.fs");	
	ourShader.CreateMatrixBuffer();
	
	Object teapot("..//models/typhoon.obj");
	//Object teapot("..//models/heli/uh60.obj");

	int x_max = 256;
	int y_max = 256;
	
	clock_t start, stop;

	int count = 0;
	
	int averageAmount = 10;
	
	
	//----REGULAR VERSION 1------ 7.9627 seconds
	count = 0;
	start = clock();
	for(int i = 0; i < averageAmount; i++)
	{		
		for(int x = 0; x < x_max; x++)
		{
			for(int y = 0; y < y_max; y++)
			{
				count += teapot.CheckForIntersection(Ray(0, x, y, 1, 0, 0));
			}
		}			
	}
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Regular Version 1: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;
	
	
	//----REGULAR VERSION 2------ 7.7637 seconds
	count = 0;
	start = clock();
	for(int i = 0; i < averageAmount; i++)
	{	
		for (int xy = 0; xy < x_max*y_max; ++xy) {
			int x = xy / y_max;
			int y = xy % y_max;
			count += teapot.CheckForIntersection(Ray(0, x, y, 1, 0, 0));
		}	
	}		
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Regular Version 2: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;
		
	
	//-----REGULAR VERSION 3----- 7.5525 seconds
	count = 0;
	start = clock();
	count = teapot.CheckForIntersection();
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Regular Version 3: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;	
	
	
	//-----PARRALLEL VERSION 1-----	5.0389 seconds
	count = 0;
	start = clock();
	for(int i = 0; i < averageAmount; i++)
	{	
		#pragma omp parallel
		{
			for(int x = 0; x < x_max; x++)
			{
				#pragma omp for	
				for(int y = 0; y < y_max; y++)
				{
					count += teapot.CheckForIntersection(Ray(0, x, y, 1, 0, 0));
				}
			}	
		}
	}		
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Parallel Version 1: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;	
	
	
	//-----PARRALLEL VERSION 2-----	4.7708 seconds
	count = 0;
	start = clock();
	for(int i = 0; i < averageAmount; i++)
	{	
		#pragma omp parallel for schedule(dynamic,1)
		for (int xy = 0; xy < x_max*y_max; ++xy) {
			int x = xy / y_max;
			int y = xy % y_max;
			count += teapot.CheckForIntersection(Ray(0, x, y, 1, 0, 0));
		}
	}		
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Parallel Version 2: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;	
	
		
	//----MOLLER VERSION 1------ Typhoon Object: 6.0464 seconds
	count = 0;
	start = clock();
	for(int i = 0; i < averageAmount; i++)
	{		
		for(int x = 0; x < x_max; x++)
		{
			for(int y = 0; y < y_max; y++)
			{
				count += teapot.MollerTrumboreIntersection(Ray(0, x, y, 1, 0, 0));
			}
		}			
	}
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Moller Version 1: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;
	
	
	//----MATRIX VERSION 1------ Typhoon Object: 5.6556 seconds
	count = 0;
	start = clock();
	for(int i = 0; i < averageAmount; i++)
	{		
		for(int x = 0; x < x_max; x++)
		{
			for(int y = 0; y < y_max; y++)
			{
				count += teapot.MatrixIntersection(Ray(0, x, y, 1, 0, 0));
			}
		}			
	}
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Matrix Version 1: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;
	
	
	
	//----MOLLER PARALLEL VERSION 1------ Typhoon Object: 5.1626 seconds
	count = 0;
	start = clock();
	for(int i = 0; i < averageAmount; i++)
	{		
		#pragma omp parallel
		{
			for(int x = 0; x < x_max; x++)
			{
				#pragma omp for	
				for(int y = 0; y < y_max; y++)
				{
					count += teapot.MollerTrumboreIntersection(Ray(0, x, y, 1, 0, 0));
				}
			}	
		}		
	}
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Moller Parallel 1: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;
	
	
	//----MATRIX PARALLEL VERSION 1------ Typhoon Object: 5.1457 seconds
	count = 0;
	start = clock();
	for(int i = 0; i < averageAmount; i++)
	{		
		#pragma omp parallel
		{
			for(int x = 0; x < x_max; x++)
			{
				#pragma omp for	
				for(int y = 0; y < y_max; y++)
				{
					count += teapot.MatrixIntersection(Ray(0, x, y, 1, 0, 0));
				}
			}	
		}		
	}
	stop = clock();	
	std::cout << count / averageAmount << std::endl;
	std::cout << "Matrix Parallel 1: " << ((float)(stop - start) / CLOCKS_PER_SEC) / averageAmount << std::endl;
	

	while(openGL.ShouldWindowClose())
	{	
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		openGL.ProcessInput();

		
		glm::mat4 model = glm::mat4();		
        glm::mat4 view = cameraMain->GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(cameraMain->Zoom), (float)openGL.GetWindowWidth() / (float)openGL.GetWindowHeight(), 0.1f, 1000.0f);
		ourShader.UpdateMatrix(projection, view);	


		ourShader.use();
		model = glm::translate(model, glm::vec3(-2.0, 0.0, 0.0));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.5f)); 
		ourShader.setMat4("model", model);		
		teapot.Draw();
		

		
		openGL.SwapBuffers(); 
	}

	return 0;
}

