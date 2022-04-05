#pragma once

#include <utility>
#include "Functor.hpp"

namespace qsigslot {

template <typename T> class MethodFunctor;

template <typename C, typename R, typename ...Args>
class MethodFunctor<R(C::*)(Args...)> : public Functor<R(Args...)> {
    C* object;
    R(C::*method)(Args...);
public:
    MethodFunctor(C *object, R(C::*method)(Args...))
        : object(object)
        , method(method)
    {}

    virtual R operator()(Args... args) override {
        return (object->*method)(std::forward<Args>(args)...);
    }
};

}
