#pragma once

#include <concepts>

#include <primitive_set.hpp>
#include <group.hpp>

namespace abstract_algebra
{

enum class TYPE 
{
    SET,
    GROUP,
    RING
};

template <typename S, TYPE type>
class element_of {};

template <typename S> requires std::derived_from<S, primitive_set_t>
class element_of<S, TYPE::SET>
{
};

template <typename G> requires std::derived_from<G, group_t>
class element_of<G, TYPE::GROUP>
{
};

} // namespace abstract_algebra
