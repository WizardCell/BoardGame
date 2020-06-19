#include "Matrix.h"


int main()
{
    mtm::Dimensions d(2,3);
    mtm::Matrix<std::string> m(d); 
    mtm::Matrix<std::string> m2(m);
    m = m2;
    return 0;
}