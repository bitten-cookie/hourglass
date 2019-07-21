#include <gtest/gtest.h>

#include "bittencookie/hourglass.hpp"
#include <functional>

using namespace bittencookie;

TEST(Hourglass, SupportsLambda)
{
    using lambda = std::function<int(int)>;

    hourglass<lambda> h;
    h.addEvent(0, [](int v)
    {
        return v + 1;
    });

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();
    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event(0), 1);
}