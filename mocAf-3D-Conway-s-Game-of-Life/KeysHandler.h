#pragma once
class KeysHandler
{
public :
	KeysHandler(void);
	~KeysHandler(void);
	void* anyVar;
	void processInput(GLFWwindow* window, Shader shaderProg);
private : 
	float temp;
};

