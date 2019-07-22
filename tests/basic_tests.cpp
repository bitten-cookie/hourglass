#include <gtest/gtest.h>

#include "bittencookie/hourglass.hpp"

using namespace bittencookie;

namespace
{
    struct DumbEvent {};
}


TEST(Hourglass, Default_ctor)
{
    hourglass<DumbEvent> h;

    ASSERT_EQ(h.currentTime(), 0);
    ASSERT_EQ(h.pastEvents().empty(), true);
    ASSERT_EQ(h.eventsForCurrentTime().empty(), true);
    ASSERT_EQ(h.futureEvents().empty(), true);
}

TEST(Hourglass, Ctor_with_specific_time)
{
    hourglass<DumbEvent> h(8);

    ASSERT_EQ(h.currentTime(), 8);
    ASSERT_EQ(h.pastEvents().empty(), true);
    ASSERT_EQ(h.eventsForCurrentTime().empty(), true);
    ASSERT_EQ(h.futureEvents().empty(), true);
}

TEST(Hourglass, AddingEvents)
{
    hourglass<DumbEvent> h(0);

    h.emplaceEvent(0);
    h.emplaceEvent(1);
    h.emplaceEvent(1);
    h.emplaceEvent(2);

    ASSERT_EQ(h.currentTime(), 0);
    ASSERT_EQ(h.pastEvents().empty(), true);
    ASSERT_EQ(h.eventsForCurrentTime().size(), 1);
    ASSERT_EQ(h.futureEvents().size(), 3);

    h.advanceTime();

    ASSERT_EQ(h.currentTime(), 1);
    ASSERT_EQ(h.pastEvents().size(), 1);
    ASSERT_EQ(h.eventsForCurrentTime().size(), 2);
    ASSERT_EQ(h.futureEvents().size(), 1);

    h.advanceTime();

    ASSERT_EQ(h.currentTime(), 2);
    ASSERT_EQ(h.pastEvents().size(), 3);
    ASSERT_EQ(h.eventsForCurrentTime().size(), 1);
    ASSERT_EQ(h.futureEvents().size(), 0);

    h.advanceTime();

    ASSERT_EQ(h.currentTime(), 3);
    ASSERT_EQ(h.pastEvents().size(), 4);
    ASSERT_EQ(h.eventsForCurrentTime().size(), 0);
    ASSERT_EQ(h.futureEvents().size(), 0);
}

TEST(Hourglass, AdvanceTime)
{
    hourglass<DumbEvent> h;

    ASSERT_EQ(h.currentTime(), 0);

    h.advanceTime();
    ASSERT_EQ(h.currentTime(), 1);

    h.advanceTime();
    ASSERT_EQ(h.currentTime(), 2);

    h.advanceTime();
    ASSERT_EQ(h.currentTime(), 3);

    h.advanceTime();
    ASSERT_EQ(h.currentTime(), 4);
}
