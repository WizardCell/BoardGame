#include "IntMatrix.h"
#include <assert.h>

/* IntMatrix class */

mtm::IntMatrix::IntMatrix(Dimensions dims, int initVal)
	: dims(dims.getRow(), dims.getCol())
{
	array2D = new int*[dims.getRow()];
	for (int i = 0; i < dims.getRow(); i++)
	{
		array2D[i] = new int[dims.getCol()];
	}

	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); j++)
		{
			array2D[i][j] = initVal;
		}
	}
}

mtm::IntMatrix::IntMatrix(const IntMatrix& other)
	: dims(other.dims.getRow(), other.dims.getCol())
{
	array2D = new int*[dims.getRow()];
	for (int i = 0; i < dims.getRow(); i++)
	{
		array2D[i] = new int[dims.getCol()];
	}
	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); j++)
		{
			array2D[i][j] = other.array2D[i][j];
		}
	}
}

mtm::IntMatrix::~IntMatrix()
{
	for (int i = 0; i < dims.getRow(); i++)
	{
		delete[] array2D[i];
	}
	delete[] array2D;
}

mtm::IntMatrix::iterator mtm::IntMatrix::begin()
{
	return iterator(this, dims, 0);
}

mtm::IntMatrix::iterator mtm::IntMatrix::end()
{
	return iterator(this, dims, this->size());
}

mtm::IntMatrix::const_iterator mtm::IntMatrix::begin() const
{
	return const_iterator(this, dims, 0);
}

mtm::IntMatrix::const_iterator mtm::IntMatrix::end() const
{
	return const_iterator(this, dims, this->size());
}


mtm::IntMatrix mtm::IntMatrix::Identity(int size)
{
	Dimensions identityDims(size, size);
	IntMatrix identity(identityDims);

	for (int i = 0; i < identityDims.getRow(); i++)
	{
		identity.array2D[i][i] = 1;
	}
	return identity;
}

mtm::IntMatrix mtm::IntMatrix::transpose() const
{
	Dimensions dim(dims.getCol(), dims.getRow());
	IntMatrix transposedMatrix(dim);

	for (int i = 0; i < dims.getCol(); i++)
	{
		for (int j = 0; j < dims.getRow(); j++)
		{
			transposedMatrix.array2D[i][j] = array2D[j][i];
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
			result.array2D[i][j] = matrix1.array2D[i][j] + matrix2.array2D[i][j];
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
			result.array2D[i][j] *= -1;
		}
	}
	return result;
}

mtm::IntMatrix mtm::IntMatrix::operator-(const IntMatrix& matrix) const
{
	return operator+(*this, -matrix);
}

mtm::IntMatrix& mtm::IntMatrix::operator=(const IntMatrix& other)
{
	if (this == &other)    //checking selfOperator=
	{
		return *this;
	}

	for (int i = 0; i < dims.getRow(); i++)
	{
		delete[] this->array2D[i];
	}
	delete[] this->array2D;

	dims = other.dims;
	array2D = new int*[dims.getRow()];

	for (int i = 0; i < dims.getRow(); i++)
	{
		array2D[i] = new int[dims.getCol()];
	}

	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); j++)
		{
			array2D[i][j] = other.array2D[i][j];
		}
	}
	return *this;
}


mtm::IntMatrix& mtm::IntMatrix::operator+=(int number)
{
	for (int i = 0; i < dims.getRow(); i++)
	{
		for (int j = 0; j < dims.getCol(); j++)
		{
			array2D[i][j] += number;
		}
	}
	return (*this);
}

mtm::IntMatrix mtm::operator+(const IntMatrix& matrix, int number)
{
	return IntMatrix(matrix) += number;
}

mtm::IntMatrix mtm::operator+(int number, const IntMatrix& matrix)
{
	return (matrix + number);
}

std::ostream& mtm::operator<<(std::ostream& os, const mtm::IntMatrix matrix)
{
	int col = matrix.dims.getCol();
	int row = matrix.dims.getRow();

	int* matrix_values = new int[matrix.size()];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix_values[i*col + j] = matrix.array2D[i][j];
		}
	}

	std::string str = printMatrix(matrix_values, matrix.dims);
	delete[] matrix_values;
	return os << str;
}

int& mtm::IntMatrix::operator()(int i, int j)
{
	return array2D[i][j];
}

const int& mtm::IntMatrix::operator()(int i, int j) const
{
	return array2D[i][j];
}



