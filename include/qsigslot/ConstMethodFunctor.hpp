#pragma once

#include <utility>
#include "Functor.hpp"

namespace qsigslot {

template <typename T> class ConstMethodFunctor;

template <typename C, typename R, typename ...Args>
class ConstMethodFunctor<R(C::*)(Args...)> : public Functor<R(Args...)> {
    const C* object;
    mutable R(C::*method)(Args...) const;
public:
    ConstMethodFunctor(const C *object, R(C::*method)(Args...)const)
        : object(object)
        , method(method)
    {}

    virtual R operator()(Args... args) override {
        return (object->*method)(std::forward<Args>(args)...);
    }
};

}
