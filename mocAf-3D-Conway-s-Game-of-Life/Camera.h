#pragma once
#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	Camera();
	~Camera(void);
	void initAttributes(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float screenWidth, float screenHeight);

	void glfwSetFuntions(GLFWwindow* window);
	void ProcessMouseScroll(float yoffset);
	void ProcessKeyboard(Camera_Movement direction);


	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


	void processTimeBetweenLastFrameAndCurrentFrame();
	glm::mat4  GetViewMatrix();
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	bool ConstrainPitch;
	bool firstMouse;

	float lastX;
	float lastY;

	float deltaTime;
	float lastFrame;
	float currentFrame;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
protected:


private:
	void updateCameraVectors();

	class GLFWCallbackWrapper
	{
	public:

		GLFWCallbackWrapper() = delete;
		GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
		GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
		~GLFWCallbackWrapper() = delete;


		static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
		static void ScrollPositionCallback(GLFWwindow* window, double xoffset, double yoffset);

		static void SetSubCamera(Camera* application);
	private:
		static Camera* s_application;

	};



};

