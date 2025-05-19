#include <iostream>
#include <element.hpp>

namespace aa = abstract_algebra;

int main()
{
    using S = aa::primitive_set<uint32_t, 32>;
    aa::element_of<S, aa::TYPE::SET> e;

    using G = aa::group<S>;
    aa::element_of<G, aa::TYPE::GROUP> g;
}
