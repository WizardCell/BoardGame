#ifndef EX3_INTMATRIX_H
#define EX3_INTMATRIX_H

#include <string>
#include <iostream>
#include "Auxiliaries.h"

namespace mtm
{
	class IntMatrix
	{
	private:
		int** array2D;
		Dimensions dims;

		static IntMatrix requiredMatrix(IntMatrix matrix, bool(*compare)(int, int), int number);

	public:
		/* Iterator class*/
		class iterator;

		iterator begin();
		iterator end();

		/* const iterator class */
		class const_iterator;
		const_iterator begin() const ;
		const_iterator end() const ;

		IntMatrix(Dimensions dims, int initVal = 0);
		IntMatrix(const IntMatrix& other);
		~IntMatrix();
		static IntMatrix Identity(int size);
		IntMatrix transpose() const;

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

		friend IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
		IntMatrix operator-() const;
		IntMatrix operator-(const IntMatrix& matrix) const;
		IntMatrix& operator=(const IntMatrix& matrix);
		IntMatrix& operator+=(int number);

		friend std::ostream& operator<<(std::ostream& os, const IntMatrix matrix);

		int& operator()(int i, int j);
		const int& operator()(int i, int j) const;

		IntMatrix operator<(int number);
		IntMatrix operator<=(int number);
		IntMatrix operator>(int number);
		IntMatrix operator>=(int number);
		IntMatrix operator==(int number);
		IntMatrix operator!=(int number);

		friend bool all(IntMatrix matrix);
		friend bool any(IntMatrix matrix);
	};

	/* External operator functions used for symmetric behavior */
	IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
	IntMatrix operator+(const IntMatrix& matrix, int number);
	IntMatrix operator+(int number, const IntMatrix& matrix);
	std::ostream& operator<<(std::ostream& os, const IntMatrix matrix);

	/* Simple logic functions */
	bool all(IntMatrix matrix);
	bool any(IntMatrix matrix);
	bool bigger(int a, int b);
	bool biggerEqual(int a, int b);
	bool min(int a, int b);
	bool minEqual(int a, int b);
	bool isEqual(int a, int b);
	bool notEqual(int a, int b);

	/* Non-Const iterator */
	class IntMatrix::iterator
	{
		IntMatrix* matrix;
		Dimensions dims;
		int index;
		iterator(IntMatrix* matrix, const Dimensions dims, int index);
		friend class IntMatrix;

	public:
	    int& operator*() const;
		iterator& operator++();
		iterator operator++(int);
		bool operator==(const iterator& it) const;
		bool operator!=(const iterator& it) const;
		iterator(const iterator&) = default;
		iterator& operator=(const iterator&) = default;
		~iterator() = default;

	};

	/* Constant iterator */
	class IntMatrix::const_iterator 
	{
		const IntMatrix* matrix;     
		const Dimensions dims;
		int index;
		const_iterator(const IntMatrix* matrix, const Dimensions dims, int index);
		friend class IntMatrix;

	public:
	    const int& operator*() const;  
		const_iterator& operator++();
		const_iterator operator++(int);
		bool operator==(const const_iterator& it) const;
		bool operator!=(const const_iterator& it) const;
		const_iterator(const const_iterator&) = default;
		const_iterator& operator=(const const_iterator&) = default;
		~const_iterator() = default;

	};

}


#endif //EX3_INTMATRIX_H