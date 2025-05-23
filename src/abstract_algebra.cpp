#include <iostream>
#include <element.hpp>

namespace aa = abstract_algebra;

int main()
{
    using S = aa::primitive_set<uint32_t, 32>;
    aa::element_of<S, aa::TYPE::SET> e;
    aa::element_of<S, aa::TYPE::SET> e2 = e;
    aa::element_of<S, aa::TYPE::SET> e3 = 0;
    aa::element_of<S, aa::TYPE::SET> e4;
    e4 = 0;

    std::cout << "e  = " << e << std::endl;
    std::cout << "e3 = " << e3 << std::endl;

    using G = aa::group<S, std::plus<uint32_t>>;
    aa::element_of<G, aa::TYPE::GROUP> g;
}
