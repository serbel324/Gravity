#include "continuous_world.h"

#include <algorithm>
#include <thread>
#include <atomic>
#include <condition_variable>

ContinuousWorld::ContinuousWorld(Vec2i size)
    : World(size)
    , _queue(maxStarsNumber)
{
    std::cout << std::thread::hardware_concurrency() << " threads will be used" << std::endl;
}

void ContinuousWorld::Tick(float) {
}

void ContinuousWorld::Run() {
    auto work = [&] () {
        while (true) {
            size_t star;
            _queue.pop(star);
            Vec2f force{0, 0};
            Position pos1{};
            pos1.raw = stars[star].position.load();
            for (size_t j = 0; j < starsNumber; ++j) {
                if (j == star) {
                    continue;
                }

                Position pos2{};
                pos2.raw = stars[j].position.load();
                Vec2f delta = pos2.coordinates - pos1.coordinates;
                float dist = std::max(std::pow(delta.magnitude(), 2), 1.);
                force += delta.normalized() * stars[star].mass * stars[j].mass / dist * G;
            }
            float elapsedSec = stars[star].UpdateTimestamp() / 1000;
            stars[star].velocity += force / stars[star].mass * elapsedSec;

            pos1.raw = stars[star].position.load();
            pos1.coordinates += stars[star].velocity * elapsedSec;
            stars[star].position.store(pos1.raw);
            _queue.push(star);
        }
    };

    for (size_t i = 0; i < starsNumber; ++i) {
        _queue.push(i);
    }

    size_t workersNum = std::thread::hardware_concurrency() - 1;

    _threads.resize(workersNum);
    for (size_t i = 0; i < workersNum; ++i) {
        _threads[i] = std::thread(work);
    }

}