#include <iostream>

#include "../include/qsigslot.hpp"

using namespace qsigslot;

void foo(const char* s) {
    std::cout << "foo: " << s << std::endl;
}

class Emitter
{
public:
    Signal<void(int, int)> click;
};

class Receiver
{
public:
    Slot<void(int, int)> clickSlot;

    Receiver()
        : clickSlot(this, &Receiver::onClick)
    {
    }

    void onClick(int x, int y) const {
        std::cout << "x = " << x << " y = " << y << std::endl;
    }
};

int main(int argc, char** argv) {
    Receiver receiver;
    Emitter emitter;
    emitter.click.bind(receiver.clickSlot);
    emitter.click(1, 2);

    Signal<void(const char*)> click;
    Slot<void(const char*)> onClick(foo);
    click.bind(onClick);
    click("asdf");

    return 0;
}
