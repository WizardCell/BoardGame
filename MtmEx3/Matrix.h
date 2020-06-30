#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"

/*simple logic generic functions */
template<class T>
bool bigger(T a, T b)
{
	return a > b;
}

template<class T>
bool biggerEqual(T a, T b)
{
	return a >= b;
}

template<class T>
bool min(T a, T b)
{
	return a < b;
}

template<class T>
bool minEqual(T a, T b)
{
	return a <= b;
}

template<class T>
bool isEqual(T a, T b)
{
	return a == b;
}

template<class T>
bool notEqual(T a, T b)
{
	return a != b;
}
// end logic functions // 


namespace mtm
{
	template<class T>
	class Matrix
	{
	private:
		T** array2D;
		Dimensions dims;

	public:
		bool isWithinLimits(const GridPoint point) const;

	private:
		// helper function for comparing according to compare function.
		// we assume that T is comparable.
		static Matrix<bool> requiredMatrix(Matrix matrix, bool(*compare)(T, T), T value)
		{
			Matrix<bool> result(matrix.dims);

			for (int i = 0; i < matrix.dims.getRow(); i++)
			{
				for (int j = 0; j < matrix.dims.getCol(); j++)
				{
					if (compare(matrix.array2D[i][j], value))
					{
						result(i, j) = true;  //operator()
					}
					else
					{
						result(i, j) = false;
					}
				}
			}
			return result;
		}

	public:
		/* The Exceptions Classes First */
		class AccessIllegalElement
		{
		public:
			std::string what() const
			{
				std::string errorString = "Mtm matrix error: An attempt to access an illegal element";
				return errorString;
			}
		};

		class IllegalInitialization
		{
		public:
			std::string what() const
			{
				std::string errorString = "Mtm matrix error: Illegal initialization values";
				return errorString;
			}

		};

		class DimensionMismatch
		{
			Dimensions left_dims;
			Dimensions right_dims;
		public:
			DimensionMismatch(mtm::Dimensions left_dim, mtm::Dimensions right_dim) :
				left_dims(left_dim), right_dims(right_dim) {}
			std::string what() const
			{
				std::string errorString = "Mtm matrix error: Dimension mismatch: ";
				return errorString += left_dims.toString() + " " + right_dims.toString();
			}
		};

		/* End of the exception classes */

		//constructor
		Matrix(Dimensions dim, T value = T()) : dims(dim.getRow(), dim.getCol())
		{

			if (dim.getRow() <= 0 || dim.getCol() <= 0)
			{
				throw IllegalInitialization();
			}

			array2D = new T*[dims.getRow()];
			int counter = 0;

			try
			{
				for (int i = 0; i < dims.getRow(); i++)
				{
					array2D[i] = new T[dims.getCol()];
					counter++;
				}
			}
			catch (const std::bad_alloc& e)  // here means an allocation failed. we need to free the ones we allocated.
			{
				for (int i = 0; i < counter; i++)
				{
					delete[] array2D[i];
				}
				delete[] array2D;
				throw e;
			}

			try // in case operator = for the T fails
			{
				for (int i = 0; i < dims.getRow(); i++)
				{
					for (int j = 0; j < dims.getCol(); j++)
					{
						array2D[i][j] = value;
					}
				}
			}
			catch (...)
			{
				for (int i = 0; i < dim.getRow(); i++)
				{
					delete[] array2D[i];
				}
				delete[]  array2D;
				throw;
			}
		}
		//copy constructor
		//we assume that T has operator= and default constructor
		Matrix(const Matrix& other) : dims(other.dims.getRow(), other.dims.getCol())
		{
			array2D = new T*[dims.getRow()];
			int counter = 0;

			try
			{
				for (int i = 0; i < dims.getRow(); i++)
				{
					array2D[i] = new T[dims.getCol()];
					counter++;
				}
			}
			catch (const std::bad_alloc& e)
			{
				for (int i = 0; i < counter; i++)
				{
					delete[] array2D[i];
				}
				delete[] array2D;
				throw e;
			}

			try
			{
				for (int i = 0; i < dims.getRow(); i++)
				{
					for (int j = 0; j < dims.getCol(); j++)
					{
						array2D[i][j] = other.array2D[i][j];    //assuming that T has operator = 
					}
				}
			}
			catch (...)
			{
				for (int i = 0; i < dims.getRow(); i++)
				{
					delete[] array2D[i];
				}
				delete[]  array2D;
				throw;
			}


		}

		//destructor
		~Matrix()
		{
			for (int i = 0; i < dims.getRow(); i++)
			{
				delete[] array2D[i];
			}
			delete[] array2D;

		}

