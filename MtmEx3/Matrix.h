#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"


namespace mtm
{
    template<class T>
    class Matrix 
    {
        private:
            T** array2D;
            Dimensions dims;
        public:
            /* The Exceptions Classes First */
            class AccessIllegalElement
            {
                public:
                std::string what()
                {
                    std::string s = "Mtm matrix error: An attempt to access an illegal element";
                    return s;
                }
            };
            class IllegalInitialization
            {
                public:
                std::string what()
                {
                    std::string s = "Mtm matrix error: Illegal initialization values";
                    return s;
                }
               
            };
            class DimensionMismatch
            {
                 //TODO
            };
            /* End of the exception classes */


            Matrix(Dimensions dim, T value = T()): dims(dim.getRow(),dims.getCol())
            {
                if ( dims.getRow() <= 0 || dims.getCol() <=0)
                {
                    throw IllegalInitialization();
                }
                array2D = new T*[dims.getRow()];
	            for (int i = 0; i < dims.getRow(); i++)
	            {
		            array2D[i] = new T[dims.getCol()];
	            }

	            for (int i = 0; i < dims.getRow(); i++)
	            {
		            for (int j = 0; j < dims.getCol(); j++)
		               {
			            array2D[i][j] = value;
		               }
	            }

            }

            Matrix(const Matrix& other) : dims(other.dims.getRow(), other.dims.getCol())
            {
                array2D = new T*[dims.getRow()];
	            for (int i = 0; i < dims.getRow(); i++)
	            {
		            array2D[i] = new T[dims.getCol()];
	            }
	            for (int i = 0; i < dims.getRow(); i++)
	            {
		              for (int j = 0; j < dims.getCol(); j++)
		            {
			            array2D[i][j] = other.array2D[i][j];    //assuming that T has operator = 
		            }
	            }                                                        
            }

            ~Matrix()
            {
                for (int i = 0; i < dims.getRow(); i++)
                {
                 delete[] array2D[i];
                }
                delete[]  array2D;
            
            }
             // operator = 
             // changing the this values to the param values
             // assumig that T  has the constructor with no params ,and T has operator =.
            Matrix& operator=(const Matrix& matrix)
            {
               T** temp = new T*[matrix.dims.getRow()];
               for (int i = 0; i < matrix.dims.getRow(); i++)
	            {
		            temp[i] = new T[matrix.dims.getCol()];
	            }
                for (int i = 0; i < matrix.dims.getRow(); i++)
	            {
		              for (int j = 0; j < matrix.dims.getCol(); j++)
		            {
			            temp[i][j] = matrix.array2D[i][j];    //assuming that T has operator = 
		            }
	            }
                delete[]  array2D;
                array2D = temp;
                dims = matrix.dims;
                return (*this);                                                    
            }


            


            

    

    };
    
} // namespace mtm

#endif 