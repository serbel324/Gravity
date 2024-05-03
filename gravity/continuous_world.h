#pragma once

#include <thread>

#include "world.h"

#include <contrib/rigtorp/mpmc_queue.h>
#include <library/vec2.h>

class ContinuousWorld : public World {
public:
    ContinuousWorld(Vec2i size);

    void Tick(float) override;
    void Run() override;

private:
    using MPMCQueue = rigtorp::mpmc::Queue<size_t>;
    // using MPMCQueue = MutexMPMCQueue<size_t>;
    MPMCQueue _queue;

    std::vector<std::thread> _threads;
};
