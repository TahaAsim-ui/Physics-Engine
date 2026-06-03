#include "HUD.hpp"
#include <string>

void HUD::drawPanel(sf::RenderWindow& window, sf::FloatRect b, sf::Color fill) const {
    sf::RectangleShape panel({b.size.x, b.size.y});
    panel.setPosition({b.position.x, b.position.y});
    panel.setFillColor(fill);
    window.draw(panel);
}

void HUD::draw(sf::RenderWindow& window,
               const World& world,
               const char* sceneName,
               const char* controls,
               int sceneNum) const
{
    const float W = (float)window.getSize().x;

    // ── Top bar ──────────────────────────────────────────────────────
    drawPanel(window, {{0.f, 0.f}, {W, 38.f}}, sf::Color(10, 10, 20, 200));

    // Scene number badge
    sf::Text badge(m_font, std::to_string(sceneNum) + "/6", 14u);
    badge.setFillColor(sf::Color(140, 140, 180));
    badge.setPosition({10.f, 10.f});
    window.draw(badge);

    // Scene name (centred)
    sf::Text title(m_font, sceneName, 18u);
    title.setFillColor(sf::Color(230, 230, 255));
    float titleX = W * 0.5f - title.getLocalBounds().size.x * 0.5f;
    title.setPosition({titleX, 9.f});
    window.draw(title);

    // Body count + FPS (right-aligned)
    int dynamicCount = 0;
    for (const auto& b : world.bodies) if (!b.isStatic && b.alive) ++dynamicCount;

    std::string info = "Bodies: " + std::to_string(dynamicCount);
    sf::Text infoText(m_font, info, 14u);
    infoText.setFillColor(sf::Color(140, 200, 140));
    infoText.setPosition({W - infoText.getLocalBounds().size.x - 12.f, 10.f});
    window.draw(infoText);

    // ── Paused banner ────────────────────────────────────────────────
    if (world.paused) {
        sf::Text paused(m_font, "PAUSED", 36u);
        paused.setFillColor(sf::Color(255, 200, 50, 220));
        float px = W * 0.5f - paused.getLocalBounds().size.x * 0.5f;
        paused.setPosition({px, 300.f});
        window.draw(paused);
    }

    // ── Bottom bar ───────────────────────────────────────────────────
    const float barH  = 28.f;
    const float barY  = (float)window.getSize().y - barH;
    drawPanel(window, {{0.f, barY}, {W, barH}}, sf::Color(10, 10, 20, 200));

    std::string ctrlStr = "1-6: Scene   Space: Pause   R: Reset   Esc: Quit";
    if (controls && controls[0] != '\0')
        ctrlStr = std::string(controls) + "   |   " + ctrlStr;

    sf::Text ctrlText(m_font, ctrlStr, 12u);
    ctrlText.setFillColor(sf::Color(120, 120, 160));
    ctrlText.setPosition({10.f, barY + 6.f});
    window.draw(ctrlText);
}
