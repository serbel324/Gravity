#pragma once

#include "world.h"

#include <library/vec2.h>

class SingleThreadedWorld : public World {
public:
    SingleThreadedWorld(Vec2i size);

    void Tick(float elapsedSec) override;
    void Run() override;
};
