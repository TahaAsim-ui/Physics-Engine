#pragma once
#include "Scene.hpp"
#include <vector>

class ProjectileMotion : public Scene {
public:
    void setup(World& world) override;
    void update(World& world, float dt) override;
    void renderOverlay(sf::RenderWindow& window, const sf::Font& font) override;

    const char* name()     const override { return "Projectile Motion"; }
    const char* controls() const override { return "Auto-fires at varying angles"; }

private:
    float m_timer     = 0.f;
    float m_interval  = 1.8f;
    int   m_angleIdx  = 0;

    static constexpr float kAngles[] = {25.f, 35.f, 45.f, 55.f, 65.f, 75.f};
    static constexpr float kSpeed    = 620.f;

    void fireProjectile(World& world);
};
