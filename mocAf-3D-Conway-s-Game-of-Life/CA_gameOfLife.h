#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "CellularAutomataSystem.h"
#include "Shader.h"
#include "Model.h"



class CA_gameOfLife
{
public:
	CA_gameOfLife(unsigned short matrixChoice);
	~CA_gameOfLife(void);
	void draw(glm::mat4 projection, glm::mat4 view);
	void setupCA_system(vector<Model> models, Shader shader);

	void changePositions();
	unsigned short speed_FPS;
	unsigned short drawOnlyTimes;

private:
	vector<Model> models;
	Shader shader;
	glm::mat4* modelMatrices_aliveCells;
	glm::mat4* modelMatrices_deadCells;
	unsigned int amountAliveCells;
	unsigned int amountDeadCells;
	unsigned int generations_counter;
	bool stateStablized;
	unsigned int buffer_aliveCells;
	unsigned int buffer_deadCells;
	CellularAutomataSystem ca_systemObj;

	unsigned int configureInstancedArrayBuffer(unsigned int amount, glm::mat4* modelMatrices);
	void configureAttribParam(Model model);

	glm::mat4* create_modelMatrices(unsigned int amount);


	void copyDataToInstancedArray(unsigned int buffer, glm::mat4* modelMatrices, unsigned int amount);
	void renderModel(Model model, unsigned int amount);

};

