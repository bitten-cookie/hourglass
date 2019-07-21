#include <gtest/gtest.h>

#include "bittencookie/hourglass.hpp"

#include <memory>

using namespace bittencookie;

class SimpleEvent
{
public:
    explicit SimpleEvent(int v) : value_(v) {}
    virtual ~SimpleEvent() = default;
    virtual int value() const { return value_; }

protected:
    int value_;
};

using SimpleEvent_uptr = std::unique_ptr<SimpleEvent>;

TEST(Hourglass, SupportsUniquePtr)
{
    hourglass<SimpleEvent_uptr> h;
    auto e = std::make_unique<SimpleEvent>(10);
    h.addEvent(0, std::move(e));

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();
    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get()->value(), 10);
}

TEST(Hourglass, SupportsUniquePtrInPlaceConstruct)
{
    hourglass<SimpleEvent_uptr> h;
    h.addEvent(0, 10);

    ASSERT_EQ(h.currentTime(), 0);

    const auto& events = h.eventsForCurrentTime();
    ASSERT_EQ(events.size(), 1);

    const auto& event = events[0];
    ASSERT_EQ(event.get()->value(), 10);
}
