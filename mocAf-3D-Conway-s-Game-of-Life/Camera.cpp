#include "Camera.h"



Camera::Camera() {}
Camera::~Camera() {}

void Camera::initAttributes(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float screenWidth, float screenHeight) {
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;

	ConstrainPitch = true;
	firstMouse = true;

	lastX = screenWidth / 2.0f;
	lastY = screenHeight / 2.0f;


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	MovementSpeed = 3.5f;
	MouseSensitivity = 0.1f;
	Zoom = 45.0f;
	updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	if (direction == UP)
		Position -= Up * velocity;
	if (direction == DOWN)
		Position += Up * velocity;
}
void Camera::processTimeBetweenLastFrameAndCurrentFrame()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}


void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}



void Camera::glfwSetFuntions(GLFWwindow* window) {

	GLFWCallbackWrapper::SetSubCamera(this);
	glfwSetCursorPosCallback(window, GLFWCallbackWrapper::MousePositionCallback);
	glfwSetScrollCallback(window, GLFWCallbackWrapper::ScrollPositionCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (ConstrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();

}
void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;

}


void Camera::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double positionX, double positionY)
{
	s_application->mouse_callback(window, positionX, positionY);
}
void Camera::GLFWCallbackWrapper::ScrollPositionCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	s_application->scroll_callback(window, xoffset, yoffset);
}



void Camera::GLFWCallbackWrapper::SetSubCamera(Camera* camera)
{
	GLFWCallbackWrapper::s_application = camera;
}

Camera* Camera::GLFWCallbackWrapper::s_application = nullptr;


