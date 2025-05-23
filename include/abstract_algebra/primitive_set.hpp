#pragma once

#include <cstdint>

namespace abstract_algebra
{

class primitive_set_t
{

};

template <typename T, uint64_t N>
class primitive_set : public primitive_set_t
{
public:
    typedef T value_type;
    static constexpr uint64_t size = N;
};
}

