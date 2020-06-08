#include "IntMatrix.h"

mtm::IntMatrix::IntMatrix(Dimensions dims, int initVal)
	: this->dims(dims)
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

mtm::IntMatrix::IntMatrix(const IntMatrix& matrix)
	: this->matrix(new int*[matrix.dims.getRow()]), this->dims(matrix.dims)
{
	for (int i = 0; i < dims.getRow(); i++)
	{
		this->matrix[i] = new int[dims.getCol()];
	}

	for (int i = 0; i < dims.getRow(); i++) 
	{
		for (int j = 0; j < dims.getCol(); j++) 
		{
			matrix[i][j] = matrix[i][j];
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

static IntMatrix mtm::IntMatrix::Identity(int size)
{
	Dimensions identityDims(size, size);
	IntMatrix identity(identityDims);

	for (int i = 0; i < dims.getRow(); i++)
	{
		identity[i][i] = 1;
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
			transposedMatrix[j][i] = matrix[i][j];
		}
	}
}

IntMatrix mtm::IntMatrix::operator+(const IntMatrix& matrix) const;
{
	IntMatrix result(*this);

	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); j++)
		{
			result[i][j] += matrix[i][j];
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