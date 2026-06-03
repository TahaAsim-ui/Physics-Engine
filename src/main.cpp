#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <algorithm>

#include "engine/World.hpp"
#include "ui/HUD.hpp"
#include "scenes/Scene.hpp"
#include "scenes/BouncingBalls.hpp"
#include "scenes/FallingBlocks.hpp"
#include "scenes/ObjectCollision.hpp"
#include "scenes/ProjectileMotion.hpp"
#include "scenes/Sandbox.hpp"
#include "scenes/FrictionDemo.hpp"

static constexpr float kWidth  = 1280.f;
static constexpr float kHeight = 720.f;

static void drawBackground(sf::RenderWindow& window) {
    window.clear(sf::Color(22, 22, 36));

    // Subtle grid
    sf::RectangleShape line;
    line.setFillColor(sf::Color(35, 35, 55));
    for (float x = 0.f; x < kWidth; x += 80.f) {
        line.setSize({1.f, kHeight});
        line.setPosition({x, 0.f});
        window.draw(line);
    }
    for (float y = 0.f; y < kHeight; y += 80.f) {
        line.setSize({kWidth, 1.f});
        line.setPosition({0.f, y});
        window.draw(line);
    }
}

static void drawBounds(sf::RenderWindow& window) {
    const sf::Color wallCol(60, 60, 100, 200);
    const float T = 3.f;

    sf::RectangleShape wall;
    wall.setFillColor(wallCol);

    // Floor
    wall.setSize({kWidth, T});
    wall.setPosition({0.f, kHeight - T});
    window.draw(wall);
    // Ceiling
    wall.setPosition({0.f, 0.f});
    window.draw(wall);
    // Left
    wall.setSize({T, kHeight});
    wall.setPosition({0.f, 0.f});
    window.draw(wall);
    // Right
    wall.setPosition({kWidth - T, 0.f});
    window.draw(wall);
}

int main() {
    sf::RenderWindow window(
        sf::VideoMode({(unsigned)kWidth, (unsigned)kHeight}),
        "2D Physics Engine");
    window.setFramerateLimit(60);

    sf::Font font;
    const bool fontLoaded = font.openFromFile("/System/Library/Fonts/Monaco.ttf");

    World world(kWidth, kHeight);

    std::vector<std::unique_ptr<Scene>> scenes;
    scenes.push_back(std::make_unique<BouncingBalls>());
    scenes.push_back(std::make_unique<FallingBlocks>());
    scenes.push_back(std::make_unique<ObjectCollision>());
    scenes.push_back(std::make_unique<ProjectileMotion>());
    scenes.push_back(std::make_unique<Sandbox>());
    scenes.push_back(std::make_unique<FrictionDemo>());

    int currentScene = 0;
    scenes[currentScene]->setup(world);

    // HUD is only constructed if font loaded
    std::unique_ptr<HUD> hud;
    if (fontLoaded) hud = std::make_unique<HUD>(font);

    sf::Clock   clock;
    float       accumulator = 0.f;
    const float kFixedDt    = 1.f / 120.f;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        dt = std::min(dt, 0.05f);   // cap: prevents spiral-of-death

        // ── Events ───────────────────────────────────────────────────
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                continue;
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                // Scene switching: keys 1–6
                const auto k = key->code;
                const auto N1 = sf::Keyboard::Key::Num1;
                if (k >= N1 && k <= sf::Keyboard::Key::Num6) {
                    int idx = static_cast<int>(k) - static_cast<int>(N1);
                    if (idx != currentScene && idx < (int)scenes.size()) {
                        currentScene = idx;
                        scenes[currentScene]->setup(world);
                    }
                }
                if (k == sf::Keyboard::Key::Space)
                    world.paused = !world.paused;
                if (k == sf::Keyboard::Key::R) {
                    scenes[currentScene]->setup(world);
                }
                if (k == sf::Keyboard::Key::Escape)
                    window.close();
            }

            // Forward all events to the active scene
            scenes[currentScene]->handleEvent(*event, world, window);
        }

        // ── Fixed-timestep update ────────────────────────────────────
        accumulator += dt;
        while (accumulator >= kFixedDt) {
            scenes[currentScene]->update(world, kFixedDt);
            world.step(kFixedDt);
            accumulator -= kFixedDt;
        }

        // ── Render ───────────────────────────────────────────────────
        drawBackground(window);
        drawBounds(window);
        world.render(window);

        if (fontLoaded) {
            scenes[currentScene]->renderOverlay(window, font);
            hud->draw(window, world,
                      scenes[currentScene]->name(),
                      scenes[currentScene]->controls(),
                      currentScene + 1);
        }

        window.display();
    }

    return 0;
}
