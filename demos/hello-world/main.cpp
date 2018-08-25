#include <iostream>
#include "hourglass/hourglass.hpp"

struct SimpleEvent
{
    std::string message;
    int value;

    friend std::ostream& operator<<(std::ostream& os, const SimpleEvent& event)
    {
        os << "message: " << event.message << " value: " << event.value;
        return os;
    }
};

int main()
{
    hourglass::hourglass<SimpleEvent> h{0};
    h.addEvent({"a", 1}, 0);
    h.addEvent({"b", 2}, 1);
    h.addEvent({"c", 3}, 1);
    h.addEvent({"d", 4}, 1);
    h.addEvent({"e", 5}, 2);
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    return 0;
}
