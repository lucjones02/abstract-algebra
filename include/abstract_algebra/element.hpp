#pragma once

#include <concepts>
#include <optional>
#include <iostream>
#include <cassert>

#include <abstract_algebra/primitive_set.hpp>
#include <abstract_algebra/group.hpp>

namespace abstract_algebra {

enum class TYPE {
    SET,
    GROUP,
    RING
};

template <typename S, TYPE type, class Impl> // Impl is for CRTP
class element_of_base {
public:
    element_of_base() = default;
    element_of_base(typename S::value_type _val) : m_value(_val) {};
    element_of_base(const Impl& _e) : m_value(_e.m_value) {};

    element_of_base& operator=(const Impl& _e) { m_value = _e.m_value; return *this; }
    element_of_base& operator=(typename S::value_type _val) { m_value = _val; return *this; }

    friend std::ostream& operator<<(std::ostream& os, Impl& e) {
        if (e.has_value()) {
            os << e.m_value.value();
        }
        else {
            os << "no value";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& os, Impl& e) {
        typename S::value_type _val;
        os >> _val; // TODO: deal with bad inputs
        e.m_value = _val;
        return os;
    }

    bool has_value() const { return m_value.has_value(); }
    S::value_type get_value() const { return m_value.value(); }
    void set_value(S::value_type _val) { m_value = _val; }

private:
    std::optional<typename S::value_type> m_value;

};

template <typename S, TYPE type>
class element_of : public element_of_base<S, type, element_of<S, type>> {};

template <typename S> requires std::derived_from<S, primitive_set_t>
class element_of<S, TYPE::SET> : public element_of_base<S, TYPE::SET, element_of<S, TYPE::SET>> {
    using element_t = element_of<S, TYPE::SET>;
    using base_element_t = element_of_base<S, TYPE::SET, element_t>;

public:
    element_of() : base_element_t() {}
    element_of(typename S::value_type _val) : base_element_t(_val) {}
    element_of(const element_of& _e) : base_element_t(_e) {}

    element_t& operator=(typename S::value_type _val) { base_element_t::operator=(_val); return *this; }
    element_t& operator=(const element_t& _e) { base_element_t::operator=(_e); return *this; }

};

template <typename G> requires std::derived_from<G, group_t>
class element_of<G, TYPE::GROUP> : public element_of_base<G, TYPE::GROUP, element_of<G, TYPE::GROUP>> {
    using element_t = element_of<G, TYPE::GROUP>;
    using base_element_t = element_of_base<G, TYPE::GROUP, element_t>;

public:
    element_of() : base_element_t() {}
    element_of(typename G::value_type _val) : base_element_t(_val) {}
    element_of(const element_of& _e) : base_element_t(_e) {}

    element_t& operator=(typename G::value_type _val) { base_element_t::operator=(_val); return *this; }
    element_t& operator=(const element_t& _e) { base_element_t::operator=(_e); return *this; }

    friend element_t operator+(const element_t& _e1, const element_t& _e2) { 
        assert(_e1.has_value() && _e2.has_value());
        return G::addition(_e1.get_value(), _e2.get_value());
    }
};

} // namespace abstract_algebra
