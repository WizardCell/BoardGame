#ifndef EX3_INTMATRIX_H
#define EX3_INTMATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"




namespace mtm
{
	class IntMatrix
	{
		int** matrix;
		Dimensions dims;

	public:
		IntMatrix(Dimensions dims, int initVal = 0);
		IntMatrix(const IntMatrix&);
		~IntMatrix();

		static IntMatrix Identity(int size);

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

		IntMatrix transpose() const;

		friend IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
		IntMatrix operator-() const;
		IntMatrix operator-(const IntMatrix& matrix) const;
		IntMatrix& operator=(const IntMatrix& m);
		IntMatrix& operator+=(int number);
	};
	 IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
	 IntMatrix operator+(const IntMatrix& matrix1, int number);
	 IntMatrix operator+(int number, const IntMatrix& matrix1);


}


#endif //EX3_INTMATRIX_H