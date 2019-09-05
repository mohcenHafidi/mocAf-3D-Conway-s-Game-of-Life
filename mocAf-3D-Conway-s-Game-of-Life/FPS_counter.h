#pragma once
#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include<iostream>
class FPS_counter
{
public:


	FPS_counter(void);
	~FPS_counter(void);
	void calculate();

private:
	double lastTime;
	int nbFrames;

	double currentTime;

};

