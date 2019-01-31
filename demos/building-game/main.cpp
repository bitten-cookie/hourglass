#include <iostream>
#include "hourglass/hourglass.hpp"

#include "gameEvent.hpp"
#include "render.hpp"

static int static_id_counter = 0;

struct RandomEvent
{

};

struct Building
{
    Building(std::string n, int cost, int income)
        : name(std::move(n)), cost_to_build(cost), income_per_day(income), id(static_id_counter++) {}

    int id;
    std::string name;
    int cost_to_build;
    int income_per_day;
};

class game_state
{
public:
    game_state()
    {
        addBuilding({"House 1", 100, 10});
        available_buildings_.emplace_back("Old House", 100, 5);
        available_buildings_.emplace_back("Regular House", 200, 15);
        available_buildings_.emplace_back("Penthouse", 300, 20);
    }

    void addBuilding(Building&& b) { owned_buidings_.push_back(std::move(b)); }

    void buyBuilding(int building_id)
    {
        auto building_it = std::find_if(available_buildings_.begin(), available_buildings_.end(), [=](const Building& b)
        {
            return b.id == building_id;
        });

        if(building_it != available_buildings_.end())
        {
            auto building = *building_it;
            if( money_ - building.cost_to_build >= 0 )
            {
                money_ -= building.cost_to_build;
                addBuilding(std::move(building));
                available_buildings_.erase(building_it);
            }
        }
    }

    void sellHouse(int building_id)
    {
        auto building_it = std::find_if(owned_buidings_.begin(), owned_buidings_.end(), [=](const Building& b)
        {
            return b.id == building_id;
        });

        if(building_it != owned_buidings_.end())
        {
            auto building = *building_it;
            money_ += static_cast<int>(building.cost_to_build * 0.9);

            available_buildings_.push_back(building);
            owned_buidings_.erase(building_it);
        }
    }

    std::vector<Building> owned_buidings_;
    std::vector<Building> available_buildings_;

    int money_ = 120;
};

class game
{
public:
    void startOfTheDay()
    {
        const auto today_events = random_.eventsForCurrentTime();
        for(const auto& event : today_events)
        {

        }
    }

    void endOfTheDay()
    {
        for(const auto& b : gs_.owned_buidings_)
        {
            gs_.money_ += b.income_per_day;
        }

        random_.advanceTime();
    }

    hourglass::hourglass<RandomEvent> random_{0};
    game_state gs_;
};

int main(int, char**)
{
    game game_;

    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    auto window = setupWindowSystem();
    if(window == nullptr) return -1;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

        {
            ImGuiWindowFlags window_flags = 0;
            window_flags |= ImGuiWindowFlags_NoCollapse;
            window_flags |= ImGuiWindowFlags_NoNav;

            ImGui::Begin("Building Game!", nullptr, window_flags);
            ImGui::TextColored(ImVec4(1.0f,0.0f,1.0f,1.0f), "Day %d", game_.random_.currentTime());
            ImGui::Text("Money: %d", game_.gs_.money_);
            ImGui::Checkbox("Demo Window", &show_demo_window);
            if( ImGui::Button("Next Day!") )
            {
                game_.endOfTheDay();
                game_.startOfTheDay();
            }

            ImGuiTreeNodeFlags flags = 0;
            flags |= ImGuiTreeNodeFlags_DefaultOpen;

            if (ImGui::CollapsingHeader("Owned Houses", flags))
            {
                ImGui::Columns(3, "mixed", true);

                for(const auto& house : game_.gs_.owned_buidings_)
                {
                    if (ImGui::GetColumnIndex() == 0)
                        ImGui::Separator();

                    ImGui::TextColored(ImVec4(1.0f,1.0f,0.0f,1.0f), "%s", house.name.c_str());
                    ImGui::Text("Actual Value: %d", house.cost_to_build);
                    ImGui::Text("Per day: %d", house.income_per_day);

                    ImGui::PushID(house.id);
                    if( ImGui::Button("Sell") )
                    {
                        game_.gs_.sellHouse(house.id);
                    }
                    ImGui::PopID();

                    ImGui::NextColumn();
                }
            }

            ImGui::Columns(1);
            ImGui::Separator();

            if (ImGui::CollapsingHeader("Houses to Buy", flags))
            {
                ImGui::Columns(3, "mixed", true);

                for(const auto& house : game_.gs_.available_buildings_)
                {
                    if (ImGui::GetColumnIndex() == 0)
                        ImGui::Separator();

                    ImGui::TextColored(ImVec4(1.0f,1.0f,0.0f,1.0f), "%s", house.name.c_str());
                    ImGui::Text("Actual Value: %d", house.cost_to_build);
                    ImGui::Text("Per day: %d", house.income_per_day);

                    if( game_.gs_.money_ >= house.cost_to_build )
                    {
                        ImGui::PushID(house.id);
                        if( ImGui::Button("Buy") )
                        {
                            game_.gs_.buyBuilding(house.id);
                        }
                        ImGui::PopID();
                    }

                    ImGui::NextColumn();
                }
            }

            ImGui::Columns(1);
            ImGui::Separator();

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwMakeContextCurrent(window);
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}