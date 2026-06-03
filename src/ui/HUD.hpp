#pragma once
#include "engine/World.hpp"
#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD(const sf::Font& font) : m_font(font) {}

    void draw(sf::RenderWindow& window,
              const World& world,
              const char* sceneName,
              const char* controls,
              int sceneNum) const;

private:
    const sf::Font& m_font;

    void drawPanel(sf::RenderWindow& window, sf::FloatRect bounds,
                   sf::Color fill) const;
};
