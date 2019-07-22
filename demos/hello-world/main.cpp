#include <iostream>
#include "bittencookie/hourglass.hpp"

struct SimpleEvent
{
    std::string message;
    int value;

    SimpleEvent(std::string m, int v) : message(std::move(m)), value(v) {}

    friend std::ostream& operator<<(std::ostream& os, const SimpleEvent& event)
    {
        os << "message: " << event.message << " value: " << event.value;
        return os;
    }
};

int main()
{
    bittencookie::hourglass<SimpleEvent> h{0};
    h.addEvent(0, {"a", 1});
    h.addEvent(1, {"b", 2});
    h.addEvent(1, {"c", 3});
    h.addEvent(1, {"d", 4});
    h.addEvent(2, {"e", 5});
    h.emplaceEvent(2, "f", 6);
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    return 0;
}