		// operator = 
		// changing this object values to the @param values
		// assuming that T has the constructor with no params, and T has operator =
		Matrix& operator=(const Matrix& matrix)
		{
			T** temp = new T*[matrix.dims.getRow()];
			int counter = 0;

			try
			{
				for (int i = 0; i < matrix.dims.getRow(); i++)
				{
					temp[i] = new T[matrix.dims.getCol()];
					counter++;
				}
			}
			catch (const std::bad_alloc& e)
			{
				for (int i = 0; i < counter; i++)
				{
					delete[] temp[i];
				}
				delete[] temp;
				throw e;
			}

			try
			{
				for (int i = 0; i < matrix.dims.getRow(); i++)
				{
					for (int j = 0; j < matrix.dims.getCol(); j++)
					{
						temp[i][j] = matrix.array2D[i][j];
					}
				}
			}
			catch (...)
			{
				for (int i = 0; i < matrix.dims.getRow(); i++)
				{
					delete[] temp[i];
				}
				delete[]  temp;
				throw;
			}
			delete[]  array2D; //from this point nothing can fail
			array2D = temp;
			dims = matrix.dims;
			return (*this);
		}

		// creating diagonal matrix 
		// the diagonal is filled with the value, anywhere else with the default constructor.
		// we assume that T has the default constructor and operator =
		static Matrix Diagonal(int dim, T value)
		{
			if (dim <= 0)
			{
				throw IllegalInitialization();
			}
			Dimensions new_dim(dim, dim);
			Matrix<T> matrix(new_dim);

			for (int i = 0; i < dim; i++)
			{
				matrix.array2D[i][i] = value;
			}
			return matrix;
		}

		/*simple functions */
		int height() const
		{
			return this->dims.getRow();
		}

		int width() const
		{
			return this->dims.getCol();
		}

		int size() const
		{
			return height() * width();
		}

		// transpose function
		// doing transpose to the matrix without changing the given one.
		// assuming that T has default cons' and operator =
		Matrix transpose() const
		{
			Dimensions dim(dims.getCol(), dims.getRow());
			Matrix transposedMatrix(dim);

			for (int i = 0; i < dims.getCol(); i++)
			{
				for (int j = 0; j < dims.getRow(); j++)
				{
					transposedMatrix.array2D[i][j] = array2D[j][i];
				}
			}
			return transposedMatrix;
		}



		// operator - unary
		// we assume that T has - unary;
		Matrix operator-() const
		{
			Matrix result(*this);

			for (int i = 0; i < dims.getRow(); i++)
			{
				for (int j = 0; j < dims.getCol(); j++)
				{
					result.array2D[i][j] = -result.array2D[i][j];
				}
			}
			return result;
		}

		//operator - binary
		// we assume that T has  - binary;
		Matrix operator-(const Matrix& matrix) const
		{
			if (this->dims != matrix.dims)
			{
				Dimensions left_dim(this->height(), this->width());
				Dimensions right_dim(matrix.height(), matrix.width());
				throw DimensionMismatch(left_dim, right_dim);
			}
			return operator+(*this, -matrix);
		}

		//operator +=
		// we assume that T has +=
		Matrix& operator+=(T value)
		{
			for (int i = 0; i < dims.getRow(); i++)
			{
				for (int j = 0; j < dims.getCol(); j++)
				{
					array2D[i][j] += value;
				}
			}
			return (*this);
		}

		//Operator () , for const and non const matrixes
		//No assumption on T
		T& operator()(int i, int j)
		{
			if (i < 0 or i >= this->height() or j < 0 or j >= this->width())
			{
				throw AccessIllegalElement();
			}
			return array2D[i][j];
		}

		//The const version 
		const T& operator()(int i, int j) const
		{
			if (i < 0 or i >= this->height() or j < 0 or j >= this->width())
			{
				throw AccessIllegalElement();
			}
			return array2D[i][j];
		}


		/* The logic functions */
		// Assuming that T has the the logic functions.
		Matrix<bool> operator<(T value)
		{
			return requiredMatrix(*this, min, value);
		}
		Matrix<bool> operator<=(T value)
		{
			return requiredMatrix(*this, minEqual, value);
		}
		Matrix<bool> operator==(T value)
		{
			return requiredMatrix(*this, isEqual, value);
		}
		Matrix<bool> operator!=(T value)
		{
			return requiredMatrix(*this, notEqual, value);
		}
		Matrix<bool> operator>(T value)
		{
			return requiredMatrix(*this, bigger, value);
		}
		Matrix<bool> operator>=(T value)
		{
			return requiredMatrix(*this, biggerEqual, value);
		}
		//  end of logic functions  //

		/* Iterator class*/
		class iterator;
		iterator begin();
		iterator end();

		/* const iterator class */
		class const_iterator;
		const_iterator begin() const   //const_iterator to the first element in the matrix
		{
			return const_iterator(this, dims, 0);
		}
		const_iterator end() const    //const_itertor to the last elemnt in the matrix
		{
			return const_iterator(this, dims, this->size());
		}


		// apply the functor on the matrix and return updated function.
		// we assume that the functor take T return T , and T has operator=
		template<class U>
		Matrix apply(U functor) const
		{
			Matrix result(*this);
			for (int i = 0; i < dims.getRow(); i++)
			{
				for (int j = 0; j < dims.getCol(); j++)
				{
					result(i, j) = functor((*this)(i, j));
				}

			}
			return result;

		}

	};
	/* End of Matrix<T> class */

	// Check if param @point is within matrix limits
	template <class T>
	bool Matrix<T>::isWithinLimits(const GridPoint point) const
	{
		return point.col >= 0 && point.col < width() && point.row >= 0 && point.row < height();
	}

