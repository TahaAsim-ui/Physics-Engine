#pragma once
#include "Body.hpp"

namespace Collision {
    // Detect and resolve the collision between two bodies (if any).
    void resolve(Body& a, Body& b);
}
