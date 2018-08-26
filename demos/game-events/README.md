# Simple Game Event Example

Imagine you're building a game. For the sake of simplicity, consider that you're tracking the hero's 
state as:

```cpp
struct player_status
{
    int hp = 100;
    int money = 300;
};
```

and your *event-driven* design has a message (`SimpleEvent`), which receives the `game_state`, 
applies its behavior and returns the **new** `game_state`:

```cpp
struct SimpleEvent
{
    std::string message;
    std::function<game_status(game_status&&)> behavior;
};
```

So, you wish to trigger some events as the game goes on.
Remember that: `addEvent` function takes 2 parameters: the Event (`SimpleEvent` in this case) and the 
time-point when it should be triggered.

So, you can do it by:

```cpp
g.hourglass_.addEvent({"You found a life pack (+10)", [](game_status g){
    g.player.hp += 10;
    return g;
}}, 1);
g.hourglass_.addEvent({"End of the month. Here's your salary: 200", [](game_status g){
    g.player.money += 200;
    return g;
}}, 2);
g.hourglass_.addEvent({"You've got a cold. (-70)", [](game_status g){
    g.player.hp -= 70;
    return g;
}}, 3);
```

**Hourglass** enables you to simulate the time passing through. With a game loop as simple as:

```cpp
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
```

```
DAY [0] starts with 
  money: 300 and HP: 100

DAY [1] starts with 
  money: 300 and HP: 100

  Event: You found a life pack (+10)
  money: 300 and HP: 110

DAY [2] starts with 
  money: 300 and HP: 110

  Event: End of the month. Here's your salary: 200
  money: 500 and HP: 110

DAY [3] starts with 
  money: 500 and HP: 110

  Event: You've got a cold. (-70)
  money: 500 and HP: 40
```
