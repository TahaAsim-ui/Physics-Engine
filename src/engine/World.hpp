#pragma once
#include "Body.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class World {
public:
    std::vector<Body> bodies;
    Vec2  gravity{0.f, 500.f};
    float width, height;
    bool  paused = false;

    World(float w, float h) : width(w), height(h) {}

    Body& addBody(Body b);
    void  clear();
    void  reset();
    void  step(float dt);
    void  render(sf::RenderWindow& window) const;

private:
    static constexpr int   kCollisionIterations = 5;
    static constexpr float kMaxSpeed            = 2500.f;

    void resolveWorldBounds(Body& b, float dt);
};
