#pragma once
#include <cstddef>

#include "MethodFunctor.hpp"

namespace qsigslot {

class FunctorTraits {
    struct TraitBase {
        virtual void method() {}
    };

    struct TraitDerived : public TraitBase {
        virtual void method() {}
    };

public:

    static constexpr size_t MAX_SIZEOF = sizeof(MethodFunctor<void (TraitDerived::*)()>);
};

}
