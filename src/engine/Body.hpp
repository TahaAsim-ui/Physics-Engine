#pragma once
#include "Vec2.hpp"
#include <SFML/Graphics/Color.hpp>

enum class ShapeType { Circle, Rect };

struct Body {
    Vec2  pos, vel;
    float mass       = 1.f;
    float invMass    = 1.f;
    float restitution = 0.5f;
    float friction    = 0.3f;

    ShapeType shape    = ShapeType::Circle;
    float     radius   = 10.f;
    Vec2      halfSize;

    sf::Color color    = sf::Color::White;
    bool      isStatic = false;
    bool      alive    = true;

    static Body circle(Vec2 pos, float r, float mass,
                       float e  = 0.6f,
                       float mu = 0.3f,
                       sf::Color col = sf::Color::White);

    static Body rect(Vec2 pos, float w, float h, float mass,
                     float e  = 0.4f,
                     float mu = 0.5f,
                     sf::Color col = sf::Color::White);

    static Body staticRect(Vec2 pos, float w, float h,
                           sf::Color col = sf::Color(70, 70, 95, 255));
};
