#pragma once
#include "engine/World.hpp"
#include <SFML/Graphics.hpp>

class Scene {
public:
    virtual ~Scene() = default;

    virtual void setup(World& world) = 0;

    virtual void update(World& /*world*/, float /*dt*/) {}

    virtual void handleEvent(const sf::Event& /*event*/,
                             World& /*world*/,
                             sf::RenderWindow& /*window*/) {}

    virtual void renderOverlay(sf::RenderWindow& /*window*/,
                               const sf::Font& /*font*/) {}

    virtual const char* name()     const = 0;
    virtual const char* controls() const { return ""; }
};
