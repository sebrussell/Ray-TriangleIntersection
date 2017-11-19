#include "OpenGL.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


OpenGL::OpenGL()
{

}

int OpenGL::Setup()
{
	//------------------SETUP-------------------------------------------------------------
    if (!glfwInit())
	{
		std::cout << "GLFW Failed to initialise." << std::endl;
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwWindowHint(GLFW_SAMPLES, 4); //multisampling
	
	
	SCR_WIDTH = 800;
	SCR_HEIGHT = 600;
	
	#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif
	
	m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game Engine", NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	
	
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //regular
	
	m_camera = std::weak_ptr<Camera>();
	
	
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);  
	
	
	/*
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);	
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_BLEND);  	
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	//glEnable(GL_CULL_FACE); //this SPEEEDS IT UP LOADS - doesnt work with transpare tho
	*/
   
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetCursorPosCallback(m_window, mouse_callback);  //register mouse callback function
	glfwSetScrollCallback(m_window, scroll_callback);
	glfwSetErrorCallback(error_callback);
	
	//glEnable(GL_PROGRAM_POINT_SIZE);  
	//glEnable(GL_CULL_FACE);
	
	std::cout << "OpenGL Setup Completed" << std::endl;
	return 0;
	
	//-------------------------END SETUP ------------------------------------
}

OpenGL::~OpenGL()
{
	glBindVertexArray(0);
	glfwTerminate();
}

void OpenGL::SwapBuffers()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();

}

bool OpenGL::ShouldWindowClose()
{  
	float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
	return !glfwWindowShouldClose(m_window);
	
}
void OpenGL::ProcessInput()
{
	float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(m_window, true);	
	}
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
        m_camera.lock()->ProcessKeyboard(FORWARD, deltaTime);
	}
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
        m_camera.lock()->ProcessKeyboard(BACKWARD, deltaTime);
	}
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
        m_camera.lock()->ProcessKeyboard(LEFT, deltaTime);
	}
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
        m_camera.lock()->ProcessKeyboard(RIGHT, deltaTime);
	}
	
	

	
}

void OpenGL::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void OpenGL::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


void OpenGL::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGL::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{	
	//cameraMain.ProcessMouseMovement(xpos, ypos);
}

void OpenGL::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//cameraMain.ProcessMouseScroll(yoffset);
}

