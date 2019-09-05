#pragma once
#include<vector>
#include<iostream>
#include<stdexcept>
class CellularAutomata_Matrix
{
public:
	CellularAutomata_Matrix(void);
	~CellularAutomata_Matrix(void);
	void initSquaredMatrixAttrib();
	void initNonSquaredMatrixAttrib(unsigned int width_column_lastI, unsigned int height_row_lastJ);
	void insertElement(unsigned int intValue);
	void editElement(unsigned int i, unsigned int j, unsigned int intValue);
	unsigned int getElement(unsigned int i, unsigned int j);
	unsigned int getWidth_column_lastI();
	unsigned int getHeight_row_lastJ();
	unsigned int getMatrixSize();
	void deleteAllElements();
	std::vector <unsigned int> data;

private:

	int matrixSize;
	int width_column_lastI;
	int height_row_lastJ;


};

