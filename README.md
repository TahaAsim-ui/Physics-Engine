# 2D Physics Engine

A real-time 2D physics sandbox built in C++ with SFML. Features rigid body simulation with gravity, collision detection, and 6 interactive demo scenes.

## Features

- Circle and rectangle rigid bodies
- Gravity, friction, and restitution
- Iterative collision resolution with wall bounds
- Fixed-timestep simulation at 120 Hz
- HUD with live body count and controls

## Scenes

| Key | Scene | Description |
|-----|-------|-------------|
| `1` | Bouncing Balls | Circles bouncing under gravity |
| `2` | Falling Blocks | Stacked rectangles collapsing |
| `3` | Object Collision | Shapes colliding at various angles |
| `4` | Projectile Motion | Launched projectiles with trajectories |
| `5` | Sandbox | Spawn your own shapes interactively |
| `6` | Friction Demo | Blocks sliding across surfaces |

## Controls

| Key | Action |
|-----|--------|
| `1`–`6` | Switch scene |
| `Space` | Pause / unpause |
| `R` | Reset current scene |
| `Escape` | Quit |

**Sandbox extras:** Left-click spawns a circle, right-click spawns a rectangle, `Up`/`Down` adjusts gravity, `C` clears all bodies.

## Building

**Requirements:** C++17, CMake 3.16+, SFML 3 (via Homebrew)

```bash
brew install sfml
mkdir build && cd build
cmake ..
make
./PhysicsEngine
```

## Project Structure

```
src/
├── engine/
│   ├── Body.hpp / Body.cpp        # Rigid body (circle + rect)
│   ├── Collision.hpp / Collision.cpp  # Collision detection & response
│   ├── World.hpp / World.cpp      # Simulation loop, broad-phase
│   └── Vec2.hpp                   # 2D vector math
├── scenes/
│   ├── Scene.hpp                  # Abstract scene interface
│   ├── BouncingBalls, FallingBlocks, ObjectCollision
│   ├── ProjectileMotion, Sandbox, FrictionDemo
└── ui/
    └── HUD.hpp / HUD.cpp          # On-screen overlay
```
