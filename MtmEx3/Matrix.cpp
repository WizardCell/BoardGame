#include "Matrix.h"
int main()
{
    mtm::Dimensions d(2,3);
    mtm::Matrix<std::string> m(d);
    m+="!!";
    return 0;
}