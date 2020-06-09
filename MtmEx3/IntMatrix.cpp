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
	:  dims(matrix1.dims.getRow(),matrix1.dims.getCol())
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

mtm::IntMatrix mtm::IntMatrix::Identity(int size)
{
	Dimensions identityDims(size, size);
	IntMatrix identity(identityDims);

	for (int i = 0; i < identityDims.getRow(); i++)
	{
		identity.matrix[i][i] = 1;
	}
	return identity;
}

mtm::IntMatrix mtm::IntMatrix::transpose() const
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
	return transposedMatrix;
}

mtm::IntMatrix mtm::operator+(const IntMatrix& matrix1, const IntMatrix& matrix2)
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

mtm::IntMatrix mtm::IntMatrix::operator-() const
{
	IntMatrix result(*this);

	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); j++)
		{
			result.matrix[i][j] *= -1;
		}
	}

	return result;
}

mtm::IntMatrix mtm::IntMatrix::operator-(const IntMatrix& matrix) const
{
	return operator+(*this,-matrix);
}

mtm::IntMatrix& mtm::IntMatrix::operator=(const IntMatrix& m)
{
	if (this == &m)    //checking selfOperator=
	{
		return *this;
	}
	for (int i = 0; i < dims.getRow(); i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	dims = m.dims;       //deafult = for Dimensions
	matrix = new int*[dims.getRow()];
	for (int i = 0; i < dims.getRow(); i++)
	{
		matrix[i] = new int[dims.getCol()];
	}
	for (int i = 0; i < dims.getRow(); i++) {
		for (int j = 0; j < dims.getCol(); j++) {
			matrix[i][j] = m.matrix[i][j];
		}
	}
	return *this;
}


mtm::IntMatrix& mtm::IntMatrix::operator+=(int number)
{
	for (int i=0;i<dims.getRow();i++){
		for (int j=0;j<dims.getCol();j++){
			matrix[i][j] += number ;
		}
	}
	return (*this);
}

mtm::IntMatrix  mtm::operator+(const IntMatrix& matrix1, int number)
{
	return IntMatrix(matrix1) += number;
}

mtm::IntMatrix mtm::operator+(int number, const IntMatrix& matrix1)
{
   return (matrix1 + number);
}

std::ostream& mtm::operator<<(std::ostream& os, const mtm::IntMatrix& matrix1)
{
	int col = matrix1.dims.getCol();
	int row = matrix1.dims.getRow();
    int* matrix_values = new int[matrix1.size()];
	for (int i=0;i<row;i++){
		for (int j=0;j<col;j++){
			matrix_values[i*col + j] = matrix1.matrix[i][j];
		}
	}
	std::string str = printMatrix(matrix_values,matrix1.dims);
	return os << str ;
}

