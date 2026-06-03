#include "BouncingBalls.hpp"

void BouncingBalls::setup(World& world) {
    world.reset();
    world.gravity = {0.f, 400.f};

    struct BallDef { float x, y, r, mass, vx, vy; sf::Color col; };
    const BallDef defs[] = {
        { 200.f, 200.f, 28.f, 3.f,  220.f, 180.f, sf::Color(220,  60,  60) },
        { 400.f, 150.f, 22.f, 2.f, -190.f, 230.f, sf::Color(255, 140,   0) },
        { 600.f, 300.f, 35.f, 5.f,  150.f,-200.f, sf::Color(255, 220,  50) },
        { 800.f, 180.f, 18.f, 1.5f,-220.f, 160.f, sf::Color( 60, 200,  60) },
        {1000.f, 250.f, 25.f, 2.5f, 180.f,-180.f, sf::Color( 50, 190, 220) },
        { 300.f, 400.f, 20.f, 2.f,  260.f,-150.f, sf::Color( 60,  80, 220) },
        { 700.f, 350.f, 30.f, 4.f, -170.f, 200.f, sf::Color(160,  60, 220) },
        { 500.f, 120.f, 16.f, 1.f,  200.f, 240.f, sf::Color(220,  80, 160) },
        { 150.f, 500.f, 24.f, 2.f,  240.f,-120.f, sf::Color(200, 200,  80) },
        { 950.f, 450.f, 20.f, 2.f, -200.f,-160.f, sf::Color( 80, 220, 160) },
    };

    for (const auto& d : defs) {
        auto& b = world.addBody(Body::circle({d.x, d.y}, d.r, d.mass, 0.85f, 0.05f, d.col));
        b.vel = {d.vx, d.vy};
    }
}
