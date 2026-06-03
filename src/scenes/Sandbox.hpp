#pragma once
#include "Scene.hpp"

class Sandbox : public Scene {
public:
    void setup(World& world) override;
    void handleEvent(const sf::Event& event, World& world, sf::RenderWindow& window) override;
    void renderOverlay(sf::RenderWindow& window, const sf::Font& font) override;

    const char* name()     const override { return "Sandbox"; }
    const char* controls() const override {
        return "LClick: Spawn Circle  RClick: Spawn Rect  Up/Down: Gravity  C: Clear";
    }

private:
    int   m_colorIdx    = 0;
    int   m_spawnCount  = 0;
    float m_gravityY    = 500.f;

    static constexpr int kMaxBodies = 120;

    sf::Color nextColor();
};
