#pragma once

#include <utility>
#include "Functor.hpp"

namespace qsigslot {

template <typename T> class FunctionFunctor;

template <typename R, typename ...Args>
class FunctionFunctor<R(Args...)> : public Functor<R(Args...)>
{
    using Fn = R(*)(Args...);

    Fn const fn;
public:
    FunctionFunctor(const FunctionFunctor&) = delete;
    FunctionFunctor& operator = (const FunctionFunctor&) = delete;

    FunctionFunctor(const Fn fn) : fn(fn) {}

    virtual R operator()(Args... args) override
    {
        return fn(std::forward<Args>(args)...);
    }
};

}
