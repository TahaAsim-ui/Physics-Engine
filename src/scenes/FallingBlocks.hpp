#pragma once
#include "Scene.hpp"

class FallingBlocks : public Scene {
public:
    void setup(World& world) override;
    const char* name()     const override { return "Falling Blocks"; }
    const char* controls() const override { return "R: Reset"; }
};
