#include "Matrix.h"
int main()
{
    try
    {
        mtm::Dimensions d(2,3);
        mtm::Dimensions d2(3,3);
        const mtm::Matrix<int> m(d,3);
        const mtm::Matrix<int> m2(d2,2);
        std::cout << (m+m2) ;

        std::cout << *m.end();
    }
    catch(const mtm::Matrix<int>::AccessIllegalElement& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(const mtm::Matrix<int>::DimensionMismatch& e)
    {
        std::cout << e.what()<< std::endl;
    }
    
    
     

    return 0;
}