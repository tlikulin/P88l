#pragma once

#include <SFML/Graphics.hpp>

// A simple fps counter displayed in the top-left corner, updated with deltaTime.
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
    unsigned int m_frames = 0;  
};
