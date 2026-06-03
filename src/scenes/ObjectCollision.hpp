#pragma once
#include "Scene.hpp"

class ObjectCollision : public Scene {
public:
    void setup(World& world) override;
    void handleEvent(const sf::Event& event, World& world, sf::RenderWindow& window) override;
    const char* name()     const override { return "Object Collisions"; }
    const char* controls() const override { return "Space: Fire cue ball  R: Reset"; }
};
