#include "CellularAutomata_Matrix.h"


CellularAutomata_Matrix::CellularAutomata_Matrix(void) {}
CellularAutomata_Matrix::~CellularAutomata_Matrix(void) {}

void CellularAutomata_Matrix::initNonSquaredMatrixAttrib(unsigned int width_column_lastI, unsigned int height_row_lastJ) {

	this->width_column_lastI = width_column_lastI;
	this->height_row_lastJ = height_row_lastJ;
	this->matrixSize = width_column_lastI * height_row_lastJ;
}

void CellularAutomata_Matrix::insertElement(unsigned int intValue)
{
	data.push_back(intValue);
}

void CellularAutomata_Matrix::editElement(unsigned int i, unsigned int j, unsigned int intValue)
{

	try
	{
		data.at(i + j * width_column_lastI) = intValue;
	}
	catch (std::out_of_range& err)
	{
		std::cout << "index out of bounds CellularAutomata_Matrix class, editElement method !" << std::endl;
	}

}

unsigned int CellularAutomata_Matrix::getElement(unsigned int i, unsigned int j)
{
	return data.at(i + j * width_column_lastI);
}

unsigned int CellularAutomata_Matrix::getWidth_column_lastI()
{
	return width_column_lastI;
}

unsigned int CellularAutomata_Matrix::getHeight_row_lastJ()
{
	return height_row_lastJ;
}

unsigned int CellularAutomata_Matrix::getMatrixSize()
{
	return matrixSize;
}


void CellularAutomata_Matrix::deleteAllElements()
{
	data.clear();
	matrixSize = 0;
	width_column_lastI = 0;
	height_row_lastJ = 0;

}


void CellularAutomata_Matrix::initSquaredMatrixAttrib() {
	this->matrixSize = this->data.size();
	this->width_column_lastI = (unsigned int)sqrt(this->data.size());
	this->height_row_lastJ = width_column_lastI;
}


