# Hourglass :hourglass_flowing_sand: [![Build Status](https://travis-ci.com/bitten-cookie/hourglass.svg?branch=master)](https://travis-ci.com/bitten-cookie/hourglass)

**Hourglass** is a C++ library that enables event-driven design over a *time-series*.

## Features

- Lambda / `std::function` support
- `std::unique_ptr` support

## Quick-example

```cpp
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
    h.addEvent(2, "f", 6);
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
  -> message: f value: 6
[3] No events!
```

## Use the library
### CMake submodule
As simple as `add_subdirectory(hourglass)` and then `target_link_libraries(yourTarget hourglass)`

### Installing in the system
*Todo*: Complete CMake install process

### As a Conan package
*Todo*: A PR would be appreciated.

## Docs
*Todo*: A PR would be appreciated.

## More usages example

Check the [demos](/demos) folder for more examples.