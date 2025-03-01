#include "FPSCounter.hpp"
#include <string>

namespace
{
    constexpr unsigned int FPS_FONT_SIZE    = 18u;
    const sf::Color FPS_COLOR               = sf::Color::Blue;
    const sf::String FPS_INITIAL_STRING     {"---"};
    constexpr float FPS_UPDATE_EVERY        = 1.0f;
}

FPSCounter::FPSCounter()
{
    m_text.setFillColor(FPS_COLOR);
    m_text.setCharacterSize(FPS_FONT_SIZE);
    m_text.setString(FPS_INITIAL_STRING);
}

void FPSCounter::setFont(const sf::Font& font)
{
    m_text.setFont(font);
}

// The number of frames since last reset is incremented, resets when the accumulated time reaches 1s and updates the display.
void FPSCounter::update(float deltaTime)
{
    m_frames++;
    m_elapsed += deltaTime;
    if (m_elapsed >= FPS_UPDATE_EVERY)
    {
        m_text.setString(std::to_string(m_frames));
        m_elapsed -= FPS_UPDATE_EVERY;
        m_frames = 0u;
    }
}

void FPSCounter::draw(sf::RenderWindow& window)
{
    window.draw(m_text);
}
