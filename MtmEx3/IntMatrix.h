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
		static IntMatrix requiredMatrix(IntMatrix  matrix1, bool (*comp)(int,int),int number);

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
		friend std::ostream& operator<<(std::ostream& os, const IntMatrix& m);
		int& operator()(int i ,int j) ;
		const int& operator()(int i ,int j) const;
		IntMatrix operator<(int number);
		IntMatrix operator<=(int number);
		IntMatrix operator>(int number);
		IntMatrix operator>=(int number);
		IntMatrix operator==(int number);
		IntMatrix operator!=(int number);
		friend bool all(IntMatrix matrix1);
		friend bool any(IntMatrix matrix1);
	};
	 IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
	 IntMatrix operator+(const IntMatrix& matrix1, int number);
	 IntMatrix operator+(int number, const IntMatrix& matrix1);
	 std::ostream& operator<<(std::ostream& os, const IntMatrix& m);
	 bool all(IntMatrix matrix1);
	 bool any(IntMatrix matrix1);
	 bool bigger(int a,int b);
	 bool biggerEqual(int a,int b);
	 bool min(int a,int b);
	 bool minEqual(int a,int b);
	 bool isEqual(int a,int b);
	 bool notEqual(int a,int b);


}


#endif //EX3_INTMATRIX_H