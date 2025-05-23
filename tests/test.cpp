#include <catch2/catch_test_macros.hpp>
#include <abstract_algebra/element.hpp>

namespace aa = abstract_algebra;

TEST_CASE( "construct elements", "[construction]") {
    using S = aa::primitive_set<uint32_t, 32>;
    aa::element_of<S, aa::TYPE::SET> e0;
    aa::element_of<S, aa::TYPE::SET> e1 {0};
    aa::element_of<S, aa::TYPE::SET> e2 = 0;

    REQUIRE(!e0.has_value());
    REQUIRE(e1.has_value());
    REQUIRE(e2.has_value());

    REQUIRE(e1.get_value() == 0);
    REQUIRE(e2.get_value() == 0);

    using G = aa::group<S, std::plus<S::value_type>>;
    aa::element_of<G, aa::TYPE::GROUP> g0;
    aa::element_of<G, aa::TYPE::GROUP> g1 {0};
    aa::element_of<G, aa::TYPE::GROUP> g2 = 0;

    REQUIRE(!g0.has_value());
    REQUIRE(g1.has_value());
    REQUIRE(g2.has_value());

    REQUIRE(g1.get_value() == 0);
    REQUIRE(g2.get_value() == 0);
}
