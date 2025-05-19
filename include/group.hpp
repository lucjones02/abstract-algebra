#pragma once

#include <primitive_set.hpp>

#include <cstdint>
#include <concepts>

namespace abstract_algebra
{

    class group_t {};

    template <class S> requires std::derived_from<S, primitive_set_t>
    class group : group_t
    {
        public:
            typedef typename S::value_type value_type;
            static constexpr uint64_t size = S::size;
    };

}

