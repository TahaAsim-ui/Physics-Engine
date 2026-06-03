#include "World.hpp"
#include "Collision.hpp"
#include <algorithm>
#include <cmath>

Body& World::addBody(Body b) {
    bodies.push_back(std::move(b));
    return bodies.back();
}

void World::clear()  { bodies.clear(); }

void World::reset() {
    bodies.clear();
    gravity = {0.f, 500.f};
    paused  = false;
}

void World::step(float dt) {
    if (paused) return;

    // Purge dead bodies
    bodies.erase(std::remove_if(bodies.begin(), bodies.end(),
        [](const Body& b){ return !b.alive; }), bodies.end());

    const std::size_t n = bodies.size();

    // Gravity + velocity cap
    for (auto& b : bodies) {
        if (b.isStatic) continue;
        b.vel += gravity * dt;
        b.vel.x = std::clamp(b.vel.x, -kMaxSpeed, kMaxSpeed);
        b.vel.y = std::clamp(b.vel.y, -kMaxSpeed, kMaxSpeed);
    }

    // Integrate positions
    for (auto& b : bodies) {
        if (!b.isStatic) b.pos += b.vel * dt;
    }

    // Collision resolution (multiple iterations improves stacking stability)
    for (int iter = 0; iter < kCollisionIterations; ++iter) {
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = i + 1; j < n; ++j) {
                Collision::resolve(bodies[i], bodies[j]);
            }
        }
    }

    // World-boundary resolution
    for (auto& b : bodies) {
        if (!b.isStatic) resolveWorldBounds(b, dt);
    }
}

void World::resolveWorldBounds(Body& b, float dt) {
    const float e  = b.restitution;
    const float mu = b.friction;

    auto applyFloorFriction = [&]() {
        float decel = mu * std::abs(gravity.y);
        if (b.vel.x > 0.f)      b.vel.x = std::max(0.f, b.vel.x - decel * dt);
        else if (b.vel.x < 0.f) b.vel.x = std::min(0.f, b.vel.x + decel * dt);
    };

    if (b.shape == ShapeType::Circle) {
        float r = b.radius;
        bool  onFloor = false;

        if (b.pos.x - r < 0.f)      { b.pos.x = r;          b.vel.x =  std::abs(b.vel.x) * e; }
        if (b.pos.x + r > width)     { b.pos.x = width - r;  b.vel.x = -std::abs(b.vel.x) * e; }
        if (b.pos.y - r < 0.f)      { b.pos.y = r;           b.vel.y =  std::abs(b.vel.y) * e; }
        if (b.pos.y + r > height)    { b.pos.y = height - r; b.vel.y = -std::abs(b.vel.y) * e; onFloor = true; }

        if (onFloor || b.pos.y + r >= height - 1.f) applyFloorFriction();

    } else {
        float hw = b.halfSize.x, hh = b.halfSize.y;
        bool  onFloor = false;

        if (b.pos.x - hw < 0.f)     { b.pos.x = hw;           b.vel.x =  std::abs(b.vel.x) * e; }
        if (b.pos.x + hw > width)    { b.pos.x = width - hw;   b.vel.x = -std::abs(b.vel.x) * e; }
        if (b.pos.y - hh < 0.f)     { b.pos.y = hh;            b.vel.y =  std::abs(b.vel.y) * e; }
        if (b.pos.y + hh > height)   { b.pos.y = height - hh;  b.vel.y = -std::abs(b.vel.y) * e; onFloor = true; }

        if (onFloor || b.pos.y + hh >= height - 1.f) applyFloorFriction();
    }
}

void World::render(sf::RenderWindow& window) const {
    for (const auto& b : bodies) {
        if (!b.alive) continue;

        if (b.shape == ShapeType::Circle) {
            sf::CircleShape shape(b.radius);
            shape.setOrigin({b.radius, b.radius});
            shape.setPosition({b.pos.x, b.pos.y});
            shape.setFillColor(b.color);
            sf::Color outline = b.isStatic
                ? sf::Color(120, 120, 150, 200)
                : sf::Color(255, 255, 255, 50);
            shape.setOutlineColor(outline);
            shape.setOutlineThickness(1.5f);
            window.draw(shape);
        } else {
            sf::RectangleShape shape({b.halfSize.x * 2.f, b.halfSize.y * 2.f});
            shape.setOrigin({b.halfSize.x, b.halfSize.y});
            shape.setPosition({b.pos.x, b.pos.y});
            shape.setFillColor(b.color);
            sf::Color outline = b.isStatic
                ? sf::Color(120, 120, 150, 200)
                : sf::Color(255, 255, 255, 50);
            shape.setOutlineColor(outline);
            shape.setOutlineThickness(1.5f);
            window.draw(shape);
        }
    }
}
