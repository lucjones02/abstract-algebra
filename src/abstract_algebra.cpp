#include <iostream>
#include <functional>
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

    std::cout << "e3 = " << e3 << std::endl;
    std::cout << "e  = " << e << std::endl;

    using G = aa::group<S, std::plus<S::value_type>>;
    aa::element_of<G, aa::TYPE::GROUP> g0;
    aa::element_of<G, aa::TYPE::GROUP> g1 = 1;
    aa::element_of<G, aa::TYPE::GROUP> g2 = 2;
    aa::element_of<G, aa::TYPE::GROUP> g3 = g1 + g2;

    std::cout << "g0 = " << g0 << std::endl;
    std::cout << "g1 = " << g1 << std::endl;
    std::cout << "g2 = " << g2 << std::endl;
    std::cout << "g3 = " << g3 << std::endl;

}
