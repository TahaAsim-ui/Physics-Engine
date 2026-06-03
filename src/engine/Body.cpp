#include "Body.hpp"

Body Body::circle(Vec2 pos, float r, float mass, float e, float mu, sf::Color col) {
    Body b;
    b.pos = pos;  b.vel = {};
    b.mass = mass;  b.invMass = (mass > 0.f) ? 1.f / mass : 0.f;
    b.restitution = e;  b.friction = mu;
    b.shape = ShapeType::Circle;  b.radius = r;
    b.color = col;  b.isStatic = false;  b.alive = true;
    return b;
}

Body Body::rect(Vec2 pos, float w, float h, float mass, float e, float mu, sf::Color col) {
    Body b;
    b.pos = pos;  b.vel = {};
    b.mass = mass;  b.invMass = (mass > 0.f) ? 1.f / mass : 0.f;
    b.restitution = e;  b.friction = mu;
    b.shape = ShapeType::Rect;  b.halfSize = {w * 0.5f, h * 0.5f};
    b.color = col;  b.isStatic = false;  b.alive = true;
    return b;
}

Body Body::staticRect(Vec2 pos, float w, float h, sf::Color col) {
    Body b = rect(pos, w, h, 0.f, 0.3f, 0.7f, col);
    b.isStatic = true;  b.invMass = 0.f;
    return b;
}
