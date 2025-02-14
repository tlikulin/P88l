#pragma once

#include <SFML/Graphics.hpp>

class FPSCounter
{
public:
    FPSCounter();
    void setFont(const sf::Font& font);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
private:
    sf::Text m_text;
    float m_elapsed = 0.0f;
    int m_frames = 0;  
};