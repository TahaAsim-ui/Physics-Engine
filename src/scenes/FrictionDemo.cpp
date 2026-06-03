#include "FrictionDemo.hpp"
#include <string>
#include <cmath>

constexpr float FrictionDemo::kMu[];
const sf::Color FrictionDemo::kColors[kCount] = {
    sf::Color( 80, 200, 255),
    sf::Color( 80, 220, 100),
    sf::Color(255, 200,  50),
    sf::Color(255,  80,  80),
};

void FrictionDemo::setup(World& world) {
    world.reset();
    world.gravity = {0.f, 500.f};

    // Flat platform lines (static rects) for visual reference
    world.addBody(Body::staticRect({640.f, 715.f}, 1280.f, 10.f, sf::Color(70, 70, 100)));

    // One row of balls per friction value
    float spacing = 1280.f / (kCount + 1);
    for (int i = 0; i < kCount; ++i) {
        float x = spacing * (i + 1);
        auto& b = world.addBody(
            Body::circle({x, kLaunchY}, kRadius, 2.f, 0.05f, kMu[i], kColors[i]));
        b.vel = {kInitVel, 0.f};
    }
}

void FrictionDemo::renderOverlay(sf::RenderWindow& window, const sf::Font& font) {
    float spacing = 1280.f / (kCount + 1);
    for (int i = 0; i < kCount; ++i) {
        float x = spacing * (i + 1);

        // mu label above each ball
        std::string muStr = "mu=" + std::to_string(kMu[i]).substr(0, 4);
        sf::Text label(font, muStr, 16u);
        label.setFillColor(kColors[i]);
        label.setPosition({x - 26.f, kLaunchY - kRadius - 30.f});
        window.draw(label);
    }

    // Legend
    sf::Text legend(font, "All balls start with same velocity. Watch friction slow each one.", 14u);
    legend.setFillColor(sf::Color(180, 180, 180));
    legend.setPosition({10.f, 10.f});
    window.draw(legend);
}
