#include "CA_gameOfLife.h"


CA_gameOfLife::CA_gameOfLife(unsigned short matrixChoice) {
	amountAliveCells = 0;
	amountDeadCells = 0;
	speed_FPS = 100;
	drawOnlyTimes = speed_FPS;
	ca_systemObj.initAllMatrices(matrixChoice);
	stateStablized = false;
	generations_counter = 0;
}

CA_gameOfLife::~CA_gameOfLife(void) {}

unsigned int  CA_gameOfLife::configureInstancedArrayBuffer(unsigned int amount, glm::mat4* modelMatrices)
{
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
	return buffer;
}

void CA_gameOfLife::configureAttribParam(Model model)
{
	for (unsigned int i = 0; i < model.meshes.size(); i++)
	{
		unsigned int VAO = model.meshes[i].VAO;
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		
	}
}

glm::mat4* CA_gameOfLife::create_modelMatrices(unsigned int amount)
{
	glm::mat4* modelMatrices = new glm::mat4[amount * amount];

	for (unsigned int i = 0; i < amount * amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, 0));
		modelMatrices[i] = model;
	}

	return modelMatrices;
}

void CA_gameOfLife::copyDataToInstancedArray(unsigned int buffer, glm::mat4* modelMatrices, unsigned int amount)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(ptr, &modelMatrices[0], amount * sizeof(glm::mat4));
	glUnmapBuffer(GL_ARRAY_BUFFER);

}

void CA_gameOfLife::renderModel(Model model, unsigned int amount)
{
	for (unsigned int i = 0; i < model.meshes.size(); i++)
	{
		glBindVertexArray(model.meshes[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, model.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
		
	}
}


void CA_gameOfLife::draw(glm::mat4 projection, glm::mat4 view) {

	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.ModelTranslation(0.0f, 0.0f, 0.0f);

	shader.setInt("texture_diffuse1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, models.at(0).textures_loaded[0].id);


	drawOnlyTimes++;


	if (drawOnlyTimes > speed_FPS) {

		amountAliveCells = 0;
		amountDeadCells = 0;



		ca_systemObj.caculateAcctMatrix(&modelMatrices_aliveCells[0], &modelMatrices_deadCells[0], &amountAliveCells, &amountDeadCells);

		if (!stateStablized) {
			system("CLS");
			stateStablized = ca_systemObj.isStateStable();
			cout << "State stabilized (1:True 0:False) = " << stateStablized << endl;
			if (stateStablized)
				cout << " Generation at  :" << generations_counter << endl;
			else {
				cout << "Generation at  :     " << generations_counter++ << endl;
				ca_systemObj.prevPrevMatReceivePrevMat();
			}
		}
		ca_systemObj.prevMatReceiveAcctMat();



		drawOnlyTimes = 0;
	}

	copyDataToInstancedArray(buffer_aliveCells, &modelMatrices_aliveCells[0], amountAliveCells);
	copyDataToInstancedArray(buffer_deadCells, &modelMatrices_deadCells[0], amountDeadCells);


	renderModel(models.at(0), amountAliveCells);

	renderModel(models.at(1), amountDeadCells);





}

void CA_gameOfLife::setupCA_system(vector<Model> models, Shader shader)
{
	this->models = models;
	this->shader = shader;
	unsigned int amount = ca_systemObj.getAcctMatrix_row_lastJ();

	modelMatrices_aliveCells = create_modelMatrices(amount);
	buffer_aliveCells = configureInstancedArrayBuffer(amount, &modelMatrices_aliveCells[0]);
	configureAttribParam(models.at(0));



	modelMatrices_deadCells = create_modelMatrices(amount);
	buffer_deadCells = configureInstancedArrayBuffer(amount, &modelMatrices_deadCells[0]);
	configureAttribParam(models.at(1));




}


void CA_gameOfLife::changePositions() {
	copyDataToInstancedArray(buffer_aliveCells, &modelMatrices_aliveCells[0], amountAliveCells);
	copyDataToInstancedArray(buffer_deadCells, &modelMatrices_deadCells[0], amountDeadCells);

}




