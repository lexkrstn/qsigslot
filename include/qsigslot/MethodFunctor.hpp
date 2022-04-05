#pragma once

#include <utility>
#include "Functor.hpp"

namespace qsigslot {

template <typename T> class MethodFunctor;

template <typename C, typename R, typename ...Args>
class MethodFunctor<R(C::*)(Args...)> : public Functor<R(Args...)> {
    using Method = R(C::*)(Args...);

    C* const object;
    Method const method;
public:
    MethodFunctor(C* object, Method method)
        : object(object)
        , method(method)
    {}

    virtual R operator()(Args... args) override {
        return (object->*method)(std::forward<Args>(args)...);
    }
};

}
