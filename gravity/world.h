#pragma once

#include <rengine/core/graphics.h>
#include "mpmc_queue.h"

union Position {
    Vec2f coordinates;
    uint64_t raw;
};

struct Star {
    std::atomic<uint64_t> position;
    Vec2f velocity;
    float mass;
};

class World {
public:
    World(Vec2i size);
    virtual ~World() = default;

public:
    void GenerateStars(size_t starsNumber);
    virtual void Tick(float elapsedSec) = 0;
    virtual void Run() = 0;
    void Render(REngine::Graphics* gr);

private:
    Vec2i _worldSize;
    size_t _starsNum;

public:
    static constexpr size_t maxStarsNumber = 1 << 20;
    size_t starsNumber = 0;
    std::array<Star, maxStarsNumber> stars;

    static constexpr float G = 1000;
};
