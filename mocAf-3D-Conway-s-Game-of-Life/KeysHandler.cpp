#include "KeysHandler.h"

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include <iostream>
#include "Shader.h"

KeysHandler::KeysHandler(void)
{
}

KeysHandler::~KeysHandler(void)
{
}

void KeysHandler::processInput(GLFWwindow* window, Shader shaderProg)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		glfwTerminate();
		exit(0);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		
		shaderProg.getFloat("mixThirdParam", &temp);
		shaderProg.setFloat("mixThirdParam", temp - 0.1 );
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		shaderProg.getFloat("mixThirdParam", &temp);
		shaderProg.setFloat("mixThirdParam", temp + 0.1);
	}
}

