#include <gtest/gtest.h>

#include "bittencookie/hourglass.hpp"

using namespace bittencookie;

namespace
{
    class SimpleEvent
    {
    public:
        explicit SimpleEvent(int v) : value_(v) {}
        virtual ~SimpleEvent() = default;
        virtual int value() const { return value_; }

    protected:
        int value_;
    };

    class DoubleEvent : public SimpleEvent
    {
    public:
        explicit DoubleEvent(int v) : SimpleEvent(2*v) {}
    };
}

TEST(Hourglass, EventTest)
{
    hourglass<SimpleEvent> h;
    h.emplaceEvent(0, 10);

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();

    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get().value(), 10);
}

TEST(Hourglass, MoveEvent)
{
    hourglass<SimpleEvent> h;
    h.addEvent(0, SimpleEvent(10));

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();

    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get().value(), 10);
}


TEST(Hourglass, SubEvent)
{
    hourglass<SimpleEvent> h;
    h.emplaceEvent<DoubleEvent>(0, 10);

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();

    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get().value(), 20);
}

TEST(Hourglass, SubEventMove)
{
    hourglass<SimpleEvent> h;
    h.addEvent(0, DoubleEvent(10));

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();

    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get().value(), 20);
}