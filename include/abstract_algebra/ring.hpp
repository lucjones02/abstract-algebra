#pragma once

#include <abstract_algebra/primitive_set.hpp>

#include <cstdint>
#include <concepts>


namespace abstract_algebra {

class ring_t {};

template <class S, typename add, typename mult> requires std::derived_from<S, primitive_set_t>
class ring : public ring_t {
    public:
        typedef typename S::value_type value_type;
        static constexpr uint64_t size = S::size;
        static constexpr auto addition = add();
        static constexpr auto multiplication = mult();

};

} // namespace abstract_algebra
