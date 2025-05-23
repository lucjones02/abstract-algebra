#include <catch2/catch_test_macros.hpp>
#include <abstract_algebra/element.hpp>

namespace aa = abstract_algebra;

TEST_CASE("construct elements", "[construction]") {
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

TEST_CASE("basic addition in groups", "[construction]"){
    using S = aa::primitive_set<uint32_t, 32>;
    using G = aa::group<S, std::plus<S::value_type>>;
    aa::element_of<G, aa::TYPE::GROUP> g;

    SECTION("2 + 2"){
        aa::element_of<G, aa::TYPE::GROUP> g1 = 2;
        aa::element_of<G, aa::TYPE::GROUP> g2 = 2;
        g = g1 + g2;

        REQUIRE(g.has_value());
        REQUIRE(g.get_value() == 4);
    }

    SECTION("9 + 10"){
        aa::element_of<G, aa::TYPE::GROUP> g1 = 9;
        aa::element_of<G, aa::TYPE::GROUP> g2 = 10;
        g = g1 + g2;

        REQUIRE(g.has_value());
        REQUIRE(g.get_value() != 21);
    }

    SECTION("12 + 0"){
        aa::element_of<G, aa::TYPE::GROUP> g1 = 12;
        aa::element_of<G, aa::TYPE::GROUP> g2 = 0;
        g = g1 + g2;

        REQUIRE(g.has_value());
        REQUIRE(g.get_value() == g1.get_value());
    }
}

