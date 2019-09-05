#include "FPS_counter.h"

FPS_counter::FPS_counter(void)
{
	lastTime = glfwGetTime();
	nbFrames = 0;
	currentTime = 0;
}

FPS_counter::~FPS_counter(void) {}

void FPS_counter::calculate()
{
	currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) {
		system("CLS");
		std::cout << nbFrames / (currentTime - lastTime) << " FPS" << std::endl;
		nbFrames = 0;
		lastTime = currentTime;
	}
}

