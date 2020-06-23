#include <iostream>
#include <string>
#include "Matrix.h"

class Square { 
    public: 
        int operator()(int val){ 
          return val*val; 
    } 
}; 
class divide { 
    public: 
        int operator()(int val){ 
          return val/2; 
    } 
}; 
int f(int val)
{
    return val +100;
}

int main(){
    mtm::Dimensions dim_1(2,3);
    mtm::Dimensions dim_2(-2,3);
    mtm::Dimensions dim_3(3,2);
    mtm::Dimensions dim_4(0,0);
    try{
        const mtm::Matrix<std::string> mat_1(dim_2,"str1");
    } catch(mtm::Matrix<std::string>::IllegalInitialization& e){
        std::cout<<e.what()<<std::endl;
    }
    try{
        mtm::Matrix<std::string> mat_1(dim_1,"str1");
        const mtm::Matrix<std::string> mat_2((mat_1+std::string("+"))+mat_1);
        const mtm::Matrix<std::string> mat_3(mat_1.transpose());
        std::cout<<mat_2;
        mtm::Matrix<std::string> mat_4=mat_1+mat_3;
    } catch(mtm::Matrix<std::string>::DimensionMismatch& e){
        std::cout<<e.what()<<std::endl;
    }
    try{
        const mtm::Matrix<int> mat_1 = mtm::Matrix<int>::Diagonal(2,1);
        mtm::Matrix<int> mat_2 = mtm::Matrix<int>::Diagonal(2,-1);
        std::cout<<mtm::any(mat_1)<<" "<<mtm::any(mat_1-mat_2)<<" "<<mtm::all(mat_1+mat_2+1)<<std::endl;
        std::cout<<(-mat_2)(1,1)<<(-mat_2)(2,2)<<std::endl;
    } catch(mtm::Matrix<int>::AccessIllegalElement& e){
        std::cout<<e.what()<<std::endl;
    }
    try{
        mtm::Matrix<int> mat_1(dim_1);
        int counter=0;
        mtm::Matrix<int>::iterator it=mat_1.begin();
        for(;it!=mat_1.end();++it){
            *it=counter++;
        }
        std::cout<<(mat_1>=3);
        it++;
        std::cout<<(mat_1==3);
        *it;
    } catch(mtm::Matrix<int>::AccessIllegalElement& e){
        std::cout<<e.what()<<std::endl;
    }
    
    try{
        const mtm::Matrix<int> mat_1(dim_1,4);
        const mtm::Matrix<int> mat_2=mat_1.apply(Square());
        const mtm::Matrix<int> mat_3=mat_1.apply(f);
        std::cout<<mat_3 << std::endl;
        std::cout<<mat_1;
        std::cout<<mat_2(1,2)<<std::endl;
        mtm::Matrix<int>::const_iterator it = mat_2.end();
        std::cout<<*it;
    } catch(mtm::Matrix<int>::AccessIllegalElement& e){
        std::cout<<e.what()<<std::endl;
    }
    try
    {
        mtm::Matrix<std::string> m(dim_4,"aamer");
    }
    catch(const mtm::Matrix<std::string>::IllegalInitialization& e)
    {
        std::cout << e.what() << '\n';
    }
    try
    {
        mtm::Matrix<std::string> m(dim_1,"aamer");
        m += std::string("the king");
        std::cout<<m << std::endl;
        mtm::Matrix<std::string> m2(dim_1,"HI");
        std::cout<< m2+m << std::endl ; 
        mtm::Matrix<int> m3 = mtm::Matrix<int>::Diagonal(3,6);
        mtm::Matrix<int> m4 = mtm::Matrix<int>::Diagonal(4,5);
        std::cout << (m3<=6) << std::endl ;
        std::cout << (m3 > 0)<< std::endl;
        std::cout << (m4 == 5)<< std::endl;
        std::cout << m3.apply(divide())<< std::endl;
        std::cout << (m3+m4)<< std::endl;
    }
    catch(const mtm::Matrix<int>::DimensionMismatch& e)
    {
        std::cout << e.what() << '\n';
    }
    try
    {
        const mtm::Matrix<int> mat_1(dim_1);
        mtm::Matrix<int>::const_iterator ha=mat_1.end();
        std::cout << *ha ;
    }
    catch(const mtm::Matrix<int>::AccessIllegalElement& e)
    {
        std::cout << e.what() << '\n';
    }
    
    
    
}
