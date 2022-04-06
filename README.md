# Fast PUB/SUB (Signal/Slot) library for C++

The library takes its own approach to designing PUB/SUB mechanism for C++
applications to make it run as fast as possible. This is achieved by completely
eliminating the use of heap allocation to prevent memory defragmentation, which
is useful, for example, in game engines.

Typically, PUB/SUB libraries use dynamic lists or arrays to store the
subscriptions of each Publisher, which is not the case. Alternatively,
*qsigslot* uses the concept of **signals** and **slots**.

Each *slot* holds a reference to a function or method in the client code, that
must be executed upon some *signal* (read it as an event, such as clicking on a
button). In other words, the *slot* is the same as `std::function` in this
sense, but unlike the latter it doesn't use any heap memory internally.

Each *slot* may be bound to at most one *signal*. This limitation comes from
the fact that internally the *signal* builds the linked list out of the bound
*slots* themselves, i.e. without wrapping them or doing any memory allocation.

### Example of usage

```cpp
#include <iostream>
#include <qsigslot.hpp>

using namespace qsigslot;

// Sample class that emits a "hit" signal.
class PhysicsObject
{
public:
    Signal<void(const PhysicsObject*)> hit;

    void detectHit(const PhysicsObject* other)
    {
        if (true) // some calculations may go here
            hit(other); // emitting the signal with hit object as an argument
    }
};

// Sample class that listens to "hit" signals from a PhysicsObject instance.
class SceneNode
{
    PhysicsObject *physicsObject;
    Slot<void(const PhysicsObject*)> hitSlot;
public:
    SceneNode()
        : physicsObject(new PhysicsObject())
        , hitSlot(this, &SceneNode::onHit)
    {
        physicsObject->hit.bind(hitSlot);
    }

    // A handler associated with the hitSlot slot.
    void onHit(const PhysicsObject* hit)
    {
        std::cout << "The object is hit (log 1)" << std::endl;
    }

    PhysicsObject* getPhysicsObject()
    {
        return physicsObject;
    }
};

// Sample free function to wrap in a slot.
void logHit(const PhysicsObject* hit) {
    std::cout << "The object is hit (log 2)" << std::endl;
}

int main(int argc, char** argv)
{
    const int numNodes = 2;
    SceneNode nodes[numNodes];

    // Create a slot object from the free function
    Slot<void(const PhysicsObject*)> hitSlot(logHit);
    nodes[0].getPhysicsObject()->hit.bind(hitSlot);
    
    // Detect if objects hit each other
    for (int i = 0; i < numNodes; i++)
    {
        PhysicsObject* object1 = nodes[i].getPhysicsObject();
        for (int j = i + 1; j < numNodes; j++)
            object1->detectHit(nodes[j].getPhysicsObject());
    }
    return 0;
}
```

Outputs:
```
The object is hit (log 2)
The object is hit (log 1)
```
