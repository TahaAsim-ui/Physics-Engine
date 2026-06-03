#pragma once
#include "Scene.hpp"

class BouncingBalls : public Scene {
public:
    void setup(World& world) override;
    const char* name()     const override { return "Bouncing Balls"; }
    const char* controls() const override { return "R: Reset"; }
};
