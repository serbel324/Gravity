#include <cassert>

#include <library/ext_math.h>

#include "world.h"

World::World(Vec2i size)
    : _worldSize(size)
{}

void World::GenerateStars(size_t starsNum) {
    assert(starsNum <= maxStarsNumber);
    starsNumber = starsNum;

    for (size_t i = 0; i < starsNumber; ++i) {
        Position pos{};
        pos.coordinates = { ExtMath::RandomDouble(0, _worldSize.x), ExtMath::RandomDouble(0, _worldSize.y) };
        stars[i].position.store(pos.raw);
        stars[i].mass = 1;
        stars[i].velocity = {0, 0};
    }
}

void World::Render(REngine::Graphics* gr) {
    gr->SetFillColor(REngine::Color::BLACK);
    gr->Fill();

    gr->SetFillColor(REngine::Color::WHITE);
    for (size_t i = 0; i < starsNumber; ++i) {
        Position pos{};
        pos.raw = stars[i].position.load();
        gr->DrawCircle(pos.coordinates, 2);
    }
}
