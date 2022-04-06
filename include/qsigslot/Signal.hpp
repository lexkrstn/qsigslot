#pragma once

#include <utility>

namespace qsigslot {

template <typename T> class Signal;
template <typename T> class Slot;

template <typename R, typename... Args>
class Signal<R(Args...)>
{
    Slot<R(Args...)>* first;

public:
    Signal(const Signal&) = delete;
    Signal& operator = (const Signal&) = delete;

    Signal() {
        first = nullptr;
    }

    ~Signal() {
        // When the signal destructs detach all its slots.
        Slot<R(Args...)> *next;
        while (first != nullptr) {
            next = first->next;
            first->next = nullptr;
            first->previous = nullptr;
            first->signal = nullptr;
            first = next;
        }
    }

    void operator()(Args... args) const {
        Slot<R(Args...)> *slot = first;
        while (slot != nullptr) {
            slot->operator()(std::forward<Args>(args)...);
            slot = slot->next;
        }
    }

    void bind(Slot<R(Args...)>& slot) {
        slot.next = first;
        if (first != nullptr)
            first->previous = &slot;
        first = &slot;
    }

    void unbind(Slot<R(Args...)>& slot) {
        assert(slot.signal == this);
        if (slot.previous != nullptr) {
            slot.previous->next = slot.next;
            slot.previous = nullptr;
        } else {
            first = slot.next;
        }
        if (slot.next != nullptr) {
            slot.next->previous = slot.previous;
            slot.next = nullptr;
        }
        slot.signal = nullptr;
    }
};

}
