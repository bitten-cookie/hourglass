#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <ostream>

namespace hourglass
{
    template<class Event, class Time = int>
    class hourglass
    {
    public:
        using EventRef = std::reference_wrapper<const Event>;
        using EventIt = typename std::multimap<Time,Event>::iterator;
        using CEventIt = typename std::multimap<Time,Event>::const_iterator;

        hourglass() = default;
        explicit hourglass(Time t) : time_(t) {}

        Time currentTime() const { return time_; }
        void advanceTime() { time_++; } //todo: implement operator++

        void addEvent(Time&& t, Event&& e) { timeline_.emplace(std::forward<Time>(t), std::forward<Event>(e)); }

        bool hasEventsForCurrentTime() const { return timeline_.count(time_) != 0; }
        std::vector<EventRef> eventsForCurrentTime() const { return this->eventsOnRange(timeline_.equal_range(time_)); }

        std::vector<EventRef> pastEvents() const
        {
            return this->eventsOnRange({std::begin(timeline_), timeline_.lower_bound(time_)});
        }

        std::vector<EventRef> futureEvents() const
        {
            return this->eventsOnRange({timeline_.upper_bound(time_), std::end(timeline_)});
        }

        friend std::ostream& operator<<(std::ostream& os, const hourglass& h)
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

    protected:
        Time time_ = {}; // must have the ++ operator
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
