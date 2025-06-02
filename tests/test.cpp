#include <catch2/catch_test_macros.hpp>
#include <abstract_algebra/element.hpp>

namespace aa = abstract_algebra;

TEST_CASE("construct elements", "[construction]") {
    using S = aa::primitive_set<uint32_t, 32>;
    aa::element_of<S> e0;
    aa::element_of<S> e1 {0};
    aa::element_of<S> e2 = 0;

    REQUIRE(!e0.has_value());
    REQUIRE(e1.has_value());
    REQUIRE(e2.has_value());

    REQUIRE(e1.get_value() == 0);
    REQUIRE(e2.get_value() == 0);

    using G = aa::group<S, std::plus<S::value_type>>;
    aa::element_of<G> g0;
    aa::element_of<G> g1 {0};
    aa::element_of<G> g2 = 0;

    REQUIRE(!g0.has_value());
    REQUIRE(g1.has_value());
    REQUIRE(g2.has_value());

    REQUIRE(g1.get_value() == 0);
    REQUIRE(g2.get_value() == 0);
}

TEST_CASE("basic addition in groups", "[construction]"){
    using S = aa::primitive_set<uint32_t, 32>;
    using G = aa::group<S, std::plus<S::value_type>>;
    aa::element_of<G> g;

    SECTION("2 + 2"){
        aa::element_of<G> g1 = 2;
        aa::element_of<G> g2 = 2;
        g = g1 + g2;

        REQUIRE(g.has_value());
        REQUIRE(g.get_value() == 4);
    }

    SECTION("9 + 10"){
        aa::element_of<G> g1 = 9;
        aa::element_of<G> g2 = 10;
        g = g1 + g2;

        REQUIRE(g.has_value());
        REQUIRE(g.get_value() != 21);
    }

    SECTION("12 + 0"){
        aa::element_of<G> g1 = 12;
        aa::element_of<G> g2 = 0;
        g = g1 + g2;

        REQUIRE(g.has_value());
        REQUIRE(g.get_value() == g1.get_value());
    }
}

constexpr char cayley_table[4][4] = {
    {'e', 'a', 'b', 'c'},
    {'a', 'e', 'c', 'b'},
    {'b', 'c', 'e', 'a'},
    {'c', 'b', 'a', 'e'},
};

TEST_CASE( "Klein four-group", "[construction]"){
    using S = aa::primitive_set<char, 4>;

    struct klein_mult {
        char operator()(const char& _c1, const char& _c2) const{
            char i = _c1 == 'e' ? 0 : _c1 - 'a' + 1;
            char j = _c2 == 'e' ? 0 : _c2 - 'a' + 1;
            return cayley_table[i][j];
        }
    };

    using G = aa::group<S, klein_mult>;
    aa::element_of<G> e = 'e';
    aa::element_of<G> a = 'a';
    aa::element_of<G> b = 'b';
    aa::element_of<G> c = 'c';

    aa::element_of<G> g;

    SECTION("e * a"){
        g = e + a;

        REQUIRE(g.has_value());
        REQUIRE(g == a);
    }

    SECTION("e * b"){
        g = e + b;

        REQUIRE(g.has_value());
        REQUIRE(g == b);
    }

    SECTION("e * c"){
        g = e + c;

        REQUIRE(g.has_value());
        REQUIRE(g == c);
    }

    SECTION("a * a"){
        g = a + a;

        REQUIRE(g.has_value());
        REQUIRE(g == klein_mult()('a', 'a'));
        REQUIRE(g == e);
    }

    SECTION("a * c"){
        g = a + c;

        REQUIRE(g.has_value());
        REQUIRE(g == klein_mult()('a', 'c'));
        REQUIRE(g == b);
    }

    SECTION("(a * a) * (b * b)"){
        g = (a + a) + (b + b);

        REQUIRE(g.has_value());
        REQUIRE(g == e);
    }

    SECTION("(a * c) * (a * c)"){
        g = (a + c) + (a + c);

        REQUIRE(g.has_value());
        REQUIRE(g == e);
    }
}

