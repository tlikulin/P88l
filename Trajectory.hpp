#pragma once

#include <SFML/Graphics.hpp>
#include "Specs.hpp"

class Trajectory
{
public:
    Trajectory();
    void update(const sf::Vector2f& chargeStart, const sf::Vector2f& mousePosition);
    void draw(sf::RenderWindow& window);
private:
    sf::Vertex m_segment1[2];
    sf::Vertex m_segment2[2];
    sf::CircleShape m_ballPrev;
    bool m_isExtensionNeeded = false;
};
