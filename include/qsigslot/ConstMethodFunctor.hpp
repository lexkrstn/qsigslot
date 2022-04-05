#pragma once

#include <utility>
#include "Functor.hpp"

namespace qsigslot {

template <typename T> class ConstMethodFunctor;

template <typename C, typename R, typename ...Args>
class ConstMethodFunctor<R(C::*)(Args...)> : public Functor<R(Args...)>
{
    using Method = R(C::*)(Args...) const;

    const C* const object;
    Method const method;
public:
    ConstMethodFunctor(const C* object, const Method method)
        : object(object)
        , method(method)
    {}

    virtual R operator()(Args... args) override
    {
        return (object->*method)(std::forward<Args>(args)...);
    }
};

}
