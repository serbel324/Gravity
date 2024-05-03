#pragma once

#include <algorithm>
#include <chrono>
#include <rengine/core/graphics.h>
#include "mpmc_queue.h"

union UintFloat {
    uint32_t ui;
    float f;
};

union Position {
    Vec2f coordinates;
    uint64_t raw;
};

struct Star {
    std::atomic<uint64_t> position;
    Vec2f velocity;
    float mass;

    std::atomic<float> lastElapsed = 0;

    using Clock = std::chrono::steady_clock;
    using Timestamp = std::chrono::time_point<Clock>;
    using Duration = std::chrono::duration<float>;
    using Ns = std::chrono::nanoseconds;
    Timestamp lastTs;

    float UpdateTimestamp() {
        static UintFloat converter;
        Timestamp now = Clock::now();
        Duration duration = now - lastTs;
        float elapsedNs = std::chrono::duration_cast<Ns>(duration).count();
        float elapsedMs = elapsedNs / 1'000'000;
        converter.f = elapsedMs;
        lastElapsed.store(converter.ui);
        lastTs = now;
        return std::min(elapsedMs, 1000.f);
    }
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
