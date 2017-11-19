#ifndef OPENGL_H
#define OPENGL_H

#include "Camera.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>



class OpenGL
{
	public:
		OpenGL();
		~OpenGL();
		int Setup();
		void SetCamera(std::shared_ptr<Camera> _camera) { m_camera = _camera; }
		
		
		int GetWindowWidth() { return SCR_WIDTH; }
		int GetWindowHeight() { return SCR_HEIGHT; }
		
		bool ShouldWindowClose();
		void ProcessInput();
		void SwapBuffers();
		
		//-------- CALLBACK FUNCTIONS ----------//
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void error_callback(int error, const char* description);
		
		
		
		float deltaTime;	// Time between current frame and last frame
	private:
		GLFWwindow* m_window;
		std::weak_ptr<Camera> m_camera;
		float lastFrame; // Time of last frame
		int SCR_WIDTH;
		int SCR_HEIGHT;
		
		
};

#endif