#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "model.h"
#include "Shader.h"
#include "Camera.h"
#include "CA_gameOfLife.h"
#include <iostream>
#include "FPS_counter.h"
#include <random>
#include <ctime>

#define SCR_WIDTH 1024
#define SCR_HEIGHT 768


static GLFWwindow * myWindowInit();
void  show_glfw_error(int error, const char* description);
void  window_resized(GLFWwindow* window, int width, int height);
void  framebuffer_size_callback(GLFWwindow* window, int width, int height);
void  processInput(GLFWwindow* window);
void  zBuffer(bool onOff);
void  faceCulling();
void  clearFuncitons();


bool alreadyInit;
std::default_random_engine generator(time(0));

Camera myCamera;

CA_gameOfLife gameOfLifeObj(2); //choose the matrix input for the Cellular automata system

int main()
{

	FPS_counter fpsObj;
	GLFWwindow* window = myWindowInit();

	int screenWidth, screenHeight;
	glfwGetWindowSize(window, &screenWidth, &screenHeight);

	myCamera.initAttributes(glm::vec3(30.0f, 30.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f, screenWidth, screenHeight);

	zBuffer(true);
	faceCulling();

	
	Shader ourShader2("mocAf-3D-Conway-s-Game-of-Life/ressources/shaders/shader_InstancedRendering.vs", "mocAf-3D-Conway-s-Game-of-Life/ressources/shaders/shader_InstancedRendering.fs");



	vector<Model> models;
	models.push_back(Model("mocAf-3D-Conway-s-Game-of-Life/ressources/models/quad/quad_Green.obj", false));
	models.push_back(Model("mocAf-3D-Conway-s-Game-of-Life/ressources/models/quad/quad_Black.obj", false));

	gameOfLifeObj.setupCA_system(models, ourShader2);



	while (!glfwWindowShouldClose(window))
	{
		//fpsObj.calculate();

		myCamera.processTimeBetweenLastFrameAndCurrentFrame();
		processInput(window);
		clearFuncitons();

		glm::mat4 projection = glm::perspective(glm::radians(myCamera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 1000.0f);
		glm::mat4 view = myCamera.GetViewMatrix();


		gameOfLifeObj.draw(projection, view);

		glFlush();
		glfwPollEvents();



	}




	glfwTerminate();
	return 0;
}


void  faceCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
}



void clearFuncitons() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.ProcessKeyboard(FORWARD);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.ProcessKeyboard(BACKWARD);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.ProcessKeyboard(LEFT);
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.ProcessKeyboard(RIGHT);

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		myCamera.ProcessKeyboard(UP);
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		myCamera.ProcessKeyboard(DOWN);


	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		gameOfLifeObj.speed_FPS = gameOfLifeObj.speed_FPS + 1;
	else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		if (gameOfLifeObj.speed_FPS > 1)gameOfLifeObj.speed_FPS = gameOfLifeObj.speed_FPS - 1;

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void zBuffer(bool onOff) {
	if (onOff)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

static GLFWwindow* myWindowInit() {
	if (!glfwInit()) {
		std::cerr << "GLFW fail to be initialized" << '\n';
		exit(-1);
	}

	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);





	GLFWwindow* window = glfwCreateWindow(
		SCR_WIDTH,
		SCR_HEIGHT,
		"mocAf-3D Conway's Game of Life",
		NULL, NULL);
	if (!window)
	{
		std::cerr << "glfw terminated" << '\n';
		glfwTerminate();
		exit(-1);
	}


	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, window_resized);
	myCamera.glfwSetFuntions(window);

	glfwSwapInterval(1);


	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "glew terminated " << glewGetErrorString(err) << '\n';
		glfwTerminate();
		exit(-1);
	}


	std::cout << glGetString(GL_VERSION) << '\n';


	int nr_extensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nr_extensions);

	for (int i = 0; i < nr_extensions; ++i) {
		std::cout << glGetStringi(GL_EXTENSIONS, i) << '\n';
	}

	return window;
}
void show_glfw_error(int error, const char* description) {
	std::cerr << "Error: " << description << '\n';
}
void window_resized(GLFWwindow* window, int width, int height) {
	std::cout << "Window resized, new window size: " << width << " x " << height << '\n';

	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

