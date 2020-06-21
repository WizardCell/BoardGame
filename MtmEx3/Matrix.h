#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include <string>
#include <iostream>
#include "Auxiliaries.h"

/*simple logic GENERIC functions */
    template<class T>
    bool bigger(T a, T b)
    {
        return a > b;
    }
    template<class T>
	bool biggerEqual(T a, T b)
    {
        return a >= b ;
    }
    template<class T>
	bool min(T a, T b)
    {
        return a < b ;
    }
    template<class T>
	bool minEqual(T a, T b)
    {
        return a <= b;
    }
    template<class T>
	bool isEqual(T a, T b)
    {
        return a == b ;
    }
    template<class T>
	bool notEqual(T a, T b)
    {
        return a != b ; 
    }


namespace mtm
{
    template<class T>
    class Matrix 
    {
        private:
            T** array2D;
            Dimensions dims;

            // helper function for comparing according to compare function.
            // we assume that T is compareable.
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

            //constructor
            Matrix(Dimensions dim, T value = T()): dims(dim.getRow(),dim.getCol())
            {
                
                if ( dim.getRow() <= 0 || dim.getCol() <=0)
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
                catch(const std::bad_alloc& e)  // here means an allocation failed . we need to free the ones we allocated.
                {
                    for (int i = 0; i < counter; i++)
                    {
                        delete [] array2D[i];
                    }
                    throw e;
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
                int counter = 0 ; 
                try
                {
                    for (int i = 0; i < dims.getRow(); i++)
	                {
		                array2D[i] = new T[dims.getCol()];
                        counter++;
	                }
                }
                catch(const std::bad_alloc& e)
                {
                    for (int i = 0; i < counter; i++)
                    {
                        delete[] array2D[i];
                    }
                    throw e;
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
             // changing the this values to the @param values
             // assumig that T  has the constructor with no params ,and T has operator =.
            Matrix& operator=(const Matrix& matrix)
            {
               T** temp = new T*[matrix.dims.getRow()];
               int counter =0 ;
               try
               {
                   for (int i = 0; i < matrix.dims.getRow(); i++)
	                {
		                temp[i] = new T[matrix.dims.getCol()];
                        counter++;
	                }
               }
               catch(const std::bad_alloc& e)
               {
                   for (int i = 0; i < counter; i++)
                   {
                       delete[] temp[i];
                   }
                   throw e;
               }
               
               
                for (int i = 0; i < matrix.dims.getRow(); i++)
	            {
		              for (int j = 0; j < matrix.dims.getCol(); j++)
		            {
			            temp[i][j] = matrix.array2D[i][j];     
		            }
	            }
                delete[]  array2D;
                array2D = temp;
                dims = matrix.dims;
                return (*this);                                                    
            }

             // creating diagonal matrix 
             // the diagonal fills with the value , anywhere else with the deafuld constructor.
             // we assume that  T HAS the default constructor and  operator =
            static Matrix Diagonal(Dimensions dim ,T value)
            {
                if ( dim.getCol() <=0 or dim.getRow()<=0)
                {
                    throw IllegalInitialization();
                }
                Matrix<T> matrix(dim);
                for (int i = 0; i < dim.getRow(); i++)
                {
                   matrix.array2D[i][i] = value;
                }
                
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
            // doing trasnpose to the matrix without changing the given one.
            // assumeing that T has deafualt cons' and opeartor =
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
            
           
            
            //operator - unari
            // we assume that T has  - unari;
            Matrix operator-() const
            {
                Matrix result(*this);

	            for (int i = 0; i < dims.getRow(); i++)
	            {
		            for (int j = 0; j < dims.getCol(); j++)
		            {
			            result.array2D[i][j] *= -1;
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
                    throw DimensionMismatch(); /////////////
                }
                return operator+(*this,-matrix);
            }
            //operator +=
            // we assume that T has  +=
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
                if (i < 0 or i > this->height() or j<0 or j > this->width())
                {
                    throw AccessIllegalElement();
                }
	            return array2D[i][j];
            }
            //THE CONST version 
            const T& operator()(int i, int j) const 
            {
                if (i < 0 or i > this->height() or j<0 or j > this->width())
                {
                    throw AccessIllegalElement();
                }
	            return array2D[i][j];
            }


        /* the logic functions */
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
	        return requiredMatrix(*this,isEqual, value);
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
        iterator begin()  ;
        iterator end()  ;
        





            



            


            

    

    };


    // operator + 
    // we assume that T has operator + 
    template<class T>
    mtm::Matrix<T> operator+(const mtm::Matrix<T>& matrix1, const mtm::Matrix<T>& matrix2)
    {

       if (matrix1.width() != matrix2.width() or matrix1.height()!=matrix2.height())
        {
            throw typename mtm::Matrix<T>::DimensionMismatch(); // need to give matrixes dims 
        }
        Dimensions new_dim(matrix1.height(),matrix1.width());
        mtm::Matrix<T> result(new_dim);

	    for (int i = 0; i < matrix1.height(); i++)
	    {
		    for (int j = 0; j < matrix1.width(); j++)
		    {
			    result(i,j) = matrix1(i,j) + matrix2(i,j);
		    }
	    }
	        return result;
    }

    template<class T>
    Matrix<T> operator+(const Matrix<T>& matrix,T value)
    {
        return Matrix<T>(matrix) += value;
    }

    template<class T>
    Matrix<T> operator+(T value,const Matrix<T>& matrix)
    {
        return (matrix + value);
    }
    /* endof opeartor + */


    template<class T>
    std::ostream& operator<<(std::ostream& os,  Matrix<T> matrix) //remember to put back the const when const iterator is done//
     {
        typename mtm::Matrix<T>::iterator it_begin = matrix.begin();
        typename mtm::Matrix<T>::iterator it_end = matrix.end();
        return printMatrix(os,it_begin,it_end,matrix.width());
     }


    
    //all function
    //return false if one of the matrix's value is false
    //we assume that T has casting to boolean
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

    //any function
    //return true if atleast one of the matrix's value is not false
    //we assume that T has casting to boolean
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
     return iterator(this,dims,0);
    }

    template<class T>
    typename Matrix<T>::iterator Matrix<T>::end() 
    {
     return iterator(this,dims,this->size());
    }


    /* Iterator class*/
    template<class T>
    class Matrix<T>::iterator
	{
		Matrix<T>* matrix;
		Dimensions dims;
		int index;
		iterator(Matrix* matrix, const Dimensions dims, int index)
        : matrix(matrix) , dims(dims),index(index)
        {}

		friend class Matrix<T>;

	public:
	    T& operator*() const
        {
            if (index < 0 or index > matrix->size())
            {
                throw mtm::Matrix<T>::AccessIllegalElement();
            }
            int col = dims.getCol();
	        return matrix->array2D[(int)index/col][index%col];
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
            //check self operator == (what kind of exception should throw)
            return this->index == it.index;
        }
		bool operator!=(const iterator& it) const
        {
            return !(*this == it);
        }
		iterator(const iterator&) = default;
		iterator& operator=(const iterator&) = default;
		~iterator() = default;

	};

} // namespace mtm

#endif 