#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>




class Shader
{
public:
	unsigned int ID;

	Shader(void);

	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const char* name, bool value) const;
	void setInt(const char* name, int value) const;
	void setFloat(const char* name, float value) const;
	void set4Float(const char* name, glm::vec4 vec) const;
	void setMat4(const char* name, glm::mat4 matrix) const;
	void ModelTranslation(float x, float y, float z) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};
#endif