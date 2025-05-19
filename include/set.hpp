#pragma once

#include <vector>
#include <functional>

#include <element.hpp>

namespace abstract_algebra {

template <typename T>
class TypedSet{
public:
    TypedSet(): m_condition([](T elem){return true;}){};
    TypedSet(std::function<bool(T)> func_condition): m_condition(func_condition){};
    
    bool Contains(Element<T> elem);

private:
    std::function<bool(T)> m_condition;
};


}
