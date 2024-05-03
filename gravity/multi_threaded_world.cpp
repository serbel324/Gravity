#include "multi_threaded_world.h"

#include <algorithm>
#include <thread>
#include <atomic>
#include <condition_variable>

MultiThreadedWorld::MultiThreadedWorld(Vec2i size)
    : World(size)
    , _queue(maxStarsNumber)
{
    std::cout << std::thread::hardware_concurrency() << " threads will be used" << std::endl;
}

void MultiThreadedWorld::Tick(float elapsedSec) {
    std::atomic<int32_t> tasksPending = starsNumber;
    std::atomic<bool> lockPassed = false;

    size_t workersNum = std::thread::hardware_concurrency() - 1;
    auto work = [&] () {
        while (tasksPending.fetch_sub(1) > 0) {
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
            stars[star].velocity += force / stars[star].mass * elapsedSec;
        }
    };

    for (size_t i = 0; i < starsNumber; ++i) {
        _queue.push(i);
    }


    std::vector<std::thread> threads;
    threads.resize(workersNum);

    for (size_t i = 0; i < workersNum; ++i) {
        threads[i] = std::thread(work);
    }

    for (size_t i = 0; i < workersNum; ++i) {
        threads[i].join();
    }

    for (size_t i = 0; i < starsNumber; ++i) {
        Position pos1{};
        pos1.raw = stars[i].position.load();
        pos1.coordinates += stars[i].velocity * elapsedSec;
        stars[i].position.store(pos1.raw);
    }

}

void MultiThreadedWorld::Run() {
}