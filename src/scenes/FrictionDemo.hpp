#pragma once
#include "Scene.hpp"
#include <array>

class FrictionDemo : public Scene {
public:
    void setup(World& world) override;
    void renderOverlay(sf::RenderWindow& window, const sf::Font& font) override;

    const char* name()     const override { return "Friction Demo"; }
    const char* controls() const override { return "R: Relaunch"; }

private:
    static constexpr float kMu[]    = {0.0f, 0.12f, 0.35f, 0.75f};
    static constexpr float kInitVel = 420.f;
    static constexpr float kRadius  = 24.f;
    static constexpr float kLaunchY = 650.f;   // near floor
    static constexpr int   kCount   = 4;

    static const sf::Color kColors[kCount];
};
