#pragma once

#include <SFML/Graphics.hpp>

// The visual part of the table.
class Table
{
public:
    Table();
    
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape m_cloth;
    sf::RectangleShape m_rails;
};