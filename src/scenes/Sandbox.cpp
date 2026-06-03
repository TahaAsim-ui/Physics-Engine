#include "Sandbox.hpp"
#include <string>
#include <algorithm>

static const sf::Color kPalette[] = {
    sf::Color(220,  60,  60), sf::Color(255, 140,   0), sf::Color(255, 220,  50),
    sf::Color( 60, 200,  60), sf::Color( 50, 190, 220), sf::Color(160,  60, 220),
    sf::Color(220,  80, 160), sf::Color(200, 200,  80), sf::Color( 80, 220, 160),
};
static constexpr int kPaletteSize = 9;

sf::Color Sandbox::nextColor() {
    sf::Color c = kPalette[m_colorIdx % kPaletteSize];
    ++m_colorIdx;
    return c;
}

void Sandbox::setup(World& world) {
    world.reset();
    world.gravity  = {0.f, 500.f};
    m_gravityY     = 500.f;
    m_colorIdx     = 0;
    m_spawnCount   = 0;
}

void Sandbox::handleEvent(const sf::Event& event, World& world, sf::RenderWindow& window) {
    if (const auto* mb = event.getIf<sf::Event::MouseButtonPressed>()) {
        if ((int)world.bodies.size() >= kMaxBodies) return;

        auto mp  = sf::Mouse::getPosition(window);
        Vec2 pos = {(float)mp.x, (float)mp.y};

        if (mb->button == sf::Mouse::Button::Left) {
            float r = 14.f + (m_spawnCount % 5) * 3.f;
            world.addBody(Body::circle(pos, r, 1.5f, 0.6f, 0.3f, nextColor()));
        } else if (mb->button == sf::Mouse::Button::Right) {
            float w = 32.f + (m_spawnCount % 4) * 12.f;
            float h = 22.f + (m_spawnCount % 3) * 10.f;
            world.addBody(Body::rect(pos, w, h, 2.f, 0.4f, 0.5f, nextColor()));
        }
        ++m_spawnCount;
    }

    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
        if (key->code == sf::Keyboard::Key::Up) {
            m_gravityY = std::max(-1000.f, m_gravityY - 100.f);
            world.gravity.y = m_gravityY;
        }
        if (key->code == sf::Keyboard::Key::Down) {
            m_gravityY = std::min(1500.f, m_gravityY + 100.f);
            world.gravity.y = m_gravityY;
        }
        if (key->code == sf::Keyboard::Key::C) {
            world.clear();
            m_spawnCount = 0;
        }
    }
}

void Sandbox::renderOverlay(sf::RenderWindow& window, const sf::Font& font) {
    std::string gravStr = "Gravity: " + std::to_string((int)m_gravityY) + " px/s2";
    sf::Text label(font, gravStr, 15u);
    label.setFillColor(sf::Color(180, 220, 255));
    label.setPosition({10.f, 670.f});
    window.draw(label);
}
