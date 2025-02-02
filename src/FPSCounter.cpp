#include "FPSCounter.hpp"
#include <string>

FPSCounter::FPSCounter()
{
    m_text.setFillColor(sf::Color{0x00ed00ff});
    m_text.setCharacterSize(18);
    m_text.setOutlineThickness(1.0f);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setString("---");
}

void FPSCounter::setFont(const sf::Font& font)
{
    m_text.setFont(font);
}

void FPSCounter::update(float deltaTime)
{
    m_frames++;
    m_elapsed += deltaTime;
    if (m_elapsed >= 1.0f)
    {
        m_text.setString(std::to_string(m_frames));
        m_elapsed -= 1.0f;
        m_frames = 0;
    }
}

void FPSCounter::draw(sf::RenderWindow& window)
{
    window.draw(m_text);
}