bool mtm::bigger(int a, int b)
{
	return a > b;
}
bool mtm::min(int a, int b)
{
	return a < b;
}
bool mtm::biggerEqual(int a, int b)
{
	return a >= b;
}
bool mtm::minEqual(int a, int b)
{
	return a <= b;
}
bool mtm::isEqual(int a, int b)
{
	return a == b;
}
bool mtm::notEqual(int a, int b)
{
	return a != b;
}

mtm::IntMatrix mtm::IntMatrix::operator<(int number)
{
	return requiredMatrix(*this, min, number);
}

mtm::IntMatrix mtm::IntMatrix::operator<=(int number)
{
	return requiredMatrix(*this, minEqual, number);
}

mtm::IntMatrix mtm::IntMatrix::operator>=(int number)
{
	return requiredMatrix(*this, biggerEqual, number);
}

mtm::IntMatrix mtm::IntMatrix::operator>(int number)
{
	return requiredMatrix(*this, bigger, number);
}

mtm::IntMatrix mtm::IntMatrix::operator==(int number)
{
	return requiredMatrix(*this, isEqual, number);
}

mtm::IntMatrix mtm::IntMatrix::operator!=(int number)
{
	return requiredMatrix(*this, notEqual, number);
}


//Helper function do the comparison according to the compare function
mtm::IntMatrix mtm::IntMatrix::requiredMatrix(mtm::IntMatrix matrix, bool(*compare)(int, int), int number)
{
	mtm::IntMatrix result(matrix.dims);

	for (int i = 0; i < matrix.dims.getRow(); i++)
	{
		for (int j = 0; j < matrix.dims.getCol(); j++)
		{
			if (compare(matrix.array2D[i][j], number))
			{
				result(i, j) = 1;  //operator()
			}
			else
			{
				result(i, j) = 0;
			}
		}
	}
	return result;
}

bool mtm::all(IntMatrix matrix)
{
	for (int i = 0; i < matrix.dims.getRow(); i++)
	{
		for (int j = 0; j < matrix.dims.getCol(); j++)
		{
			if (matrix(i, j) == 0)
				return false;
		}
	}
	return true;
}

bool mtm::any(IntMatrix matrix)
{
	for (int i = 0; i < matrix.dims.getRow(); i++)
	{
		for (int j = 0; j < matrix.dims.getCol(); j++)
		{
			if (matrix(i, j) != 0)
				return true;
		}
	}
	return false;
}


/* Non-Constant iterator class */

mtm::IntMatrix::iterator::iterator(IntMatrix* matrix, const Dimensions dims, int index)
	: matrix(matrix), dims(dims), index(index)
{}

int& mtm::IntMatrix::iterator::operator*() const
{
	assert(index >= 0 && index < matrix->size());
	int col = dims.getCol();
	return matrix->array2D[(int)index / col][index%col];
}

mtm::IntMatrix::iterator& mtm::IntMatrix::iterator::operator++()
{
	++index;
	return *this;
}

mtm::IntMatrix::iterator mtm::IntMatrix::iterator::operator++(int)
{
	iterator result = *this;
	++*this;
	return result;
}

bool mtm::IntMatrix::iterator::operator==(const iterator& it) const
{
	assert(this->matrix == it.matrix);
	return this->index == it.index;
}

bool mtm::IntMatrix::iterator::operator!=(const iterator& it) const
{
	return !(*this == it);
}


/* Constant iterator class */

mtm::IntMatrix::const_iterator::const_iterator(const IntMatrix* matrix, const Dimensions dims, int index)
	: matrix(matrix), dims(dims), index(index)
{}

const int& mtm::IntMatrix::const_iterator::operator*() const
{
	assert(index >= 0 && index < matrix->size());
	int col = dims.getCol();
	return matrix->array2D[(int)index / col][index % col];
}

mtm::IntMatrix::const_iterator& mtm::IntMatrix::const_iterator::operator++()
{
	++index;
	return *this;
}

mtm::IntMatrix::const_iterator mtm::IntMatrix::const_iterator::operator++(int)
{
	const_iterator result = *this;
	++*this;
	return result;
}

bool mtm::IntMatrix::const_iterator::operator==(const const_iterator& it) const
{
	assert(this->matrix == it.matrix);
	return this->index == it.index;
}

bool mtm::IntMatrix::const_iterator::operator!=(const const_iterator& it) const
{
	return !(*this == it);
}

