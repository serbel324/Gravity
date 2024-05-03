#include <rengine/core/frame.h>
#include <rengine/core/color.h>
#include <library/vec2.h>
#include <library/ext_math.h>

#include <iostream>
#include <atomic>

#include "world.h"
#include "single_threaded_world.h"
#include "multi_threaded_world.h"

const Vec2i worldSize = {800, 800};

class MainFrame : public REngine::Frame {
public:
    using BraveNewWorld = SingleThreadedWorld;

public:
    MainFrame()
        : Frame(
            Frame::Settings{
                .id = "GravityFrame",
                .screenSize = worldSize,
            },
            nullptr,
            REngine::MakeGenericWindow(worldSize, "Gravity"))
        , _world(new BraveNewWorld(worldSize))
    {}

    void Initialize() override {
        size_t starsNum = 1000;
        std::cout << "Initialize " << starsNum << " stars" << std::endl;
        _world->GenerateStars(starsNum);

        font.loadFromFile("font.ttf");
    }

    bool Update(float elapsedMs) override {
        _world->Tick(0.01);

        totalMsElapsed += elapsedMs;
        window.push_back(elapsedMs);

        if (window.size() > maxWindowSize) {
            totalMsElapsed -= window.front();
            window.pop_front();
        }
        avgTickTime = totalMsElapsed / window.size();
    
        return Frame::Update(elapsedMs);
    }

    void Render() override {
        _world->Render(Gr());
        Gr()->SetFillColor(REngine::Color::RED);
        std::string text;
        text.resize(10);
        text.resize(std::snprintf(text.data(), 10, "%.2f", avgTickTime));
        Gr()->FillText(text, 0, 0, 30, font);
        Gr()->Present();
    }

private:
    sf::Font font;

    std::unique_ptr<World> _world;

    const size_t maxWindowSize = 1000;
    std::deque<float> window;

    float totalMsElapsed = 0;
    float avgTickTime = 0;
};
