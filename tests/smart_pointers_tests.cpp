#include <gtest/gtest.h>

#include "bittencookie/hourglass.hpp"

#include <memory>

using namespace bittencookie;

namespace
{
    class BaseEvent
    {
    public:
        virtual ~BaseEvent() = default;
        virtual int value() const = 0;
    };

    class SimpleEvent : public BaseEvent
    {
    public:
        int value() const override { return 10; }
    };

    class DoubleEvent : public BaseEvent
    {
    public:
        int value() const override { return 20; }
    };

    using BaseEvent_uptr = std::unique_ptr<BaseEvent>;
}


TEST(Hourglass, SupportsUniquePtr)
{
    std::vector<int> a;
    a.push_back(1);
    hourglass<BaseEvent_uptr> h;
    auto e = std::make_unique<SimpleEvent>();
    h.addEvent(0, std::move(e));

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();
    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get()->value(), 10);
}

TEST(Hourglass, SupportsUniquePtrInPlaceConstruct)
{
    hourglass<BaseEvent_uptr> h;
    h.emplaceEvent<SimpleEvent>(0);

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();
    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get()->value(), 10);
}

TEST(Hourglass, SupportsDerivedPointers)
{
    hourglass<BaseEvent_uptr> h;
    auto e = std::make_unique<DoubleEvent>();
    h.addEvent(0, std::move(e));

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();
    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get()->value(), 20);
}

TEST(Hourglass, SupportsDerivedPointersInPlaceConstruct)
{
    hourglass<BaseEvent_uptr> h;
    h.emplaceEvent<DoubleEvent>(0);

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();
    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get()->value(), 20);
}

