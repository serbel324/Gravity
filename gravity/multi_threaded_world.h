#pragma once

#include "world.h"

#include <contrib/rigtorp/mpmc_queue.h>

#include <library/vec2.h>

class MultiThreadedWorld : public World {
public:
    MultiThreadedWorld(Vec2i size);

    void Tick(float elapsedSec) override;
    void Run() override;

private:
    using MPMCQueue = rigtorp::mpmc::Queue<size_t>;
    // using MPMCQueue = MutexMPMCQueue<size_t>;
    MPMCQueue _queue;
};
