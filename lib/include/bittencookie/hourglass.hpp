#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <ostream>

#include "types.hpp"

namespace bittencookie
{
    /// \brief A simple class that allows iteration over a time-series
    ///
    /// \tparam Event A class that represents the event which we are storing
    /// \tparam Time A class that needs to implement operator++ (to move the time forward)
    /// and operator< to order the times chronologically. Time also needs to be default constructible
    template<class Event, class Time = int>
    class hourglass
    {
    public:
        using EventRef = std::reference_wrapper<const Event>;
        using EventIt = typename std::multimap<Time,Event>::iterator;
        using CEventIt = typename std::multimap<Time,Event>::const_iterator;

        hourglass() = default;
        explicit hourglass(Time&& t) : time_(std::forward<Time>(t)) {}

        const Time& currentTime() const { return time_; }
        void advanceTime() { ++time_; }

        void addEvent(Time&& t, Event&& e) { timeline_.emplace(std::forward<Time>(t), std::forward<Event>(e)); }

        template<class SubType = Event, class ...EventArgs>
        void emplaceEvent(Time&& t, EventArgs... args)
        {
            if constexpr(is_unique_pointer_v<SubType>)
            {
                using UnderlyingType = typename SubType::element_type;
                timeline_.emplace(std::forward<Time>(t), std::make_unique<UnderlyingType>(std::forward<EventArgs>(args)...));
            }
            else if constexpr(is_unique_pointer_v<Event>)
            {
                timeline_.emplace(std::forward<Time>(t), std::make_unique<SubType>(std::forward<EventArgs>(args)...));
            }
            else
            {
                addEvent(std::forward<Time>(t), SubType(std::forward<EventArgs>(args)...));
            }
        }

        bool hasEventsForCurrentTime() const { return timeline_.count(time_) != 0; }
        std::vector<EventRef> eventsForCurrentTime() const { return this->eventsOnRange(timeline_.equal_range(time_)); }

        /// Returns events in the range [start, now[
        std::vector<EventRef> pastEvents() const
        {
            return this->eventsOnRange({std::begin(timeline_), timeline_.lower_bound(time_)});
        }

        /// Returns events in the range ]now, end]
        std::vector<EventRef> futureEvents() const
        {
            return this->eventsOnRange({timeline_.upper_bound(time_), std::end(timeline_)});
        }

    protected:
        Time time_ = {};
        std::multimap<Time, Event> timeline_ = {};

    private:
        std::vector<EventRef> eventsOnRange(std::pair<CEventIt,CEventIt> range) const
        {
            std::vector<EventRef> events;
            std::transform(range.first, range.second, std::back_inserter(events), [](auto& it)
            {
                return EventRef(it.second);
            });

            return events;
        }
    };
}

template<class Event, class Time>
std::ostream& operator<<(std::ostream& os, const bittencookie::hourglass<Event,Time>& h)
{
    os << "[" << h.currentTime() << "] ";
    if( h.hasEventsForCurrentTime() )
    {
        os << "Has events!" << std::endl;
        const auto events = h.eventsForCurrentTime();

        for(auto e: events)
        {
            os << "  -> " << e << std::endl;
        }
    }
    else
    {
        os << "No events!" << std::endl;
    }
    return os;
}
