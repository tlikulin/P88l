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
    sf::Vertex m_segment1L[2];
    sf::Vertex m_segment1R[2];
    sf::Vertex m_segment2[2];
    sf::Vertex m_segment2L[2];
    sf::Vertex m_segment2R[2];
    sf::CircleShape m_ballPrev1;
    sf::CircleShape m_ballPrev2;
    bool m_isExtensionNeeded = false;
};
