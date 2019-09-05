#pragma once
#include<vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"CellularAutomata_Matrix.h"
#define MAT_N 160
#define MAT_N2 160

class CellularAutomataSystem
{
public:
	CellularAutomataSystem(void);
	~CellularAutomataSystem(void);

	int getValueFromPrevMat(int x, int y);
	bool isThereExactlyThreeAliveCellulsOnNeighbords(int i, int j);
	bool isThereTwoOrThreeAliveCellulsOnNeighbords(int i, int j);
	bool isStateStable();
	void caculateAcctMatrix(glm::mat4* modelMatrices_aliveCells, glm::mat4* modelMatrices_deadCells, unsigned int* amountAliveCells, unsigned int* amountDeadCells);
	void initAllMatrices(unsigned short int dataMapMat_choice);
	void prevMatReceiveAcctMat();
	void prevPrevMatReceivePrevMat();

	unsigned int  getValueFromAcctMat(int i, int j);


	int getAcctMatrix_row_lastJ();

private:
	CellularAutomata_Matrix prevPrevMatrix;
	CellularAutomata_Matrix prevMatrix;
	CellularAutomata_Matrix acctMatrix;



	unsigned int toBeOnfireTimeMat[MAT_N][MAT_N];
	unsigned int OnfireTimeMat[MAT_N][MAT_N];

};

