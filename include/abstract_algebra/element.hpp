#pragma once

#include <concepts>
#include <optional>
#include <iostream>
#include <cassert>

#include <abstract_algebra/primitive_set.hpp>
#include <abstract_algebra/group.hpp>

namespace abstract_algebra {

template <typename S, class Impl> // Impl is for CRTP
class element_of_base {
public:
    element_of_base() = default;
    element_of_base(typename S::value_type _val) : m_value(_val) {};
    element_of_base(const Impl& _e) : m_value(_e.m_value) {};

    element_of_base& operator=(const Impl& _e) { m_value = _e.m_value; return *this; }
    element_of_base& operator=(typename S::value_type _val) { m_value = _val; return *this; }

    friend bool operator==(const Impl& _e1, const Impl& _e2) { return _e1.m_value == _e2.m_value; }
    friend bool operator==(const Impl& _e, typename S::value_type _val) { return _e.has_value() ? _e.get_value() == _val : false; }

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

template <typename S>
class element_of : public element_of_base<S, element_of<S>> {};

template <std::derived_from<primitive_set_t> S>
class element_of<S> : public element_of_base<S, element_of<S>> {
    using element_t = element_of<S>;
    using base_element_t = element_of_base<S, element_t>;

public:
    element_of() : base_element_t() {}
    element_of(typename S::value_type _val) : base_element_t(_val) {}
    element_of(const element_of& _e) : base_element_t(_e) {}

    element_t& operator=(typename S::value_type _val) { base_element_t::operator=(_val); return *this; }
    element_t& operator=(const element_t& _e) { base_element_t::operator=(_e); return *this; }
};

template <std::derived_from<group_t> G>
class element_of<G> : public element_of_base<G, element_of<G>> {
    using element_t = element_of<G>;
    using base_element_t = element_of_base<G, element_t>;

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
