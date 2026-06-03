#include "ObjectCollision.hpp"

static void addBilliardRack(World& world) {
    const float R    = 22.f;
    const float gap  = R * 2.f + 1.f;
    const float cx   = 820.f;
    const float cy   = 360.f;
    const sf::Color col(220, 200, 80);

    // Triangular billiard rack (3 rows)
    float rowX = cx;
    float rowY = cy;
    for (int row = 0; row < 4; ++row) {
        for (int i = 0; i <= row; ++i) {
            float bx = rowX;
            float by = rowY - row * gap * 0.5f + i * gap;
            world.addBody(Body::circle({bx, by}, R, 2.f, 0.92f, 0.04f, col));
        }
        rowX += gap * 0.866f;   // sqrt(3)/2
    }
}

static void fireCueBall(World& world) {
    auto& cue = world.addBody(
        Body::circle({180.f, 360.f}, 22.f, 2.f, 0.92f, 0.04f, sf::Color(240, 240, 240)));
    cue.vel = {580.f, 0.f};
}

void ObjectCollision::setup(World& world) {
    world.reset();
    world.gravity = {0.f, 0.f};   // top-down billiard table, no gravity

    addBilliardRack(world);
    fireCueBall(world);
}

void ObjectCollision::handleEvent(const sf::Event& event, World& world, sf::RenderWindow&) {
    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        if (key->code == sf::Keyboard::Key::Space) {
            fireCueBall(world);
        }
    }
}
