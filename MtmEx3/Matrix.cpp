#include "Matrix.h"
int main()
{
    mtm::Dimensions d(2,3);
    mtm::Matrix<int> m(d,3);
    mtm::Matrix<bool> m2= m>4;
    std::cout << m2;

    return 0;
}