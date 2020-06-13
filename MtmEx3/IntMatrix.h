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

		//TODO: shouldn't be a public function?
		static IntMatrix requiredMatrix(IntMatrix matrix, bool(*compare)(int, int), int number);

	public:
		/* Iterator class*/
		class Iterator;

		Iterator begin() const;
		Iterator end() const;

	public:
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

		friend std::ostream& operator<<(std::ostream& os, const IntMatrix& matrix);

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
	std::ostream& operator<<(std::ostream& os, const IntMatrix& matrix);

	/* simple logic functions */
	bool all(IntMatrix matrix);
	bool any(IntMatrix matrix);
	bool bigger(int a, int b);
	bool biggerEqual(int a, int b);
	bool min(int a, int b);
	bool minEqual(int a, int b);
	bool isEqual(int a, int b);
	bool notEqual(int a, int b);

	class IntMatrix::Iterator
	{
		const IntMatrix* matrix;
		const Dimensions dims;
		int index;
		Iterator(const IntMatrix* matrix, const Dimensions dims, int index);
		friend class IntMatrix;

	public:
		const int& operator*() const;
		Iterator& operator++();
		Iterator operator++(int);
		bool operator==(const Iterator& it) const;
		bool operator!=(const Iterator& it) const;
		Iterator(const Iterator&) = default;
		Iterator& operator=(const Iterator&) = default;
		~Iterator();


	};

}


#endif //EX3_INTMATRIX_H