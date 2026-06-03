#include "Collision.hpp"
#include <algorithm>
#include <cmath>

namespace {

// Convention: n points FROM a TOWARD b.
// relVel = velB - velA; velN < 0 means approaching.
void applyImpulse(Body& a, Body& b, Vec2 n, float penetration) {
    Vec2  relVel = b.vel - a.vel;
    float velN   = relVel.dot(n);
    if (velN > 0.f) return;  // already separating

    float e = std::min(a.restitution, b.restitution);
    float j = -(1.f + e) * velN / (a.invMass + b.invMass);

    Vec2 impulse = n * j;
    a.vel -= impulse * a.invMass;
    b.vel += impulse * b.invMass;

    // Tangential friction impulse
    Vec2 relVel2 = b.vel - a.vel;
    Vec2 tangent = relVel2 - n * relVel2.dot(n);
    if (tangent.lengthSq() > 1e-8f) {
        tangent      = tangent.normalized();
        float jt     = -relVel2.dot(tangent) / (a.invMass + b.invMass);
        float mu     = std::sqrt(a.friction * a.friction + b.friction * b.friction);
        Vec2  fImpulse = (std::abs(jt) < std::abs(j) * mu)
                           ? tangent * jt
                           : tangent * (-std::abs(j) * mu);
        a.vel -= fImpulse * a.invMass;
        b.vel += fImpulse * b.invMass;
    }

    // Positional correction to prevent sinking
    const float percent = 0.4f, slop = 0.02f;
    float corrMag = std::max(penetration - slop, 0.f) / (a.invMass + b.invMass) * percent;
    Vec2  corr    = n * corrMag;
    a.pos -= corr * a.invMass;
    b.pos += corr * b.invMass;
}

void circleCircle(Body& a, Body& b) {
    Vec2  d    = b.pos - a.pos;
    float dist = d.length();
    float sum  = a.radius + b.radius;
    if (dist >= sum) return;

    Vec2 n = (dist < 1e-6f) ? Vec2{1.f, 0.f} : d / dist;
    applyImpulse(a, b, n, sum - dist);
}

void rectRect(Body& a, Body& b) {
    Vec2  d  = b.pos - a.pos;
    float ox = (a.halfSize.x + b.halfSize.x) - std::abs(d.x);
    float oy = (a.halfSize.y + b.halfSize.y) - std::abs(d.y);
    if (ox <= 0.f || oy <= 0.f) return;

    Vec2  n;
    float pen;
    if (ox < oy) { n = {(d.x > 0.f) ? 1.f : -1.f, 0.f}; pen = ox; }
    else         { n = {0.f, (d.y > 0.f) ? 1.f : -1.f}; pen = oy; }

    applyImpulse(a, b, n, pen);
}

// a = circle, b = rect
void circleRect(Body& c, Body& r) {
    float cx = std::clamp(c.pos.x, r.pos.x - r.halfSize.x, r.pos.x + r.halfSize.x);
    float cy = std::clamp(c.pos.y, r.pos.y - r.halfSize.y, r.pos.y + r.halfSize.y);

    Vec2  diff   = c.pos - Vec2{cx, cy};
    float distSq = diff.lengthSq();
    if (distSq >= c.radius * c.radius || distSq < 1e-8f) return;

    float dist = std::sqrt(distSq);
    // n from a (circle) toward b (rect): negate diff direction
    Vec2 n = -(diff / dist);
    applyImpulse(c, r, n, c.radius - dist);
}

} // namespace

void Collision::resolve(Body& a, Body& b) {
    if (a.isStatic && b.isStatic) return;

    if      (a.shape == ShapeType::Circle && b.shape == ShapeType::Circle) circleCircle(a, b);
    else if (a.shape == ShapeType::Rect   && b.shape == ShapeType::Rect)   rectRect(a, b);
    else if (a.shape == ShapeType::Circle && b.shape == ShapeType::Rect)   circleRect(a, b);
    else if (a.shape == ShapeType::Rect   && b.shape == ShapeType::Circle) circleRect(b, a);
}
