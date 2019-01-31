# Hourglass :hourglass_flowing_sand:

**Hourglass** is a C++ library that enables event-driven design over a *time-series*.

## Quick-example

```cpp
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
    hourglass::hourglass<SimpleEvent> h{0}; //using an integer to count time elapsing
    h.addEvent(0, {"a", 1}); // adds the event to timepoint 0
    h.addEvent(1, {"b", 2});
    h.addEvent(1, {"c", 3});
    h.addEvent(1, {"d", 4});
    h.addEvent(2, {"e", 5});
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    h.advanceTime();
    std::cout << h;

    return 0;
}

```

```
[0] Has events!
  -> message: a value: 1
[1] Has events!
  -> message: b value: 2
  -> message: c value: 3
  -> message: d value: 4
[2] Has events!
  -> message: e value: 5
[3] No events!
```

## Use the library
### As a CMake submodule

### Installing in the system
*Todo*: Complete CMake install process

### As a Conan package
*Todo*: A PR would be appreciated.

## More usages example

Check the [demos](/demos) folder for more examples.