	// operator + 
	// we assume that T has operator + and operator =
	template<class T>
	mtm::Matrix<T> operator+(const mtm::Matrix<T>& matrix1, const mtm::Matrix<T>& matrix2)
	{

		if (matrix1.width() != matrix2.width() || matrix1.height() != matrix2.height())
		{
			Dimensions left_dim(matrix1.height(), matrix1.width());
			Dimensions right_dim(matrix2.height(), matrix2.width());
			throw typename mtm::Matrix<T>::DimensionMismatch(left_dim, right_dim);
		}
		Dimensions new_dim(matrix1.height(), matrix1.width());
		mtm::Matrix<T> result(new_dim);

		for (int i = 0; i < matrix1.height(); i++)
		{
			for (int j = 0; j < matrix1.width(); j++)
			{
				result(i, j) = matrix1(i, j) + matrix2(i, j);
			}
		}
		return result;
	}

	// operator +  with T value
	// we assume that T has operator += 
	template<class T>
	Matrix<T> operator+(const Matrix<T>& matrix, T value)
	{
		return Matrix<T>(matrix) += value;
	}

	// we assume that T has operator +
	template<class T>
	Matrix<T> operator+(T value, const Matrix<T>& matrix)
	{
		Matrix<T> temp_mat(matrix);
		for (int i = 0; i < matrix.height(); i++)
			{
				for (int j = 0; j < matrix.width(); j++)
				{
					temp_mat(i,j) = value + temp_mat(i,j) ;
				}
			}
			return (temp_mat);
	}
	/* end of operator + */


	template<class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<T> matrix)
	{
		typename mtm::Matrix<T>::const_iterator it_begin = matrix.begin();
		typename mtm::Matrix<T>::const_iterator it_end = matrix.end();
		return printMatrix(os, it_begin, it_end, matrix.width());
	}


	// all function
	// return false if one of the matrix's value is false
	// we assume that T has casting to boolean
	template<class T>
	bool all(Matrix<T> matrix)
	{
		for (int i = 0; i < matrix.height(); i++)
		{
			for (int j = 0; j < matrix.width(); j++)
			{
				if (matrix(i, j) == false)
					return false;
			}
		}
		return true;
	}

	// any function
	// return true if at least one of the matrix's value is not false
	// we assume that T has casting to boolean
	template<class T>
	bool any(Matrix<T> matrix)
	{
		for (int i = 0; i < matrix.height(); i++)
		{
			for (int j = 0; j < matrix.width(); j++)
			{
				if (matrix(i, j) != false)
					return true;
			}
		}
		return false;
	}

	template<class T>
	typename Matrix<T>::iterator Matrix<T>::begin()
	{
		return iterator(this, dims, 0);
	}

	template<class T>
	typename Matrix<T>::iterator Matrix<T>::end()
	{
		return iterator(this, dims, this->size());
	}


	/* Iterator class */
	template<class T>
	class Matrix<T>::iterator
	{
		Matrix<T>* matrix;
		Dimensions dims;
		int index;
		iterator(Matrix* matrix, const Dimensions dims, int index)
			: matrix(matrix), dims(dims), index(index)
		{}

		friend class Matrix<T>;

	public:
		T& operator*() const
		{
			if (index < 0 or index > matrix->size()  or *this == this->matrix->end())
			{
				throw mtm::Matrix<T>::AccessIllegalElement();
			}
			int col = dims.getCol();
			return matrix->array2D[(int)index / col][index % col];
		}

		iterator& operator++()
		{
			++index;
			return *this;
		}

		iterator operator++(int)
		{
			iterator result = *this;
			++*this;
			return result;
		}

		bool operator==(const iterator& it) const
		{
			return this->index == it.index;
		}

		bool operator!=(const iterator& it) const
		{
			return !(*this == it);
		}

		iterator(const iterator&) = default;
		iterator& operator=(const iterator&) = default;
		~iterator() = default;

	}; // end of class iterator

	/* class const iterator */
	template<class T>
	class Matrix<T>::const_iterator
	{
		const Matrix<T>* matrix;
		Dimensions dims;
		int index;
		const_iterator(const Matrix* matrix, const Dimensions dims, int index)
			: matrix(matrix), dims(dims), index(index)
		{}
		friend class Matrix<T>;

	public:
		const T& operator*() const
		{
			if (index < 0 or index > matrix->size() or *this == this->matrix->end())
			{
				throw mtm::Matrix<T>::AccessIllegalElement();
			}
			int col = dims.getCol();
			return matrix->array2D[(int)index / col][index % col];
		}
		const_iterator& operator++()
		{
			++index;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator result = *this;
			++*this;
			return result;
		}
		bool operator==(const const_iterator& it) const
		{
			return this->index == it.index;
		}
		bool operator!=(const const_iterator& it) const
		{
			return !(*this == it);
		}
		const_iterator(const const_iterator&) = default;
		const_iterator& operator=(const const_iterator&) = default;
		~const_iterator() = default;
	};


} // namespace mtm

#endif 