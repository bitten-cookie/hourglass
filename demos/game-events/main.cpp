#include <iostream>
#include "hourglass/hourglass.hpp"

struct player_status
{
    int hp = 100;
    int money = 300;
};

void print_player_status(const player_status& s)
{
    std::cout << "  money: " << s.money << " and HP: " << s.hp << std::endl;
}

struct SimpleEvent;

struct game_status
{
    hourglass::hourglass<SimpleEvent> hourglass_{0};
    player_status player{};
};

struct SimpleEvent
{
    std::string message;
    std::function<game_status(game_status&&)> behavior;

    friend std::ostream& operator<<(std::ostream& os, const SimpleEvent& event)
    {
        os << "  Event: " <<  event.message;
        return os;
    }
};

int main()
{
    constexpr auto number_of_days_to_simulate = 4;
    game_status g{};
    g.hourglass_.addEvent(1, {"You found a life pack (+10)", [](game_status g){
        g.player.hp += 10;
        return g;
    }});
    g.hourglass_.addEvent(2, {"End of the month. Here's your salary: 200", [](game_status g){
        g.player.money += 200;
        return g;
    }});
    g.hourglass_.addEvent(3, {"You've got a cold. (-70)", [](game_status g){
        g.player.hp -= 70;
        return g;
    }});


    for(auto i = 0; i < number_of_days_to_simulate; i++)
    {
        // simulate today's day
        std::cout << "DAY [" << g.hourglass_.currentTime() << "] starts with " << std::endl;
        print_player_status(g.player);
        std::cout << std::endl;

        for(const auto& e : g.hourglass_.eventsForCurrentTime())
        {
            const auto& evt = e.get();
            std::cout << evt << std::endl;
            g = evt.behavior(std::move(g));
            print_player_status(g.player);
            std::cout << std::endl;
        }

        // next day
        g.hourglass_.advanceTime();
    }

    return 0;
}
