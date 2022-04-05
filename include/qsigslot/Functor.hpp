#pragma once

namespace qsigslot {

template <typename T> class Functor;

template <typename R, typename ...Args>
class Functor<R(Args...)>
{
public:
    virtual ~Functor() = default;
    virtual R operator()(Args...) = 0;
};

}
