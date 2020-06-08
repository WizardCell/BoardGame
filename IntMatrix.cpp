#include "IntMatrix.h"

mtm::IntMatrix::IntMatrix(Dimensions dims, int initVal)
	: dims(dims.getRow(),dims.getCol())
{
	this->matrix = new int*[dims.getRow()];
	for (int i = 0; i < dims.getRow(); i++)
	{
		this->matrix[i] = new int[dims.getCol()];
	}

	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); j++)
		{
			matrix[i][j] = initVal;
		}
	}
}

mtm::IntMatrix::IntMatrix(const IntMatrix& matrix1)
	:  dims(dims.getRow(),dims.getCol())
{
	matrix = new int*[dims.getRow()];
	for(int i = 0; i < dims.getRow(); i++)
	{
		matrix[i] = new int[dims.getCol()];
	}
    for ( int i=0; i<dims.getRow();i++){
        for ( int j=0; j<dims.getCol();j++){
            matrix[i][j] = matrix1.matrix[i][j];
        }
    }
}

mtm::IntMatrix::~IntMatrix()
{
	for (int i = 0; i < dims.getRow(); i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}

IntMatrix mtm::IntMatrix::Identity(int size)
{
	Dimensions identityDims(size, size);
	IntMatrix identity(identityDims);

	for (int i = 0; i < identityDims.getRow(); i++)
	{
		identity.matrix[i][i] = 1;
	}
}

IntMatrix mtm::IntMatrix::transpose() const
{
	Dimensions(dims.getCol(), dims.getRow());
	IntMatrix transposedMatrix(dims);

	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); i++)
		{
			transposedMatrix.matrix[j][i] = matrix[i][j];
		}
	}
}

IntMatrix mtm::operator+(const IntMatrix& matrix1, const IntMatrix& matrix2)
{
	IntMatrix result(matrix1.dims);

	for (int i = 0; i < matrix1.dims.getRow(); i++)
	{
		for (int j = 0; j < matrix1.dims.getCol(); j++)
		{
			result.matrix[i][j]= matrix1.matrix[i][j] + matrix2.matrix[i][j];
		}
	}

	return result;
}

IntMatrix mtm::IntMatrix::operator-() const
{
	IntMatrix result(*this);

	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); j++)
		{
			result[i][j] *= -1;
		}
	}

	return result;
}

IntMatrix mtm::IntMatrix::operator-(const IntMatrix& matrix) const
{
	return *this - matrix;
}

mtm::IntMatrix& mtm::IntMatrix::operator=(const IntMatrix& m)
{
	if (this == &m)    //checking selfOperator=
	{
		return *this;
	}
	for (int i = 0; i < dim.getRow(); i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	dims = m.dims;       //deafult = for Dimensions
	matrix = new int*[dim.getRow()];
	for (int i = 0; i < dim.getRow(); i++)
	{
		matrix[i] = new int[dim.getCol()];
	}
	for (int i = 0; i < dim.getRow(); i++) {
		for (int j = 0; j < dim.getCol(); j++) {
			matrix[i][j] = m.matrix[i][j];
		}
	}
	return *this;
}