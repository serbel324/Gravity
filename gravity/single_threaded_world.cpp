#include "single_threaded_world.h"

#include <algorithm>

SingleThreadedWorld::SingleThreadedWorld(Vec2i size)
    : World(size)
{}

void SingleThreadedWorld::Tick(float elapsedSec) {
    for (size_t i = 0; i < starsNumber; ++i) {
        Vec2f force{0, 0};
        Position pos1{};
        pos1.raw = stars[i].position.load();
        for (size_t j = 0; j < starsNumber; ++j) {
            if (i == j) {
                continue;
            }

            Position pos2{};
            pos2.raw = stars[j].position.load();
            Vec2f delta = pos2.coordinates - pos1.coordinates;
            float dist = std::max(std::pow(delta.magnitude(), 2), 1.);
            force += delta.normalized() * stars[i].mass * stars[j].mass / dist * G;
        }
        stars[i].velocity += force / stars[i].mass * elapsedSec;
    }

    UintFloat converter;
    for (size_t i = 0; i < starsNumber; ++i) {
        converter.f = elapsedSec * 1000;
        stars[i].lastElapsed.store(converter.ui);
        Position pos1{};
        pos1.raw = stars[i].position.load();
        pos1.coordinates += stars[i].velocity * elapsedSec;
        stars[i].position.store(pos1.raw);
    }
}

void SingleThreadedWorld::Run() {
}