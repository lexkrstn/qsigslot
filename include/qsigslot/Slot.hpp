#pragma once

#include <utility>
#include "Functor.hpp"
#include "FunctionFunctor.hpp"
#include "MethodFunctor.hpp"
#include "ConstMethodFunctor.hpp"
#include "FunctorTraits.hpp"

namespace qsigslot {

template <typename T> class Signal;
template <typename T> class Slot;

template <typename R, typename... Args>
class Slot<R(Args...)>
{
    char functorBytes[FunctorTraits::MAX_SIZEOF];

    Signal<R(Args...)> *signal;
    Slot<R(Args...)> *next;
    Slot<R(Args...)> *previous;

    friend class Signal<R(Args...)>;

public:
    Slot(const Slot&) = delete;
    Slot& operator = (const Slot&) = delete;

    Slot(R(*fn)(Args... args))
        : signal(nullptr)
        , next(nullptr)
        , previous(nullptr)
    {
        auto functor = reinterpret_cast<FunctionFunctor<R(Args...)>*>(functorBytes);
        new (functor) FunctionFunctor<R(Args...)>(fn);
    }

    template <typename C>
    Slot(C *object, R(C::*method)(Args... args))
        : signal(nullptr)
        , next(nullptr)
        , previous(nullptr)
    {
        auto functor = reinterpret_cast<MethodFunctor<R(C::*)(Args...)>*>(functorBytes);
        new (functor) MethodFunctor<R(C::*)(Args...)>(object, method);
    }

    template <typename C>
    Slot(const C *object, R(C::*method)(Args... args)const)
        : signal(nullptr)
        , next(nullptr)
        , previous(nullptr)
    {
        auto functor = reinterpret_cast<ConstMethodFunctor<R(C::*)(Args...)>*>(functorBytes);
        new (functor) ConstMethodFunctor<R(C::*)(Args...)>(object, method);
    }

    ~Slot()
    {
        if (signal != nullptr)
            signal->unbind(*this);

        auto functor = reinterpret_cast<Functor<R(Args...)>*>(functorBytes);
        functor->~Functor();
    }

    R operator()(Args... args)
    {
        auto functor = reinterpret_cast<Functor<R(Args...)>*>(functorBytes);
        return functor->operator()(std::forward<Args>(args)...);
    }
};

}
