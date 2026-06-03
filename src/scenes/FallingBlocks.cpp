#include "FallingBlocks.hpp"

void FallingBlocks::setup(World& world) {
    world.reset();
    world.gravity = {0.f, 500.f};

    // Varied blocks: pos-x, pos-y, width, height, mass, color
    struct BlockDef { float x, y, w, h, mass; sf::Color col; };
    const BlockDef defs[] = {
        { 200.f,  80.f, 90.f, 40.f, 4.f, sf::Color(180,  90,  40) },
        { 500.f, 120.f, 70.f, 50.f, 3.f, sf::Color(140, 110,  60) },
        { 750.f,  60.f, 80.f, 35.f, 3.5f,sf::Color(160,  80,  50) },
        {1000.f, 100.f, 60.f, 60.f, 4.f, sf::Color(120, 100,  70) },
        { 350.f, 200.f,100.f, 30.f, 4.5f,sf::Color(190, 120,  40) },
        { 640.f, 180.f, 55.f, 55.f, 3.f, sf::Color(150,  70,  90) },
        { 870.f, 140.f, 75.f, 45.f, 3.5f,sf::Color(100, 130,  80) },
        { 450.f,  40.f, 65.f, 65.f, 5.f, sf::Color(170,  95,  55) },
    };

    for (const auto& d : defs) {
        world.addBody(Body::rect({d.x, d.y}, d.w, d.h, d.mass, 0.3f, 0.6f, d.col));
    }
}
