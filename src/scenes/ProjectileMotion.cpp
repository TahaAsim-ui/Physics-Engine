#include "ProjectileMotion.hpp"
#include <cmath>
#include <string>

constexpr float ProjectileMotion::kAngles[];

static const sf::Color kProjColors[] = {
    sf::Color(255, 220,  50),
    sf::Color( 50, 220, 255),
    sf::Color(255,  80, 120),
    sf::Color( 80, 255, 140),
    sf::Color(220,  80, 255),
    sf::Color(255, 160,  40),
};

void ProjectileMotion::setup(World& world) {
    world.reset();
    world.gravity = {0.f, 450.f};
    m_timer    = 0.f;
    m_angleIdx = 0;

    // Cannon base (static)
    world.addBody(Body::staticRect({70.f, 690.f}, 60.f, 30.f, sf::Color(90, 90, 110)));
    fireProjectile(world);
}

void ProjectileMotion::fireProjectile(World& world) {
    float angleDeg = kAngles[m_angleIdx % 6];
    float rad      = angleDeg * 3.14159265f / 180.f;
    sf::Color col  = kProjColors[m_angleIdx % 6];

    auto& b = world.addBody(Body::circle({70.f, 660.f}, 12.f, 1.f, 0.4f, 0.2f, col));
    b.vel   = { kSpeed * std::cos(rad), -kSpeed * std::sin(rad) };  // negative y = upward

    // Remove old projectiles that have settled (keep last 6)
    int alive = 0;
    for (const auto& body : world.bodies)
        if (!body.isStatic) ++alive;

    if (alive > 7) {
        for (auto& body : world.bodies) {
            if (!body.isStatic) { body.alive = false; break; }
        }
    }

    m_angleIdx = (m_angleIdx + 1) % 6;
}

void ProjectileMotion::update(World& world, float dt) {
    m_timer += dt;
    if (m_timer >= m_interval) {
        m_timer = 0.f;
        fireProjectile(world);
    }
}

void ProjectileMotion::renderOverlay(sf::RenderWindow& window, const sf::Font& font) {
    // Show launch angle of next projectile
    int nextAngle = static_cast<int>(kAngles[m_angleIdx % 6]);
    sf::Text label(font, "Next launch: " + std::to_string(nextAngle) + " deg", 16u);
    label.setFillColor(sf::Color(200, 200, 200));
    label.setPosition({10.f, 670.f});
    window.draw(label);

    // Cannon barrel direction indicator
    float rad = kAngles[m_angleIdx % 6] * 3.14159265f / 180.f;
    float len = 55.f;
    sf::Vertex line[2] = {
        sf::Vertex{{70.f, 660.f}, sf::Color(200, 200, 200)},
        sf::Vertex{{70.f + len * std::cos(rad), 660.f - len * std::sin(rad)}, sf::Color(200, 200, 200)},
    };
    window.draw(line, 2, sf::PrimitiveType::Lines);
}
