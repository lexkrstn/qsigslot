#pragma once

#include <utility>
#include "Functor.hpp"

namespace qsigslot {

template <typename T> class FunctionFunctor;

template <typename R, typename ...Args>
class FunctionFunctor<R(Args...)> : public Functor<R(Args...)> {
    R(*fn)(Args...);
public:
    FunctionFunctor(R(*fn)(Args...)) : fn(fn) {}

    virtual R operator()(Args... args) override {
        return fn(std::forward<Args>(args)...);
    }
};

}
